#!/usr/bin/env python3
"""dump.py FN DRAFT : print target splat asm and draft object asm side by side."""
import importlib.util, os, re, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
sys.path.insert(0, str(ROOT / 'tools/scratch/nonmatching/T-155'))
spec = importlib.util.spec_from_file_location('cmpmod', ROOT / 'tools/scratch/nonmatching/T-155/cmp.py')
cmpmod = importlib.util.module_from_spec(spec); spec.loader.exec_module(cmpmod)

def main():
    fn, draft = sys.argv[1], Path(sys.argv[2])
    if not draft.is_absolute(): draft = ROOT / draft
    prefix = '--prefix' in sys.argv
    source, tu = cmpmod.build_source(fn, draft, prefix)
    with tempfile.TemporaryDirectory() as d:
        o = cmpmod.compile_source(source, Path(d) / 'c.c')
        pairs = cmpmod.draft_raw(o, fn)
    mine = [cmpmod.canon(cmpmod.apply_relocs(i, r)) for _, i, r in pairs]
    theirs = [cmpmod.canon(t) for t in cmpmod.target_raw(fn)]
    theirs = [t for t in theirs if not t.startswith(('dlabel','enddlabel'))]
    print(f'# {fn}  target {len(theirs)} / draft {len(mine)}')
    for i in range(max(len(theirs), len(mine))):
        t = theirs[i] if i < len(theirs) else ''
        m = mine[i] if i < len(mine) else ''
        flag = ' ' if t == m else '*'
        print(f'{flag}{i:4d}  T: {t:<40s} D: {m}')
main()
