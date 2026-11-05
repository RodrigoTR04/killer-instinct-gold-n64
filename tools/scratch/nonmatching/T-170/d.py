#!/usr/bin/env python3
"""Indexed side-by-side dump: target splat asm (canonical) vs draft objdump (canonical)."""
import importlib.util, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)

fn, draft = sys.argv[1], Path(sys.argv[2])
if not draft.is_absolute():
    draft = ROOT / draft
prefix = '--prefix' in sys.argv
src, tu = cm.build_source(fn, draft, prefix)
with tempfile.TemporaryDirectory() as d:
    o = cm.compile_source(src, Path(d)/'c.c')
    pairs = cm.draft_raw(o, fn)
mine = [cm.canon(cm.apply_relocs(i, r)) for _, i, r in pairs]
theirs = [cm.canon(t) for t in cm.target_raw(fn)]
theirs = [t for t in theirs if not t.startswith(('dlabel', 'enddlabel'))]
print(f'# {fn}  target {len(theirs)} / draft {len(mine)}')
n = max(len(theirs), len(mine))
for i in range(n):
    t = theirs[i] if i < len(theirs) else ''
    m = mine[i] if i < len(mine) else ''
    mark = '  ' if t == m else '!!'
    print(f'{mark}{i:3d} T {t:44s} | D {m}')
