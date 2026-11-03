#!/usr/bin/env python3
"""permblocks.py fn draft.c start_regex n [more 'start_regex n' pairs] [--header H] [--out f]
For each block of n consecutive lines starting at the line matching start_regex, evaluate every permutation
(coordinate descent over blocks, repeated until no gain). Objective: (exact LCS, reg-masked)."""
import argparse, concurrent.futures as cf, importlib.util, itertools, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft'); ap.add_argument('blocks', nargs='+')
    ap.add_argument('--header', default='#include "common.h"\n'); ap.add_argument('-j', type=int, default=8)
    ap.add_argument('--out', default=None); ap.add_argument('--key', default='exact', choices=['exact', 'reg', 'p'])
    a = ap.parse_args()
    lines = Path(a.draft).read_text().split('\n')
    spec_blocks = [(a.blocks[i], int(a.blocks[i + 1])) for i in range(0, len(a.blocks), 2)]
    K = (lambda s: (s[1], s[0])) if a.key == 'exact' else ((lambda s: (s[4], s[1])) if a.key == 'p' else (lambda s: (s[0], s[1])))
    def ev(ls): return fast.score(a.function, '\n'.join(ls), a.header)
    best = ev(lines); print('start', best, flush=True)
    for rnd in range(3):
        changed = False
        for rx, n in spec_blocks:
            idx = next((i for i, l in enumerate(lines) if re.search(rx, l)), None)
            if idx is None: print('missing', rx); continue
            blk = lines[idx:idx + n]
            cands = []
            for p in itertools.permutations(range(n)):
                if list(p) == list(range(n)): continue
                cands.append(lines[:idx] + [blk[k] for k in p] + lines[idx + n:])
            with cf.ThreadPoolExecutor(a.j) as ex:
                res = list(zip(cands, ex.map(ev, cands)))
            res = [(K(s), c, s) for c, s in res if s]
            if not res: continue
            res.sort(key=lambda t: t[0])
            if res[0][0] < K(best):
                best, lines, changed = res[0][2], res[0][1], True
                print('improved', rx, best, flush=True)
        if not changed: break
    print('final', best)
    if a.out: Path(a.out).write_text('\n'.join(lines))

if __name__ == '__main__':
    main()
