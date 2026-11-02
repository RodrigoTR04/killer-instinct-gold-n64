#!/usr/bin/env python3
"""Evaluate base + every single atomic edit and every pair. usage: pairs.py fn base.c atoms.py [--prefix env]
atoms.py defines ATOMS = {name: [(old,new[, 'all']),...]}"""
import sys, os, re, difflib, itertools, tempfile, importlib.util, concurrent.futures as cf
from pathlib import Path
os.environ['RONORM'] = '1'
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn, base, atoms = sys.argv[1:4]
ns = {}; exec(Path(atoms).read_text(), ns); ATOMS = ns['ATOMS']
src = Path(base).read_text()
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
def M(x): return re.sub(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-7]|k[01]|gp|sp|fp|ra|f\d+)\b', 'R', x)
def apply(names):
    t = src
    for n in names:
        for ed in ATOMS[n]:
            if ed[0] not in t: return None
            t = t.replace(ed[0], ed[1]) if len(ed) > 2 else t.replace(ed[0], ed[1], 1)
    return t
def score(names):
    t = apply(names)
    if t is None: return None
    with tempfile.TemporaryDirectory(prefix='pr-') as d:
        p = Path(d) / 'draft.c'; p.write_text(t)
        try:
            source, tu = cm.build_source(fn, p)
            o = cm.compile_source(source, Path(d) / 'c.c')
        except SystemExit:
            return None
        pairs = cm.draft_raw(o, fn)
    mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
    sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
    ex = sum(max(i2-i1, j2-j1) for tt, i1, i2, j1, j2 in sm.get_opcodes() if tt != 'equal')
    sm = difflib.SequenceMatcher(None, [M(x) for x in theirs], [M(x) for x in mine], autojunk=False)
    rg = sum(max(i2-i1, j2-j1) for tt, i1, i2, j1, j2 in sm.get_opcodes() if tt != 'equal')
    return ex, rg
names = list(ATOMS)
combos = [()] + [(n,) for n in names] + list(itertools.combinations(names, 2))
if os.environ.get('TRIPLES'): combos += list(itertools.combinations(names, 3))
with cf.ThreadPoolExecutor(14) as ex:
    res = list(ex.map(score, combos))
out = sorted((r, c) for r, c in zip(res, combos) if r)
print('base', res[0])
for r, c in out[:12]: print(r, c)
if out:
    t = apply(out[0][1]); Path('/tmp/pairs_best.c').write_text(t)
