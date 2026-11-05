#!/usr/bin/env python3
"""func_801BCB70: source line layout inside the display-list commands.

The sibling func_801C3E40 matched by writing its two command words on one
source line. Try a few layouts for the F5/E6/F4 run, where the target stores
w1 before w0 for some commands and w0 before w1 for others.
"""
import re
from pathlib import Path
OUT = Path('/tmp/vbcb70f')
OUT.mkdir(Exist_ok=True) if False else OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

# the whole F5..B2 run in the draft is on one giant line starting at "GCMD(g++, _SHIFTL(0xF5"
lines = BASE.splitlines(keepends=True)
i = next(n for n, l in enumerate(lines) if '0xF5' in l)
print('run starts at line', i)
print(repr(lines[i][:120]))

# variant: split that run into one GCMD per line
big = lines[i]
cmds = re.findall(r'GCMD\(g\+\+, .*?\);', big, re.S)
print('cmds found', len(cmds))
if len(cmds) >= 6:
    pre = big.split(cmds[0])[0]
    post = big.split(cmds[-1])[-1]
    one_per_line = pre + '\n'.join('                        ' + c for c in cmds) + post
    newlines = lines[:i] + [one_per_line] + lines[i+1:]
    (OUT / 'oneper.c').write_text(''.join(newlines))
    # variant: one per line, indented like the surrounding code
    (OUT / 'oneper2.c').write_text(''.join(newlines))
print('ok')
