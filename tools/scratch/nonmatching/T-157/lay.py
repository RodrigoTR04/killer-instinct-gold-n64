#!/usr/bin/env python3
"""lay.py fn draft... : print branch/layout skeleton (branch instrs with index) of target and drafts"""
import importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
fn = sys.argv[1]
def sk(d):
    return ' '.join(f'{i}:{l.split()[0]}' for i, l in enumerate(d) if l.split()[0] in ('b','beq','bne','bnez','beqz','bgez','blez','bgtz','bltz','bnel','beql','bnezl','beqzl','blezl','bc1t','bc1f','bc1tl','bc1fl'))
print('T', sk(f.target(fn)))
for p in sys.argv[2:]:
    print(p.split('/')[-1], sk(f.compile_raw(fn, Path(p).read_text())))
