#!/usr/bin/env python3
"""sd.py fn draft [from] [to] [--diff] : side-by-side canonical asm via fast.py (target left, draft right); --diff prints only changed hunks with context"""
import difflib, importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
args = [a for a in sys.argv[1:] if not a.startswith('--')]
fn, draft = args[0], args[1]
lo = int(args[2]) if len(args) > 2 else 0; hi = int(args[3]) if len(args) > 3 else 10**6
t = f.target(fn); d = f.compile_raw(fn, Path(draft).read_text())
sm = difflib.SequenceMatcher(None, [f.M(x) for x in t], [f.M(x) for x in d], autojunk=False)
rows = []
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    n = max(i2 - i1, j2 - j1)
    for k in range(n):
        a = t[i1 + k] if i1 + k < i2 else ''; b = d[j1 + k] if j1 + k < j2 else ''
        rows.append((tag, i1 + k if i1 + k < i2 else -1, a, b))
last = -1
for idx, (tag, ti, a, b) in enumerate(rows):
    if '--t' in sys.argv:
        if ti >= 0: last = ti
        if not (lo <= last < hi): continue
    elif idx < lo or idx >= hi: continue
    if '--diff' in sys.argv and tag == 'equal' and a == b: continue
    print(f'{ti:4d} {"=" if tag=="equal" else "!"} {a:30s} {b}')
