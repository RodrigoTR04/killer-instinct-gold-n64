#!/usr/bin/env python3
"""LCS alignment of target vs draft canonical instructions (register-masked), showing gap ops."""
import importlib.util, sys, tempfile, difflib, re, os
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)

REGS = re.compile(r'\b(zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra|f\d+)\b')

fn, draft = sys.argv[1], Path(sys.argv[2])
if not draft.is_absolute():
    draft = ROOT / draft
regmask = '--regs' in sys.argv
src, tu = cm.build_source(fn, draft, False)
with tempfile.TemporaryDirectory() as d:
    o = cm.compile_source(src, Path(d)/'c.c')
    pairs = cm.draft_raw(o, fn)
mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
if regmask:
    mine = [REGS.sub('R', x) for x in mine]
    theirs = [REGS.sub('R', x) for x in theirs]
sm = difflib.SequenceMatcher(None, theirs, mine, autojunk=False)
print(f'# {fn} target {len(theirs)} draft {len(mine)}')
bad = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal':
        continue
    bad += max(i2-i1, j2-j1)
    print(f'--- {tag} T[{i1}:{i2}] D[{j1}:{j2}]')
    for i in range(i1, i2):
        print(f'  -T{i:3d} {theirs[i]}')
    for j in range(j1, j2):
        print(f'  +D{j:3d} {mine[j]}')
print(f'# diffwords={bad}')
