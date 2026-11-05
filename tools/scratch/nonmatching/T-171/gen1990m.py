#!/usr/bin/env python3
"""func_801C1990 round 13: per-row choice of value-local vs direct stats read."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990m')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

def row(arr, idx, direct):
    if direct:
        return f"            if ({arr}[player][character] < (u32) stats[{idx}]) {arr}[player][character] = stats[{idx}];\n"
    return (f"            value = stats[{idx}];\n"
            f"            if ({arr}[player][character] < value) {arr}[player][character] = value;\n")

def build(d0, d3, d1, d4, d2, playertype, valtype):
    s = [HEAD, 'u8 func_801C1990(s32 *stats) {\n']
    s.append('    s32 result;\n    s32 mask;\n')
    s.append(f'    {playertype} player;\n    {valtype} value;\n    s32 pending;\n    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    s.append('    value = (3 - stats[0]) & mask;\n')
    s.append('    pending = D_802D37FC = value;\n')
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
    s.append(row('D_80128328', 3, d3))
    s.append(row('D_80128310', 1, d1))
    s.append('        } else {\n')
    s.append(row('D_80128328', 4, d4))
    s.append(row('D_80128310', 2, d2))
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for combo in itertools.product((False, True), repeat=4):
    for playertype in ('s32', 'u8', 'u32'):
        for valtype in ('u32', 's32'):
            d3, d1, d4, d2 = combo
            tag = ''.join('d' if c else 'v' for c in combo) + f'_{playertype}_{valtype[0]}'
            (OUT / f'{tag}.c').write_text(build(False, d3, d1, d4, d2, playertype, valtype))
            n += 1
print(n)
