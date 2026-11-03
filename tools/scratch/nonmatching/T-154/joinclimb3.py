#!/usr/bin/env python3
"""Hill-climb line joins (and splits) of a draft's function body to minimise exact diff.
usage: joinclimb.py fn draft out.c [--prefix]   (RONORM implied)"""
import sys, os, re, difflib, tempfile, importlib.util, concurrent.futures as cf
from pathlib import Path
os.environ['RONORM'] = '1'
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn, draft, out = sys.argv[1:4]
src = Path(draft).read_text()
m = re.search(r'\b' + fn + r'\([^)]*\)\s*\{\n', src)
head, body = src[:m.end()], src[m.end():]
# body ends at final "}\n" of the function
lines = body.rstrip('\n').split('\n')
assert lines[-1].strip() == '}'
lines = lines[:-1]
def split_atoms(text):
    atoms, cur, depth = [], '', 0
    for ch in text:
        cur += ch
        if ch == '(': depth += 1
        elif ch == ')': depth -= 1
        elif depth == 0 and ch in ';{}':
            atoms.append(cur.strip()); cur = ''
    if cur.strip(): atoms.append(cur.strip())
    return [a for a in atoms if a]
atoms = split_atoms(' '.join(l.strip() for l in lines))
# fold 'else' / 'while (..)' tails: keep as separate atoms
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
def build(joins):
    parts = []
    for i, a in enumerate(atoms):
        if i > 0 and joins[i - 1]: parts[-1] += ' ' + a
        else: parts.append('  ' + a)
    return head + '\n'.join(parts) + '\n}\n'
def score(joins):
    with tempfile.TemporaryDirectory(prefix='jc-') as d:
        p = Path(d) / 'draft.c'; p.write_text(build(joins))
        try:
            source, tu = cm.build_source(fn, p)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return (10**6, 10**6)
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    ex = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    import re as _re
    M = lambda x: _re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
    sm = difflib.SequenceMatcher(None, [M(x) for x in theirs], [M(x) for x in mine], autojunk=False)
    rg = sum(max(i2-i1, j2-j1) for t, i1, i2, j1, j2 in sm.get_opcodes() if t != 'equal')
    return (rg, ex)
n = len(atoms) - 1
cur = [False] * n
if len(sys.argv) > 4 and sys.argv[4] == 'keep':
    cur = None
best = score(cur); print('start', best, 'atoms', len(atoms), file=sys.stderr)
with cf.ThreadPoolExecutor(14) as ex:
    improved = True
    while improved:
        improved = False
        cands = []
        for i in range(n):
            c = list(cur); c[i] = not c[i]; cands.append(c)
        import random
        rr = random.Random(len(cands) + int(best[0]) * 7)
        for _ in range(150):
            c = list(cur)
            for k in rr.sample(range(n), 2 if rr.random() < 0.6 else 3): c[k] = not c[k]
            cands.append(c)
        res = list(ex.map(score, cands))
        mn = min(res)
        if mn < best:
            best = mn; cur = cands[res.index(mn)]; improved = True
            print('best', best, 'joins', sum(cur), file=sys.stderr)
            Path(out).write_text(build(cur))
print('final', best)
Path(out).write_text(build(cur))
