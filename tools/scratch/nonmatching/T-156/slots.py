#!/usr/bin/env python3
"""Greedy per-slot term-order search for `a + b + c` / `a | b | c` chains.

usage (inside toolbox): slots.py fn draft.c SPEC.py [-j N]
SPEC.py defines SLOTS = [ (marker, joiner, [term, ...]), ... ]
The draft must contain the literal text `marker` where the chain is placed
(marker is replaced by joiner.join(permuted terms)).  Slots are optimised one
at a time (others at their current best order), sweeping twice.
Objective: (exact LCS diff, regmask LCS diff).
"""
import argparse, itertools, sys, concurrent.futures
from pathlib import Path
import importlib.util
here = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('perm', here / 'perm.py')
perm = importlib.util.module_from_spec(spec); spec.loader.exec_module(perm)


def build(text, slots, orders):
    for (marker, joiner, terms), order in zip(slots, orders):
        text = text.replace(marker, joiner.join(terms[i] for i in order))
    return text


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft'); ap.add_argument('spec')
    ap.add_argument('-j', type=int, default=6)
    ap.add_argument('--sweeps', type=int, default=2)
    args = ap.parse_args()
    p = Path(args.draft)
    if not p.exists(): p = here / p
    text = p.read_text()
    ns = {}; exec(Path(args.spec).read_text(), ns)
    slots = ns['SLOTS']
    cur = [tuple(range(len(s[2]))) for s in slots]

    def sc(orders):
        t = build(text, slots, orders)
        e = perm.score(args.function, t, False)
        r = perm.score(args.function, t, True)
        return ((e if e is not None else 10**6), (r if r is not None else 10**6))
    best = sc(cur)
    print('start', best, flush=True)
    for sweep in range(args.sweeps):
        for si, s in enumerate(slots):
            cands = list(itertools.permutations(range(len(s[2]))))
            def run(o):
                orders = list(cur); orders[si] = o
                return sc(orders), o
            with concurrent.futures.ThreadPoolExecutor(max_workers=args.j) as ex:
                res = list(ex.map(run, cands))
            res.sort()
            if res[0][0] < best:
                best = res[0][0]; cur[si] = res[0][1]
            print('sweep', sweep, 'slot', si, 'best', best, cur, flush=True)
    out = here / 'v' / ('slots_best_' + args.function + '.c')
    out.write_text(build(text, slots, cur))
    print('wrote', out, best)


if __name__ == '__main__':
    main()
