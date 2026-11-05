#!/usr/bin/env python3
"""func_801C1990 round 15: block-scoped row pointers, one block per update."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990o')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

ROWS = {
'direct': {
 3: "            if (D_80128328[player][character] < (u32) stats[3]) D_80128328[player][character] = stats[3];\n",
 1: "            if (D_80128310[player][character] < (u32) stats[1]) D_80128310[player][character] = stats[1];\n",
 4: "            if (D_80128328[player][character] < (u32) stats[4]) D_80128328[player][character] = stats[4];\n",
 2: "            if (D_80128310[player][character] < (u32) stats[2]) D_80128310[player][character] = stats[2];\n",
},
'blockptr': {
 3: """            { u8 *row = &D_80128328[player][character];
              if (*row < (u32) stats[3]) *row = stats[3]; }
""",
 1: """            { u8 *row = &D_80128310[player][character];
              if (*row < (u32) stats[1]) *row = stats[1]; }
""",
 4: """            { u8 *row = &D_80128328[player][character];
              if (*row < (u32) stats[4]) *row = stats[4]; }
""",
 2: """            { u8 *row = &D_80128310[player][character];
              if (*row < (u32) stats[2]) *row = stats[2]; }
""",
},
'value': {
 3: "            value = stats[3];\n            if (D_80128328[player][character] < value) D_80128328[player][character] = value;\n",
 1: "            value = stats[1];\n            if (D_80128310[player][character] < value) D_80128310[player][character] = value;\n",
 4: "            value = stats[4];\n            if (D_80128328[player][character] < value) D_80128328[player][character] = value;\n",
 2: "            value = stats[2];\n            if (D_80128310[player][character] < value) D_80128310[player][character] = value;\n",
},
}

def build(rows, chained):
    s = [HEAD, 'u8 func_801C1990(s32 *stats) {\n']
    s.append('    s32 result;\n    s32 mask;\n    s32 player;\n    s32 value;\n    s32 pending;\n    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    if chained:
        s.append('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n')
    else:
        s.append('    pending = D_802D37FC = (3 - stats[0]) & mask;\n')
    s.append('    if (pending == 3) {\n')
    s.append('        result = func_801C17D0((u32 *)stats, 0);\n')
    s.append('        result |= func_801C17D0((u32 *)stats, 1) * 2;\n')
    s.append('        D_802D37FC = 0;\n        return result & 255;\n    }\n')
    s.append('    if (pending > 0) {\n')
    s.append('        func_801C17D0((u32 *)stats, (pending - 1) & 255);\n')
    s.append('        pending = D_802D37FC;\n    }\n')
    s.append('    if (D_802D37FD > 0) {\n')
    s.append('        character = D_8004EA9B[D_802D37FD];\n        D_802D37FD -= 1;\n        player = D_802D37FD;\n')
    s.append('        value = stats[6];\n')
    s.append('        if (value < (u32) D_80127C30[player]) D_80127C30[player] = value;\n')
    s.append('        if (player == 0) {\n')
    s.append(rows[3]); s.append(rows[1])
    s.append('        } else {\n')
    s.append(rows[4]); s.append(rows[2])
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for rk, rows in ROWS.items():
    for chained in (True, False):
        (OUT / f'{rk}_{int(chained)}.c').write_text(build(rows, chained))
        n += 1
# mixed: direct for the player==0 arm, blockptr for else
for chained in (True, False):
    mixed = dict(ROWS['direct'])
    mixed[4] = ROWS['blockptr'][4]
    mixed[2] = ROWS['blockptr'][2]
    (OUT / f'mix_{int(chained)}.c').write_text(build(mixed, chained))
    n += 1
print(n)
