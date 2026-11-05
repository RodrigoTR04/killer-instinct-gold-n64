#!/usr/bin/env python3
"""func_801BCB70: find the extra local by removing candidates one at a time.

The target frame is 0x138 and the draft frame is also 0x138, but the target
spills bottom-top at 0x94 while the draft spills it at 0x98 - one extra slot
ahead of it. Removing the right local should line every offset up.
"""
import re
from pathlib import Path
OUT = Path('/tmp/vbcb70j')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

LOCALS = ['accX', 'ult', 'i', 'yl', 'cellH', 'lrs', 'y1f', 'rows', 'end', 'y1c',
          'col', 'fy', 'lrt', 'x1c', 'xl', 'x1f', 'dx', 'absDx', 'pos', 'div',
          'bit', 'run', 'flag', 'x0f', 'uls', 'g', 'x']

for name in LOCALS:
    # drop the declaration line
    decl = re.compile(r'^\s*[a-zA-Z0-9]+\s*\**' + re.escape(name) + r';\s*\n', re.M)
    t, n = decl.subn('    s32 unusedSlot;\n' if False else '', BASE, count=1)
    if n != 1:
        continue
    (OUT / f'no_{name}.c').write_text(t)
print(len(list(OUT.glob('*.c'))))
