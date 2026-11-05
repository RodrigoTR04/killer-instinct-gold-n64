#!/usr/bin/env python3
"""Generate func_801C1990 source variants and write them to /tmp/v1990."""
import itertools, os, sys
from pathlib import Path
OUT = Path('/tmp/v1990')
OUT.mkdir(exist_ok=True)

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

def body(statstype, pendingdecl, pendingassign, test, playertype, valtype, charfirst, retform):
    s = []
    s.append(f'u8 func_801C1990({statstype} stats) {{\n')
    s.append('    s32 result;\n    s32 mask;\n')
    s.append(f'    {playertype} player;\n')
    if valtype: s.append(f'    {valtype} value;\n')
    s.append(f'    {pendingdecl}\n')
    s.append('    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    s.append('    D_802D37FC = (3 - stats[0]) & mask;\n')
    if pendingassign: s.append(f'    {pendingassign}\n')
    s.append(f'    if ({test}) {{\n')
    s.append('        result = func_801C17D0((u32 *)stats, 0);\n')
    s.append('        result |= func_801C17D0((u32 *)stats, 1) * 2;\n')
    s.append('        D_802D37FC = 0;\n')
    s.append('        return result & 255;\n    }\n')
    s.append('    if (pending > 0) {\n')
    s.append('        func_801C17D0((u32 *)stats, (pending - 1) & 255);\n')
    s.append('        pending = D_802D37FC;\n    }\n')
    s.append('    if (D_802D37FD > 0) {\n')
    if charfirst:
        s.append('        character = D_8004EA9B[D_802D37FD];\n')
        s.append('        D_802D37FD -= 1;\n')
        s.append('        player = D_802D37FD;\n')
    else:
        s.append('        player = D_802D37FD - 1;\n')
        s.append('        D_802D37FD = player;\n')
        s.append('        character = D_8004EA9B[player];\n')
    if valtype:
        s.append('        value = stats[6];\n')
    else:
        s.append('        value = stats[6];\n')
    s.append('        if (value < (u32)D_80127C30[player]) D_80127C30[player] = value;\n')
    s.append('        if (player == 0) {\n')
    s.append('            value = stats[3];\n')
    s.append('            if (D_80128328[player][character] < value) D_80128328[player][character] = value;\n')
    s.append('            value = stats[1];\n')
    s.append('            if (D_80128310[player][character] < value) D_80128310[player][character] = value;\n')
    s.append('        } else {\n')
    s.append('            value = stats[4];\n')
    s.append('            if (D_80128328[player][character] < value) D_80128328[player][character] = value;\n')
    s.append('            value = stats[2];\n')
    s.append('            if (D_80128310[player][character] < value) D_80128310[player][character] = value;\n')
    s.append('        }\n')
    s.append('        D_8012830A[player]++;\n')
    s.append('        if (stats[5]) D_80128308[player]++;\n')
    s.append('        D_802D37FD = player + 1;\n    }\n')
    s.append(f'    {retform}\n')
    s.append('}\n')
    return ''.join(s)

n = 0
for statstype in ('s32 *', 'u32 *'):
    for pendingdecl in ('s32 pending;', 'u8 pending;', 'u32 pending;'):
        for pendingassign in ('pending = D_802D37FC;', 'pending = (3 - stats[0]) & mask;'):
            for test in ('pending == 3', '(u8)pending == 3', 'D_802D37FC == 3'):
                for playertype in ('s32', 'u8'):
                    for valtype in ('u32', 's32'):
                        for charfirst in (True, False):
                            tag = f'{statstype[0]}_{pendingdecl.split()[0]}_{"g" if "D_802D" in pendingassign else "e"}_{test.replace(" ","").replace("(","p").replace(")","")}_{playertype}_{valtype}_{int(charfirst)}'
                            src = HEAD + body(statstype, pendingdecl, pendingassign, test, playertype, valtype, charfirst,
                                              'if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n    return 0;')
                            (OUT / f'{tag}.c').write_text(src)
                            n += 1
print(n)
