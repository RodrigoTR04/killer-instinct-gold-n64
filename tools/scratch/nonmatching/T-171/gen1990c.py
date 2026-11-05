#!/usr/bin/env python3
"""Round 3: avoid the cast temporary by giving the callee a void* parameter."""
from pathlib import Path
OUT = Path('/tmp/v1990c')
OUT.mkdir(exist_ok=True)

def build(prototype, argtext, statstype, pendingdecl, pendassign, cmptest, ret):
    s = ['#include "frontend.h"\n', prototype, '\n']
    s.append('extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;\n')
    s.append('extern s32 D_80127C30[];\n')
    s.append('extern u8 D_80128308[], D_8012830A[];\n')
    s.append('extern u64 D_802D3800[];\n')
    s.append(f'u8 func_801C1990({statstype} stats) {{\n')
    s.append('    s32 result;\n    s32 mask;\n    s32 player;\n    u32 value;\n')
    if pendingdecl: s.append(f'    {pendingdecl}\n')
    s.append('    u8 character;\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append('    if (!stats[6]) stats[6] = 100;\n')
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append('    D_802D37FD = stats[0] & mask;\n')
    s.append(f'    D_802D37FC = (3 - stats[0]) & mask;\n')
    if pendassign: s.append(f'    {pendassign}\n')
    s.append(f'    if ({cmptest}) {{\n')
    s.append(f'        result = func_801C17D0({argtext}, 0);\n')
    s.append(f'        result |= func_801C17D0({argtext}, 1) * 2;\n')
    s.append('        D_802D37FC = 0;\n')
    s.append('        return result & 255;\n    }\n')
    s.append('    if (pending > 0) {\n')
    s.append(f'        func_801C17D0({argtext}, (pending - 1) & 255);\n')
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
    s.append(ret)
    s.append('}\n')
    return ''.join(s)

n = 0
protos = [
    'extern s32 func_801C17D0(void *, u8);',
    'extern s32 func_801C17D0(u32 *, u8);',
    'extern s32 func_801C17D0(s32 *, u8);',
    'extern s32 func_801C17D0(void *);',
]
for pi, proto in enumerate(protos):
    for si, statstype in enumerate(('s32 *', 'u32 *')):
        for penddecl, pendassign, cmp in (
            ('s32 pending;', 'pending = D_802D37FC;', 'pending == 3'),
            ('s32 pending;', 'pending = (3 - stats[0]) & mask;', 'pending == 3'),
            ('u32 pending;', 'pending = D_802D37FC;', 'pending == 3'),
            ('s32 pending;', 'pending = D_802D37FC;', '(u8)pending == 3'),
        ):
            for ret in (
                '    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n    return 0;\n',
            ):
                tag = f'p{pi}_s{si}_{penddecl[:3]}_{"g" if "FC;" in pendassign else "e"}_{"c" if "u8" in cmp else "p"}'
                (OUT / f'{tag}.c').write_text(build(proto, 'stats', statstype, penddecl, pendassign, cmp, ret))
                n += 1
print(n)
