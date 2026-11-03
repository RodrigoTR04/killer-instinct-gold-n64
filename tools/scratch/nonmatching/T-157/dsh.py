#!/usr/bin/env python3
"""Declaration-order hill climb with the fast standalone evaluator.

usage: dsh.py fn draft.c [--iters N] [--seed S] [-j J] [--out best.c] [--header H]
Only the leading run of plain declaration lines (no '=' initialisers needed to stay put:
every declaration line moves) is permuted. Objective: (reg-masked LCS, exact LCS).
Each round evaluates J random moves (swap or move-to-position) from the current best
in parallel and keeps the best strictly-better-or-equal candidate.
"""
import argparse, concurrent.futures as cf, importlib.util, random, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

DECL = re.compile(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$')

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--iters', type=int, default=20); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    ap.add_argument('--header', default='#include "common.h"\n')
    ap.add_argument('--key', default='reg', choices=['reg','exact','p'])
    ap.add_argument('--keep', type=int, default=0, help='number of leading declarations pinned')
    a = ap.parse_args()
    src = Path(a.draft).read_text()
    m = re.search(r'\b' + a.function + r'\([^)]*\)\s*\{\n', src)
    i0 = m.end()
    lines = src[i0:].split('\n')
    decl = []
    for ln in lines:
        if DECL.match(ln) and not re.match(r'^    (return|goto|break)', ln):
            decl.append(ln)
        else:
            break
    n = len(decl)
    rest = '\n'.join(lines[n:])
    def build(order):
        return src[:i0] + '\n'.join(decl[k] for k in order) + '\n' + rest
    rnd = random.Random(a.seed)
    cur = tuple(range(n))
    def ev(o):
        s = fast.score(a.function, build(o), a.header)
        return s
    best = ev(cur)
    print('start', best, flush=True)
    for it in range(a.iters):
        cands = []
        for _ in range(a.j):
            o = list(cur)
            if rnd.random() < 0.5:
                i, j = rnd.sample(range(a.keep, n), 2)
                o[i], o[j] = o[j], o[i]
            else:
                i = rnd.randrange(a.keep, n); j = rnd.randrange(a.keep, n)
                v = o.pop(i); o.insert(j, v)
            cands.append(tuple(o))
        with cf.ThreadPoolExecutor(a.j) as ex:
            res = list(zip(cands, ex.map(ev, cands)))
        res = [(s, o) for o, s in res if s is not None]
        if not res:
            continue
        K = (lambda s: (s[0], s[1])) if a.key == 'reg' else ((lambda s: (s[4], s[1])) if a.key == 'p' else (lambda s: (s[1], s[0])))
        res.sort(key=lambda r: K(r[0]))
        s, o = res[0]
        if K(s) <= K(best):
            if K(s) < K(best):
                print(it, 'improved', s, [decl[k].strip().split()[-1] for k in o], flush=True)
            best, cur = s, o
            if a.out:
                Path(a.out).write_text(build(cur))
    print('final', best)
    print('\n'.join(decl[k] for k in cur))

if __name__ == '__main__':
    main()
