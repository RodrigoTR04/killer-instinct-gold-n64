#!/usr/bin/env python3
"""func_801C1990 round 10: read stats[] directly in the row updates (no value local)."""
from pathlib import Path
OUT = Path('/tmp/v1990j')
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
'r1': """            if (D_80128328[player][character] < stats[3]) D_80128328[player][character] = stats[3];
            if (D_80128310[player][character] < stats[1]) D_80128310[player][character] = stats[1];
""",
'r2': """            if (D_80128328[player][character] < (u32) stats[3]) D_80128328[player][character] = stats[3];
            if (D_80128310[player][character] < (u32) stats[1]) D_80128310[player][character] = stats[1];
""",
'r3': """            if (stats[3] > D_80128328[player][character]) D_80128328[player][character] = stats[3];
            if (stats[1] > D_80128310[player][character]) D_80128310[player][character] = stats[1];
""",
}
ROWS2 = {
'r1': """            if (D_80128328[player][character] < stats[4]) D_80128328[player][character] = stats[4];
            if (D_80128310[player][character] < stats[2]) D_80128310[player][character] = stats[2];
""",
'r2': """            if (D_80128328[player][character] < (u32) stats[4]) D_80128328[player][character] = stats[4];
            if (D_80128310[player][character] < (u32) stats[2]) D_80128310[player][character] = stats[2];
""",
'r3': """            if (stats[4] > D_80128328[player][character]) D_80128328[player][character] = stats[4];
            if (stats[2] > D_80128310[player][character]) D_80128310[player][character] = stats[2];
""",
}

def build(rowk, firstval, pendtype, statstype):
    s = [HEAD, f'u8 func_801C1990({statstype} stats) {{\n']
    s.append('    s32 result;\n    s32 mask;\n    s32 player;\n')
    if firstval: s.append('    s32 value;\n')
    s.append(f'    {pendtype} pending;\n    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    if firstval:
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
    s.append('        if ((u32) stats[6] < (u32) D_80127C30[player]) D_80127C30[player] = stats[6];\n')
    s.append('        if (player == 0) {\n')
    s.append(ROWS[rowk])
    s.append('        } else {\n')
    s.append(ROWS2[rowk])
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for rowk in ROWS:
    for firstval in (False, True):
        for pendtype in ('s32', 'u8'):
            for statstype in ('s32 *', 'u32 *'):
                tag = f'{rowk}_{int(firstval)}_{pendtype}_{statstype[0]}'
                (OUT / f'{tag}.c').write_text(build(rowk, firstval, pendtype, statstype))
                n += 1
print(n)
