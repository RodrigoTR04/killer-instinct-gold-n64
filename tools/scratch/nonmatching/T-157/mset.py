#!/usr/bin/env python3
"""mset.py fn draft... : mnemonic multiset difference (draft - target)"""
import importlib.util, sys
from collections import Counter
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('fast', ROOT / 'tools/scratch/nonmatching/T-157/fast.py')
f = importlib.util.module_from_spec(spec); spec.loader.exec_module(f)
fn = sys.argv[1]
t = Counter(l.split()[0] for l in f.target(fn))
for p in sys.argv[2:]:
    d = Counter(l.split()[0] for l in f.compile_raw(fn, Path(p).read_text()))
    diff = {k: d[k] - t[k] for k in set(t) | set(d) if d[k] != t[k]}
    print(p.split('/')[-1], sum(abs(v) for v in diff.values()) // 2, ' '.join(f'{k}:{v:+d}' for k, v in sorted(diff.items(), key=lambda kv: -abs(kv[1]))))
