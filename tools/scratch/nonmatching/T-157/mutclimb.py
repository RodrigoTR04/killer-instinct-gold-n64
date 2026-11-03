#!/usr/bin/env python3
"""mutclimb.py fn draft.c [--seconds S] [--seed N] [-j J] [--header H] [--out f]
Honest-edit hill climb: random line swaps (simple ';'-terminated statements, distance<=3), joins/splits of
adjacent simple statements, declaration moves, signedness flips of integer declarations.
Accepts equal-or-better (plateau moves allowed). Objective: (exact LCS, reg-masked)."""
import argparse, concurrent.futures as cf, importlib.util, random, re, sys, time
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

DECL = re.compile(r'^(\s+)(s32|u32|u16|f32|s16|u8)\s+(\w+);$')

def simple(l):
    s = l.strip()
    return s.endswith(';') and '{' not in s and '}' not in s and not s.startswith('#') and not s.startswith('return') and s.count(';') == 1 or \
        (s.endswith(';') and '{' not in s and '}' not in s and not s.startswith('#') and 'GCMD' in s)

IDENT = re.compile(r'[A-Za-z_]\w*')
def lhs(l):
    s = l.strip()
    if 'GCMD(' in s or 'g++' in s: return {'g', '*g'}
    m = re.match(r'^(?:\w+\s+)?([A-Za-z_]\w*)\s*(?:\+|-|\*|/|<<|>>|\|)?=[^=]', s)
    if m: return {m.group(1)}
    m = re.match(r'^(\w+)(\+\+|--)', s)
    if m: return {m.group(1)}
    return {'?'}
def ids(l): return set(IDENT.findall(l))
def independent(a, b):
    la, lb = lhs(a), lhs(b)
    if '?' in la or '?' in lb: return False
    return not (la & ids(b)) and not (lb & ids(a)) and not (la & lb)

