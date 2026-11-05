#!/usr/bin/env python3
"""func_801BCB70: block-scoped display-list pointers per command (sibling lever)."""
from pathlib import Path
OUT = Path('/tmp/vbcb70e')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-162/func_801BCB70.c').read_text()

# T-167's lever: each command gets its own block-scoped pointer taken from g++;
# the target stores w1 then w0 for the first command, w0 then w1 for the rest.
V = {}
V['base'] = BASE

# p1: split the two big GCMD runs onto separate lines, w1 first for cmd 1
V['p1'] = BASE.replace(
    "GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);",
    "GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);")

# p2: write the w1 before w0 for the texture-load commands by using a body block
V['p2'] = BASE.replace(
    "GCMD(g++, _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12), tex);",
    "{ T157Gfx *_g = g++; _g->w1 = tex; _g->w0 = _SHIFTL(0xFD, 24, 8) | _SHIFTL(2, 21, 3) | _SHIFTL(1, 19, 2) | _SHIFTL(texW - 1, 0, 12); }")

# p3: every GCMD as its own block with an explicit pointer
import re
def blockify(text):
    def rep(m):
        return '{ T157Gfx *_q = g++; _q->w0 = ' + m.group(1) + '; _q->w1 = ' + m.group(2) + '; }'
    return re.sub(r'GCMD\(g\+\+, ([^;]*?), ([^;]*?)\);', rep, text)
V['p3'] = blockify(BASE)

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
