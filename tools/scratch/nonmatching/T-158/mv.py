#!/usr/bin/env python3
"""usage: mv.py fn base.c startmarker endmarker  -- try moving each single line of [start,end] to every other slot"""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import lib
fn, base, sm, em = sys.argv[1:5]
lines = Path(base).read_text().split('\n')
a = next(i for i, l in enumerate(lines) if sm in l)
b = next(i for i, l in enumerate(lines) if em in l and i >= a)
region = lines[a:b+1]
cands = {}
n = len(region)
for i in range(n):
    for j in range(n):
        if i == j: continue
        r = region[:]
        x = r.pop(i); r.insert(j, x)
        cands[f'mv {i}->{j}'] = '\n'.join(lines[:a] + r + lines[b+1:])
names = list(cands); srcs = [cands[k] for k in names]
res = lib.run(fn, srcs, prefix=False)
out = sorted(zip(names, res), key=lambda x: (x[1] or (999, 999))[1])
for nme, r in out[:15]: print(nme, r, region[int(nme.split()[1].split('->')[0])].strip()[:50])
