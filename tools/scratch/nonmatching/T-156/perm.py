#!/usr/bin/env python3
"""Permute whole source lines [a,b] (1-indexed, inclusive) of a draft and score each.

usage (inside toolbox): perm.py fn draft a b [--max N] [-j J] [--regmask]
Each line must be an independent statement.  Prints the best orders by
LCS word diff vs the original assembly (RONORM canonicalisation).
"""
import argparse, difflib, itertools, os, random, re, sys, tempfile, concurrent.futures
from pathlib import Path
import importlib.util

here = Path(__file__).resolve().parent
spec = importlib.util.spec_from_file_location('cmp', here / 'cmp.py')
cmp = importlib.util.module_from_spec(spec); spec.loader.exec_module(cmp)
os.environ['RONORM'] = '1'


def score(function, text, mask):
    with tempfile.TemporaryDirectory(prefix='kig-perm-') as d:
        dp = Path(d) / 'd.c'
        dp.write_text(text)
        source, tu = cmp.build_source(function, dp, False)
        try:
            o = cmp.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cmp.draft_raw(o, function)
    M = (lambda x: re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)) if mask else (lambda x: x)
    mine = [M(cmp.canon(cmp.apply_relocs(i, r))) for _, i, r in pairs]
    theirs = [M(cmp.canon(t)) for t in cmp.target_raw(function)]
    theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('a', type=int); ap.add_argument('b', type=int)
    ap.add_argument('--max', type=int, default=5000)
    ap.add_argument('-j', type=int, default=6)
    ap.add_argument('--regmask', action='store_true')
    ap.add_argument('--seed', type=int, default=1)
    args = ap.parse_args()
    p = Path(args.draft)
    if not p.exists():
        p = here / p
    lines = p.read_text().split('\n')
    seg = lines[args.a - 1:args.b]
    n = len(seg)
    import math
    perms = list(itertools.permutations(range(n))) if math.factorial(n) <= args.max else None
    if perms is None:
        rnd = random.Random(args.seed)
        s = set()
        s.add(tuple(range(n)))
        while len(s) < args.max:
            q = list(range(n)); rnd.shuffle(q); s.add(tuple(q))
        perms = list(s)
    def run(q):
        txt = '\n'.join(lines[:args.a - 1] + [seg[i] for i in q] + lines[args.b:])
        return score(args.function, txt, args.regmask), q
    res = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.j) as ex:
        for r, q in ex.map(run, perms):
            if r is not None:
                res.append((r, q))
    res.sort()
    ident = [r for r, q in res if q == tuple(range(n))]
    print('identity', ident, 'tested', len(res))
    for r, q in res[:8]:
        print(r, q)
    best = res[0][1]
    out = here / 'v' / ('perm_best_' + args.function + '.c')
    out.write_text('\n'.join(lines[:args.a - 1] + [seg[i] for i in best] + lines[args.b:]))
    print('wrote', out)


if __name__ == '__main__':
    main()
