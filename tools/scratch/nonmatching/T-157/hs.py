#!/usr/bin/env python3
"""hs.py fn draft... : print (homes mismatch, mnemonic-multiset diff, pscore, exact LCS) + reg-masked/instr/frame for each draft.
env HOME_LO/HOME_HI select the stack range that holds the memory-resident locals (default 224..320)."""
import importlib.util, sys
from pathlib import Path
fn = sys.argv[1]
files = sys.argv[2:]
sys.argv = ['x']
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('hc', ROOT / 'tools/scratch/nonmatching/T-157/homeclimb.py')
m = importlib.util.module_from_spec(spec); spec.loader.exec_module(m)
for p in files:
    t = Path(p).read_text()
    h = m.hscore(fn, t, '#include "common.h"\n')
    s = m.fast.score(fn, t)
    print(p.split('/')[-1], h, s)
