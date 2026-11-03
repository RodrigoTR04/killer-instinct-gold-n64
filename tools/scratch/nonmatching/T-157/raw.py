#!/usr/bin/env python3
"""raw.py fn draft lo hi : print canonical asm lines lo..hi of the draft (or 'T' for target)"""
import importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
fn, p, lo, hi = sys.argv[1], sys.argv[2], int(sys.argv[3]), int(sys.argv[4])
d = f.target(fn) if p == 'T' else f.compile_raw(fn, Path(p).read_text())
for i in range(lo, min(hi, len(d))): print(i, d[i])
