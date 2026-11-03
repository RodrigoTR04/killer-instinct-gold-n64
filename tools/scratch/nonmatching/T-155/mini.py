#!/usr/bin/env python3
"""usage: mini.py file.c [func] -> compile standalone (with common.h) and print the asm of func (or all)"""
import sys, subprocess, tempfile
sys.path.insert(0, '.')
import lib
cm = lib.cm
src = '#include "common.h"\n' + open(sys.argv[1]).read()
with tempfile.TemporaryDirectory(prefix='mini-') as d:
    from pathlib import Path
    o = cm.compile_source(src, Path(d) / 'm.c')
    out = subprocess.run([str(cm.OBJDUMP), '-dr', '--no-show-raw-insn', str(o)], capture_output=True, text=True).stdout
print(out)
