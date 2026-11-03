#!/usr/bin/env python3
"""pairs.py fn draft.c [--alts alts.txt] [--header H] [-j J] [--out f] [--slack N] [--cap N]
Atomic honest edits: adjacent independent-statement swaps, line joins, declaration moves/swaps, int sign flips,
and operand alternatives from an alts file.  Evaluates all singles, then pairs among singles within `slack` of the
best (exact LCS), keeps the best result found."""
import argparse, concurrent.futures as cf, importlib.util, itertools, random, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
def load(name):
    spec = importlib.util.spec_from_file_location(name, ROOT / f'tools/scratch/nonmatching/T-157/{name}.py')
    m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m); return m
fast = load('fast')
mc = None
spec = importlib.util.spec_from_file_location('mutclimb', ROOT / 'tools/scratch/nonmatching/T-157/mutclimb.py')
mc = importlib.util.module_from_spec(spec); spec.loader.exec_module(mc)

def atoms(lines, alts):
    out = []  # (description, function lines->lines or None)
    n = len(lines)
    for i in range(n - 1):
        for d in (1, 2):
            j = i + d
            if j >= n: continue
            if not all(mc.simple(lines[k]) for k in range(i, j + 1)): continue
            if any(mc.DECL.match(lines[k]) for k in range(i, j + 1)): continue
            if not all(mc.independent(lines[i], lines[k]) for k in range(i + 1, j + 1)): continue
            if not all(mc.independent(lines[j], lines[k]) for k in range(i, j)): continue
            def f(ls, i=i, j=j):
                ls = list(ls); ls[i], ls[j] = ls[j], ls[i]; return ls
            out.append((f'swap {i},{j}', f))
    for i in range(1, n):
        if mc.simple(lines[i]) and mc.simple(lines[i - 1]) and not mc.DECL.match(lines[i]) and not mc.DECL.match(lines[i - 1]):
            def f(ls, i=i):
                ls = list(ls); ls[i - 1] = ls[i - 1].rstrip() + ' ' + ls[i].strip(); del ls[i]; return ls
            out.append((f'join {i}', f))
    ds = [k for k in range(n) if mc.DECL.match(lines[k])]
    for a in range(len(ds) - 1):
        for b in range(a + 1, min(len(ds), a + 4)):
            def f(ls, x=ds[a], y=ds[b]):
                ls = list(ls); ls[x], ls[y] = ls[y], ls[x]; return ls
            out.append((f'declswap {ds[a]},{ds[b]}', f))
    for k in ds:
        m = mc.DECL.match(lines[k])
        if m.group(2) in ('s32', 'u32'):
            def f(ls, k=k, m=m):
                ls = list(ls); ls[k] = f'{m.group(1)}{"u32" if m.group(2) == "s32" else "s32"} {m.group(3)};'; return ls
            out.append((f'sign {m.group(3)}', f))
    for bi, blk in enumerate(alts):
        for k in range(1, len(blk)):
            def f(ls, a=blk[0], b=blk[k]):
                t = '\n'.join(ls)
                return t.replace(a, b, 1).split('\n') if a in t else ls
            out.append((f'alt {blk[0][:20]}->{blk[k][:20]}', f))
    return out

def main():
    ap = argparse.ArgumentParser(); ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--alts', default=None); ap.add_argument('--header', default='#include "common.h"\n')
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    ap.add_argument('--slack', type=int, default=12); ap.add_argument('--cap', type=int, default=1200)
    ap.add_argument('--seed', type=int, default=1)
    a = ap.parse_args()
    lines = Path(a.draft).read_text().split('\n')
    alts = []
    if a.alts:
        alts = [[l for l in b.split('\n') if l.strip()] for b in Path(a.alts).read_text().split('\n\n') if b.strip()]
    fi = next(i for i, l in enumerate(lines) if re.search(r'\b' + a.function + r'\(', l))
    at = [(d, f) for d, f in atoms(lines, alts)]
    K = lambda s: (s[1], s[0])
    ev = lambda ls: fast.score(a.function, '\n'.join(ls), a.header)
    best = ev(lines); print('start', best, len(at), 'atoms', flush=True)
    with cf.ThreadPoolExecutor(a.j) as ex:
        sc = list(ex.map(lambda df: (df, ev(df[1](lines))), at))
    good = [(K(s), df) for df, s in sc if s and s[2] >= 400]
    good.sort(key=lambda t: t[0])
    print('singles best:', [(g[0], g[1][0]) for g in good[:6]], flush=True)
    cur_best = (K(best), lines, best)
    if good and good[0][0] < K(best):
        k, df = good[0]; cur_best = (k, df[1](lines), None)
    keep = [df for k, df in good if k[0] <= K(best)[0] + a.slack]
    print(len(keep), 'singles within slack', flush=True)
    pairs = list(itertools.combinations(range(len(keep)), 2))
    random.Random(a.seed).shuffle(pairs)
    pairs = pairs[:a.cap]
    def evp(p):
        try:
            ls = keep[p[1]][1](keep[p[0]][1](lines))
        except Exception:
            return None
        return ls, ev(ls)
    with cf.ThreadPoolExecutor(a.j) as ex:
        res = list(ex.map(evp, pairs))
    bestp = None
    for p, r in zip(pairs, res):
        if not r or not r[1] or r[1][2] < 400: continue
        if bestp is None or K(r[1]) < bestp[0]:
            bestp = (K(r[1]), r[0], r[1], (keep[p[0]][0], keep[p[1]][0]))
    if bestp and bestp[0] < cur_best[0]:
        print('best pair', bestp[2], bestp[3]); cur_best = (bestp[0], bestp[1], bestp[2])
        if a.out: Path(a.out).write_text('\n'.join(bestp[1]))
    elif a.out and cur_best[1] is not lines:
        Path(a.out).write_text('\n'.join(cur_best[1]))
    print('final', cur_best[0])

if __name__ == '__main__':
    main()
