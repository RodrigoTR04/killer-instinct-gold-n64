#!/usr/bin/env python3
"""Compile a standalone C file with the game flags and print the disassembly.
usage: mini.py file.c [function]"""
import importlib.util, subprocess, sys, tempfile
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('cmpm', ROOT / 'tools/scratch/nonmatching/T-154/cmp.py')
cm = importlib.util.module_from_spec(spec); spec.loader.exec_module(cm)
src = Path(sys.argv[1]).read_text()
with tempfile.TemporaryDirectory(prefix='mini-') as d:
    o = cm.compile_source('#include "common.h"\n' + src, Path(d) / 'm.c')
    out = subprocess.run([str(cm.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)], capture_output=True, text=True).stdout
print(out)
