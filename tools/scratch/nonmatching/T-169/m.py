#!/usr/bin/env python3
"""m.py FN DRAFT... : official full-TU count + masked/unmasked alignment."""
import importlib.util, sys, os, subprocess
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
fn = sys.argv[1]
for d in sys.argv[2:]:
    r = dict(screen.measure(fn, Path(d)))
    print(f"{d} {r['compiled']}/{r['original']} words={r['words']} ctx={r['context']}")
