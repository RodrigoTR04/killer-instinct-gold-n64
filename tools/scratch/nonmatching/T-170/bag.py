#!/usr/bin/env python3
"""Bag (multiset) diff of reg-masked canonical instructions: what is extra / missing."""
import importlib.util, sys, tempfile, re, collections
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
REGS = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')

fn, draft = sys.argv[1], Path(sys.argv[2])
if not draft.is_absolute():
    draft = ROOT / draft
src, tu = cm.build_source(fn, draft, False)
with tempfile.TemporaryDirectory() as d:
    o = cm.compile_source(src, Path(d)/'c.c')
    pairs = cm.draft_raw(o, fn)
mine = [REGS.sub('R', cm.canon(cm.apply_relocs(i, r))) for _, i, r in pairs]
theirs = [REGS.sub('R', cm.canon(t)) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
a, b = collections.Counter(theirs), collections.Counter(mine)
print(f'# {fn} target {len(theirs)} draft {len(mine)}')
for k in sorted(set(a) | set(b)):
    if a[k] != b[k]:
        print(f'  T{a[k]:2d} D{b[k]:2d}  {k}')
