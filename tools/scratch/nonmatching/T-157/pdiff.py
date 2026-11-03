#!/usr/bin/env python3
"""pdiff.py fn draft.c : print the permuter scorer's penalty breakdown for a draft (header: common.h)"""
import importlib.util, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
fn = sys.argv[1]; text = Path(sys.argv[2]).read_text()
sc = fast.pscorer(fn)
sc.debug_mode = True
with tempfile.TemporaryDirectory() as d:
    o = fast.cm.compile_source('#include "common.h"\n' + text, Path(d) / 'c.c')
    print(sc.score(str(o))[0])
