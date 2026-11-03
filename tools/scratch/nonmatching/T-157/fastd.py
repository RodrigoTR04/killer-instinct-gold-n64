#!/usr/bin/env python3
"""fastd.py fn draft.c : like fast.py but draft carries its own includes (header empty)"""
import importlib.util, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
fast = importlib.util.module_from_spec(spec); spec.loader.exec_module(fast)
for d in sys.argv[2:]:
    print(d, fast.score(sys.argv[1], Path(d).read_text(), ''))
