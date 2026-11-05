#!/usr/bin/env python3
"""func_801C1990 round 4: chained assignment so the u8 pending and the u8 store share one expression."""
from pathlib import Path
OUT = Path('/tmp/v1990d')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

def build(pendtype, chain, statstype, tail, playertype, order):
    s = [HEAD, f'u8 func_801C1990({statstype} stats) {{\n']
    s.append('    s32 result;\n    s32 mask;\n')
    s.append(f'    {playertype} player;\n')
    if order == 'valfirst':
        s.append('    u32 value;\n')
    s.append(f'    {pendtype} pending;\n')
    if order == 'vallast':
        s.append('    u32 value;\n')
    s.append('    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    if chain == 'chained':
        s.append('    pending = D_802D37FC = (3 - stats[0]) & mask;\n')
    elif chain == 'chained_store':
        s.append('    pending = (D_802D37FC = (3 - stats[0]) & mask);\n')
    else:
        s.append('    D_802D37FC = (3 - stats[0]) & mask;\n    pending = D_802D37FC;\n')
    s.append('    if (pending == 3) {\n')
    s.append('        result = func_801C17D0((u32 *)stats, 0);\n')
    s.append('        result |= func_801C17D0((u32 *)stats, 1) * 2;\n')
    s.append('        D_802D37FC = 0;\n')
    s.append('        return result & 255;\n    }\n')
    s.append('    if (pending > 0) {\n')
    s.append('        func_801C17D0((u32 *)stats, (pending - 1) & 255);\n')
    s.append('        pending = D_802D37FC;\n    }\n')
    s.append('    if (D_802D37FD > 0) {\n')
    s.append('        character = D_8004EA9B[D_802D37FD];\n')
    s.append('        D_802D37FD -= 1;\n')
    s.append('        player = D_802D37FD;\n')
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
    if tail == 'words':
        s.append('    if (pending > 0 && (D_802D3800[pending - 1] & 0xFFFFFFFF) != 0) return pending;\n')
        s.append('    if (pending > 0 && (D_802D3800[pending - 1] >> 32) != 0) return pending;\n')
    else:
        s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

n = 0
for pendtype in ('u8', 's32', 'u32'):
    for chain in ('chained', 'chained_store', 'plain'):
        for statstype in ('s32 *', 'u32 *'):
            for tail in ('one',):
                for playertype in ('s32', 'u8'):
                    for order in ('valfirst', 'vallast'):
                        tag = f'{pendtype}_{chain}_{statstype[0]}_{tail}_{playertype}_{order}'
                        (OUT / f'{tag}.c').write_text(build(pendtype, chain, statstype, tail, playertype, order))
                        n += 1
print(n)
