#!/usr/bin/env python3
"""sregs.py fn draft... : for each saved/special reg, print first definition instruction + number of refs (target first)"""
import importlib.util, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
fn = sys.argv[1]
def info(d):
    out = {}
    for i, l in enumerate(d[:]):
        if i < 30: continue  # skip prologue saves
        if l.startswith(('lw s','lw fp','lw ra')) and ('(sp)' in l) and i > len(d) - 22: continue
        m = re.match(r'(\S+)\s+(\S+)', l)
        if not m: continue
        ops = re.split(r'[,\s]+', l)[1:]
        for r in ('s0','s1','s2','s3','s4','s5','s6','s7','s8','fp','ra'):
            if r in ops[:1] and not l.startswith(('sw','sh','sb','swc1','b','beq','bne','bgez','blez')):
                out.setdefault(r, (i, l, 0))
    return out
for name, d in [('T', f.target(fn))] + [(p.split('/')[-1], f.compile_raw(fn, Path(p).read_text())) for p in sys.argv[2:]]:
    inf = info(d)
    print('==', name)
    for r in ('s0','s1','s2','s3','s4','s5','s6','s7','fp','ra'):
        cnt = sum(1 for l in d[30:-22] if re.search(r'\b%s\b' % r, l))
        print(f'  {r:3s} refs={cnt:3d} first-def: {inf.get(r, ("","",""))[:2]}')
