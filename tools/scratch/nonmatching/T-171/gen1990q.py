#!/usr/bin/env python3
"""func_801C1990: push below 77 by separating the two stat-row bases."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990q')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

ROWSETS = {
'direct': (
"""            if (D_80128328[player][character] < (u32) stats[3]) D_80128328[player][character] = stats[3];
            if (D_80128310[player][character] < (u32) stats[1]) D_80128310[player][character] = stats[1];
""",
"""            if (D_80128328[player][character] < (u32) stats[4]) D_80128328[player][character] = stats[4];
            if (D_80128310[player][character] < (u32) stats[2]) D_80128310[player][character] = stats[2];
"""),
'cursor': (
"""            { u8 *b = &D_80128328[player][character]; u8 *a = &D_80128310[player][character];
              if (*b < (u32) stats[3]) *b = stats[3];
              if (*a < (u32) stats[1]) *a = stats[1]; }
""",
"""            { u8 *b = &D_80128328[player][character]; u8 *a = &D_80128310[player][character];
              if (*b < (u32) stats[4]) *b = stats[4];
              if (*a < (u32) stats[2]) *a = stats[2]; }
"""),
'rowptr_first': (
"""            { u8 *b = &D_80128328[player][character];
              if (*b < (u32) stats[3]) *b = stats[3];
              b = &D_80128310[player][character];
              if (*b < (u32) stats[1]) *b = stats[1]; }
""",
"""            { u8 *b = &D_80128328[player][character];
              if (*b < (u32) stats[4]) *b = stats[4];
              b = &D_80128310[player][character];
              if (*b < (u32) stats[2]) *b = stats[2]; }
"""),
}

def build(rowsA, rowsB, chained, maskfirst):
    s = [HEAD, 'u8 func_801C1990(s32 *stats) {\n']
    s.append('    s32 result;\n    s32 mask;\n    s32 player;\n    u32 value;\n    s32 pending;\n    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    if maskfirst:
        s.append('    mask = D_8004A407 ^ 3;\n    D_802D37FD = stats[0] & mask;\n')
    else:
        s.append('    D_802D37FD = stats[0] & (D_8004A407 ^ 3);\n    mask = D_8004A407 ^ 3;\n')
    s.append('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n')
    s.append('    if (D_802D37FC == 3) {\n')
    s.append('        result = func_801C17D0((u32 *)stats, 0);\n')
    s.append('        result |= func_801C17D0((u32 *)stats, 1) * 2;\n')
    s.append('        D_802D37FC = 0;\n        return result & 255;\n    }\n')
    s.append('    if (pending > 0) {\n')
    s.append('        func_801C17D0((u32 *)stats, (pending - 1) & 255);\n')
    s.append('        pending = D_802D37FC;\n    }\n')
    s.append('    if (D_802D37FD > 0) {\n')
    s.append('        character = D_8004EA9B[D_802D37FD];\n        D_802D37FD -= 1;\n        player = D_802D37FD;\n')
    s.append('        value = stats[6];\n')
    s.append('        if (D_80127C30[player] > value) D_80127C30[player] = value;\n')
    s.append('        if (player == 0) {\n')
    s.append(rowsA)
    s.append('        } else {\n')
    s.append(rowsB)
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for k, (a, b) in ROWSETS.items():
    for chained in (True,):
        for maskfirst in (True, False):
            (OUT / f'{k}_{int(maskfirst)}.c').write_text(build(a, b, chained, maskfirst))
            n += 1
# mixed: player==0 arm direct, else arm cursor
a, b = ROWSETS['direct'][0], ROWSETS['cursor'][1]
(OUT / 'mix1.c').write_text(build(a, b, True, True))
a, b = ROWSETS['cursor'][0], ROWSETS['direct'][1]
(OUT / 'mix2.c').write_text(build(a, b, True, True))
print(n + 2)