def mutate(lines, rnd, fn_lo, fn_hi):
    ls = list(lines)
    for _ in range(40):
        op = rnd.choice(['swap', 'swap', 'move', 'move', 'join', 'split', 'decl', 'sign'])
        if op == 'swap':
            i = rnd.randrange(fn_lo, fn_hi - 1); d = rnd.randint(1, 3)
            j = i + d
            if j >= fn_hi: continue
            if not all(simple(ls[k]) for k in range(i, j + 1)): continue
            if any(DECL.match(ls[k]) for k in range(i, j + 1)): continue
            if not all(independent(ls[i], ls[k]) for k in range(i + 1, j + 1)): continue
            if not all(independent(ls[j], ls[k]) for k in range(i, j)): continue
            ls[i], ls[j] = ls[j], ls[i]
            return ls, f'swap {i} {j}'
        if op == 'move':
            i = rnd.randrange(fn_lo, fn_hi)
            if not simple(ls[i]) or DECL.match(ls[i]) or ls[i].strip().startswith(('GCMD', 'x +=', 'i +=', 'accX')): continue
            j = i + rnd.choice([-12, -8, -5, -4, -3, -2, 2, 3, 4, 5, 8, 12])
            if j < fn_lo or j >= fn_hi or j == i: continue
            lo, hi = (i + 1, j) if j > i else (j, i - 1)
            seg = ls[lo:hi + 1]
            if not all(simple(x) and not DECL.match(x) for x in seg): continue
            if not all(independent(ls[i], x) for x in seg): continue
            l = ls.pop(i); ls.insert(j, l)
            return ls, f'move {i}->{j}'
        if op == 'join':
            i = rnd.randrange(fn_lo + 1, fn_hi)
            if simple(ls[i]) and simple(ls[i - 1]) and not DECL.match(ls[i]) and not DECL.match(ls[i - 1]):
                ls[i - 1] = ls[i - 1].rstrip() + ' ' + ls[i].strip(); del ls[i]
                return ls, f'join {i}'
        if op == 'split':
            i = rnd.randrange(fn_lo, fn_hi)
            m = re.match(r'^(\s+)(.*?;) ((?!\}).*;)$', ls[i])
            if m and '{' not in ls[i] and '(' in ls[i]:
                ls[i:i + 1] = [m.group(1) + m.group(2), m.group(1) + m.group(3)]
                return ls, f'split {i}'
        if op == 'decl':
            ds = [k for k in range(fn_lo, fn_hi) if DECL.match(ls[k])]
            if len(ds) < 2: continue
            a, b = rnd.sample(ds, 2)
            l = ls.pop(a); b = ds[ds.index(b)] if False else b
            ls.insert(b if b < a else b, l)
            return ls, f'decl {a}->{b}'
        if op == 'sign':
            ds = [k for k in range(fn_lo, fn_hi) if DECL.match(ls[k]) and DECL.match(ls[k]).group(2) in ('s32', 'u32')]
            if not ds: continue
            k = rnd.choice(ds); m = DECL.match(ls[k])
            ls[k] = f'{m.group(1)}{"u32" if m.group(2) == "s32" else "s32"} {m.group(3)};'
            return ls, f'sign {m.group(3)}'
    return None, ''

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--seconds', type=int, default=900); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--header', default='#include "common.h"\n')
    ap.add_argument('--out', default=None); ap.add_argument('--key', default='exact', choices=['exact', 'reg', 'p'])
    ap.add_argument('--from', dest='frm', default=None)
    ap.add_argument('--alts', default=None); ap.add_argument('--temp', type=float, default=0.0)
    a = ap.parse_args()
    rnd = random.Random(a.seed)
    lines = Path(a.draft).read_text().split('\n')
    fn_lo = next(i for i, l in enumerate(lines) if re.search(r'\b' + a.function + r'\(', l))
    fn_hi = len(lines)
    K = (lambda s: (s[1], s[0])) if a.key == 'exact' else ((lambda s: (s[4], s[1])) if a.key == 'p' else (lambda s: (s[0], s[1])))
    def ev(ls): return fast.score(a.function, '\n'.join(ls), a.header)
    alts = []
    if a.alts:
        alts = [[l for l in b.split('\n') if l.strip()] for b in Path(a.alts).read_text().split('\n\n') if b.strip()]
    cur = lines; best = ev(cur); curs = best; print('start', best, flush=True)
    bestlines = cur
    t0 = time.time(); seen = set()
    while time.time() - t0 < a.seconds:
        cands = []
        for _ in range(a.j):
            c, d = mutate(cur, rnd, fn_lo + 1, len(cur) - 2)
            if alts and rnd.random() < 0.3:
                blk = rnd.choice(alts); t = '\n'.join(cur)
                for x in blk:
                    if x in t:
                        y = rnd.choice([z for z in blk if z != x]); c = t.replace(x, y, 1).split('\n'); d = 'alt ' + x[:24] + '->' + y[:24]; break
            if c is None: continue
            key = '\n'.join(c)
            if key in seen: continue
            seen.add(key); cands.append((c, d))
        if not cands: continue
        with cf.ThreadPoolExecutor(a.j) as ex:
            res = list(ex.map(lambda cd: (cd, ev(cd[0])), cands))
        res = [(K(s), cd, s) for cd, s in res if s and s[2] >= 400]
        if not res: continue
        res.sort(key=lambda t: t[0])
        k, (c, d), s = res[0]
        accept = k <= K(curs) or (a.temp > 0 and rnd.random() < pow(2.718, -(k[0] - K(curs)[0]) / a.temp))
        if accept:
            cur, curs = c, s
            if k < K(best):
                print(f'{int(time.time() - t0)}s improved {s} via {d}', flush=True)
                best, bestlines = s, c
                if a.out: Path(a.out).write_text('\n'.join(c))
    print('final', best)
    if a.out: Path(a.out).write_text('\n'.join(bestlines))

if __name__ == '__main__':
    main()
