#!/usr/bin/env python3
"""func_800297A4: blocks around the first statement after the loop header, and
around the statements that contain the func_800326F0 calls."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v297af')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_800297A4.c').read_text()

CAND = {
# first statement inside the for body = the if/else-if chain head
'c1': ('    for (j = 0; j < 12; j++, angle += 90) {\n        if (j < 4) {\n',
       '    for (j = 0; j < 12; j++, angle += 90) {\n        do { if (j < 4) {\n'),
# the velocity statement (contains a call)
'c2': ('        p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed);\n',
       '        do { p->velocity[j] = (float) (u32) (func_800326F0() % (u32) (speed / 4) + speed); } while (0);\n'),
# the position statement (contains a call)
'c3': ('        p->position[j] = (float) (u32) (func_800326F0() & 15);\n',
       '        do { p->position[j] = (float) (u32) (func_800326F0() & 15); } while (0);\n'),
# the axisX in arm 1 (contains a call)
'c4': ('            p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15));\n',
       '            do { p->axisX[j] = (float) (u32) (7 - (func_800326F0() & 15)); } while (0);\n'),
# the axisZ in arm 1
'c5': ('            p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30);\n',
       '            do { p->axisZ[j] = (float) (u32) ((func_800326F0() & 63) + angle - 30); } while (0);\n'),
# the whole if/else-if chain wrapped (close after the else arm)
'c6': ('    for (j = 0; j < 12; j++, angle += 90) {\n        if (j < 4) {\n',
       '    for (j = 0; j < 12; j++, angle += 90) {\n        do { if (j < 4) {\n'),
}
CLOSE6 = ('            p->flags[j] = 1;\n        }\n',
          '            p->flags[j] = 1;\n        } } while (0);\n')

def build(combo):
    t = BASE
    for c in combo:
        old, new = CAND[c]
        if old not in t:
            return None
        t = t.replace(old, new, 1)
    if 'c6' in combo:
        o, n = CLOSE6
        if o not in t: return None
        t = t.replace(o, n, 1)
    return t

n = 0
keys = ['c1','c2','c3','c4','c5','c6']
for r in (1, 2, 3):
    for combo in itertools.combinations(keys, r):
        if 'c1' in combo and 'c6' in combo: continue
        t = build(combo)
        if t is None: continue
        (OUT / f'{"".join(combo)}.c').write_text(t)
        n += 1
print(n)
