#!/usr/bin/env python3
"""ctx.py func draft.c [-v]: splice a draft into a copy of its owning TU (other GLOBAL_ASM pragmas dropped) and score."""
import re, sys, subprocess, glob
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
func, draft = sys.argv[1], Path(sys.argv[2])
tu = next(p for p in glob.glob(str(ROOT / 'src/*/*.c')) if f'/{func}.s")' in open(p).read())
s = open(tu).read()
d = draft.read_text().replace('#include "common.h"', '')
s = s.replace(f'#pragma GLOBAL_ASM("asm/nonmatchings/{Path(tu).parent.name}/{Path(tu).stem}/{func}.s")', d)
s = re.sub(r'#pragma GLOBAL_ASM\([^)]*\)', '', s)
out = Path(f'/tmp/ctx_{func}.c'); out.write_text(s)
mips = '--mips1' if 'mips1' in open(ROOT / 'Makefile').read().split(Path(tu).name + '.o')[-1].split('\n')[0] else ''
subprocess.run([sys.executable, str(Path(__file__).parent / 'sc.py'), str(out), func] + ([mips] if mips else []) + sys.argv[3:])
