#!/usr/bin/env python3
"""func_801C1990 round 8: broad combinatorial sweep around the 91-word base."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990h')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
'''

def build(d):
    s = [HEAD]
    s.append(f"u8 func_801C1990({d['statstype']} stats) {{\n")
    for decl in d['decls']:
        s.append(f'    {decl}\n')
    s.append(' D_802D3800[0] = 0;\n    D_802D3800[1] = 0;\n')
    s.append(d['stats6'])
    s.append('    mask = D_8004A407 ^ 3;\n')
    s.append(d['fd'])
    s.append(d['fc'])
    s.append(f"    if ({d['test']}) {{\n")
    s.append(d['calls'])
    s.append('        D_802D37FC = 0;\n')
    s.append(d['ret'])
    s.append('    }\n')
    s.append('    if (pending > 0) {\n')
    s.append('        func_801C17D0((u32 *)stats, (pending - 1) & 255);\n')
    s.append(f"        {d['reload']}\n")
    s.append('    }\n')
    s.append('    if (D_802D37FD > 0) {\n')
    s.append('        character = D_8004EA9B[D_802D37FD];\n')
    s.append('        D_802D37FD -= 1;\n')
    s.append('        player = D_802D37FD;\n')
    s.append('        value = stats[6];\n')
    s.append("        if (value < (u32) D_80127C30[player]) D_80127C30[player] = value;\n")
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
    s.append('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n')
    s.append('    return 0;\n}\n')
    return ''.join(s)

declsets = {
 'a': ['s32 result;', 's32 mask;', 's32 player;', 's32 value;', 's32 pending;', 'u8 character;'],
 'b': ['s32 result;', 's32 mask;', 's32 pending;', 's32 player;', 's32 value;', 'u8 character;'],
 'c': ['s32 result;', 's32 mask;', 's32 player;', 's32 pending;', 's32 value;', 'u8 character;'],
 'd': ['s32 result;', 's32 mask;', 'u32 value;', 's32 pending;', 's32 player;', 'u8 character;'],
 'e': ['s32 result;', 's32 mask;', 's32 player;', 'u32 value;', 'u8 pending;', 'u8 character;'],
 'f': ['s32 result;', 's32 mask;', 'u8 pending;', 's32 player;', 'u32 value;', 'u8 character;'],
 'g': ['s32 result;', 's32 mask;', 's32 pending;', 's32 player;', 'u32 value;', 'u8 character;'],
}
fcs = {
 'f1': '    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n',
 'f2': '    pending = (3 - stats[0]) & mask;\n    D_802D37FC = pending;\n',
 'f3': '    value = (3 - stats[0]) & mask;\n    D_802D37FC = pending = value;\n',
 'f4': '    pending = D_802D37FC = (3 - stats[0]) & mask;\n',
 'f5': '    pending = (3 - stats[0]) & mask;\n    D_802D37FC = (3 - stats[0]) & mask;\n',
}
tests = {'t1': 'pending == 3', 't2': '(u8) pending == 3', 't3': 'D_802D37FC == 3'}
callsets = {
 'c1': '        result = func_801C17D0((u32 *)stats, 0);\n        result |= func_801C17D0((u32 *)stats, 1) * 2;\n',
}
rets = {'r1': '        return result & 255;\n'}
reloads = {'l1': 'pending = D_802D37FC;'}

n = 0
for kd, decls in declsets.items():
    for kf, fc in fcs.items():
        for kt, test in tests.items():
            for kst, st in (('s', 's32 *'), ('u', 'u32 *')):
                d = dict(decls=decls, fc=fc, test=test, statstype=st,
                         stats6='    if (!stats[6]) stats[6] = 100;\n',
                         fd='    D_802D37FD = stats[0] & mask;\n',
                         calls=callsets['c1'], ret=rets['r1'], reload=reloads['l1'])
                (OUT / f'{kd}_{kf}_{kt}_{kst}.c').write_text(build(d))
                n += 1
print(n)
