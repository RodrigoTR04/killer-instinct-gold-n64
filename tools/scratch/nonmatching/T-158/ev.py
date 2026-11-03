#!/usr/bin/env python3
"""usage: ev.py fn variants.py  -- variants.py defines BASE (path) and V = [(name, [(old,new),...]), ...]"""
import sys, runpy
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import lib
fn = sys.argv[1]
ns = runpy.run_path(sys.argv[2])
base = Path(ns['BASE']).read_text()
names, srcs = [], []
for name, subs in ns['V']:
    s = base
    for old, new in subs:
        if old not in s:
            print('MISSING', name, repr(old[:50])); s = None; break
        s = s.replace(old, new, 1)
    if s is not None:
        names.append(name); srcs.append(s)
res = lib.run(fn, srcs, prefix=False)
for n, r in sorted(zip(names, res), key=lambda x: (x[1] or (999,999))[1]):
    print(n, r)
if len(sys.argv) > 3:
    for n, s in zip(names, srcs):
        if n == sys.argv[3]:
            Path('/tmp/best_%s.c' % fn).write_text(s)
