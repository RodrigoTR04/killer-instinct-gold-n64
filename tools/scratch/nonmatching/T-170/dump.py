#!/usr/bin/env python3
"""Dump draft instruction list (canonical, no masking)."""
import importlib.util, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT/'tools/scratch/nonmatching/T-155/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
fn = sys.argv[1]
p = Path(sys.argv[2])
src, tu = cm.build_source(fn, p, False)
with tempfile.TemporaryDirectory() as d:
    o = cm.compile_source(src, Path(d)/'c.c')
    pairs = cm.draft_raw(o, fn)
for _, i, r in pairs:
    print(cm.canon(cm.apply_relocs(i, r)))
