#!/usr/bin/env python3
"""edit.py fn draft [--regs] : LCS edit script (reg-masked) between target and draft; compact"""
import difflib, importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
fn, p = sys.argv[1], sys.argv[2]
t = f.target(fn); d = f.compile_raw(fn, Path(p).read_text())
tm = [f.M(x) for x in t]; dm = [f.M(x) for x in d]
sm = difflib.SequenceMatcher(None, tm, dm, autojunk=False)
n = 0
for tag, i1, i2, j1, j2 in sm.get_opcodes():
    if tag == 'equal': continue
    n += max(i2 - i1, j2 - j1)
    print(tag, 'T', i1, i2, 'M', j1, j2)
    print('   T:', ' | '.join(t[i1:i2])[:260])
    print('   M:', ' | '.join(d[j1:j2])[:260])
print('total', n)
