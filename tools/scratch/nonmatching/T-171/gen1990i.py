#!/usr/bin/env python3
"""func_801C1990 round 9: vary the stat-row comparison signedness/order."""
from pathlib import Path
OUT = Path('/tmp/v1990i')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

# comparison of one stat row
CMP = {
'c1': "if ({arr}[player][character] < value) {arr}[player][character] = value;",
'c2': "if ({arr}[player][character] < (u8) value) {arr}[player][character] = value;",
'c3': "if ((u32) {arr}[player][character] < value) {arr}[player][character] = value;",
'c4': "if (value > {arr}[player][character]) {arr}[player][character] = value;",
'c5': "stat = {arr}[player][character]; if (stat < value) {arr}[player][character] = value;",
}

def build(valtype, cmpk, extra, statstype):
    s = [HEAD, f'u8 func_801C1990({statstype} stats) {{\n']
    s.append('    s32 result;\n    s32 mask;\n    s32 player;\n')
    s.append(f'    {valtype} value;\n    s32 pending;\n    u8 character;\n')
    if 'stat' in cmpk: s.append('    u8 stat;\n')
    if extra: s.append('    u8 *row;\n')
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
    s.append('            value = stats[3];\n')
    s.append('            ' + CMP[cmpk].format(arr='D_80128328') + '\n')
    s.append('            value = stats[1];\n')
    s.append('            ' + CMP[cmpk].format(arr='D_80128310') + '\n')
    s.append('        } else {\n')
    s.append('            value = stats[4];\n')
    s.append('            ' + CMP[cmpk].format(arr='D_80128328') + '\n')
    s.append('            value = stats[2];\n')
    s.append('            ' + CMP[cmpk].format(arr='D_80128310') + '\n')
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for valtype in ('s32', 'u32', 'u16', 'u8'):
    for cmpk in CMP:
        for statstype in ('s32 *', 'u32 *'):
            tag = f'{valtype}_{cmpk}_{statstype[0]}'
            (OUT / f'{tag}.c').write_text(build(valtype, cmpk, False, statstype))
            n += 1
print(n)
