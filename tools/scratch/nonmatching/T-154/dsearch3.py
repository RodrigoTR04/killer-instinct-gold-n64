#!/usr/bin/env python3
"""Declaration-order search scored by register-masked LCS diff (stack offsets kept).

usage: dsearch.py fn draft [--limit N] [--seed S] [-j J] [--out dir]
Permutes the leading declaration lines (between the function's opening brace and
the first blank line / first non-declaration statement).  Lines containing '='
(initialised) are kept in place relative to each other but may move too.
"""
import argparse, difflib, importlib.util, itertools, os, random, re, sys, tempfile, concurrent.futures as cf
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
os.environ['REGMASK'] = '1'; os.environ['RONORM'] = '1'
import re as _re

def M(x):
    return _re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)

def score(function, text, theirs):
    with tempfile.TemporaryDirectory(prefix='ds-') as d:
        p = Path(d) / 'draft.c'; p.write_text(text)
        try:
            source, tu = cm.build_source(function, p)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, function)
    raw = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    mine = [M(x) for x in raw]
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    a = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    rawt = [cm.canon(t) for t in cm.target_raw(function)]
    rawt = [t for t in rawt if not t.startswith(('dlabel', 'enddlabel'))]
    sm = difflib.SequenceMatcher(None, rawt, raw, autojunk=False)
    b = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (a, b)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('function'); ap.add_argument('draft')
    ap.add_argument('--limit', type=int, default=200); ap.add_argument('--seed', type=int, default=1)
    ap.add_argument('-j', type=int, default=8); ap.add_argument('--out', default=None)
    ap.add_argument('--start', default=None, help='regex: first decl line index marker (default after signature brace)')
    a = ap.parse_args()
    src = Path(a.draft).read_text()
    m = re.search(r'\b' + a.function + r'\([^)]*\)\s*\{\n', src)
    i0 = m.end()
    lines = src[i0:].split('\n')
    decl = []
    for ln in lines:
        if re.match(r'^\s+(?:[A-Za-z_]\w*\s+)+\**\w+(\[\w*\])?( = [^;(]+)?;$', ln) and not re.match(r'^    (return|goto|break)', ln):
            decl.append(ln)
        else:
            break
    n = len(decl)
    print('decls', n, file=sys.stderr)
    theirs = [M(cm.canon(t)) for t in cm.target_raw(a.function)]
    theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
    rest = '\n'.join(lines[n:])
    def build(order):
        return src[:i0] + '\n'.join(decl[k] for k in order) + '\n' + rest
    rnd = random.Random(a.seed)
    orders = [tuple(range(n))]
    if __import__('math').factorial(n) <= a.limit:
        orders = list(itertools.permutations(range(n)))
    else:
        seen = {orders[0]}
        while len(orders) < a.limit:
            o = list(range(n)); rnd.shuffle(o); o = tuple(o)
            if o not in seen: seen.add(o); orders.append(o)
    best = None
    with cf.ThreadPoolExecutor(a.j) as ex:
        futs = {ex.submit(score, a.function, build(o), theirs): o for o in orders}
        res = []
        for f in cf.as_completed(futs):
            s = f.result(); o = futs[f]
            if s is None: continue
            res.append((s, o))
            if best is None or s < best[0]:
                best = (s, o); print('best', s, [decl[k].strip() for k in o], file=sys.stderr)
    res.sort()
    print('baseline', [r for r in res if r[1] == tuple(range(n))][:1])
    print('top', res[:5])
    if a.out and best:
        Path(a.out).write_text(build(best[1]))

if __name__ == '__main__':
    main()
