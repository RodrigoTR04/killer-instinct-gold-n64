#!/usr/bin/env python3
"""func_801C1990 round 14: micro-variants on the 89-word base."""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990n')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801C1990.c').read_text()
import os
os.chdir('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-c6fa874a')
BASE = Path('tools/scratch/nonmatching/T-171/func_801C1990.c').read_text()

HEAD, BODY = BASE.split('u8 func_801C1990(s32 *stats) {')

TESTS = {
't1': '    if (pending == 3) {',
't2': '    if (D_802D37FC == 3) {',
't3': '    if (3 == pending) {',
't4': '    if ((u8) pending == 3) {',
}
ASGS = {
'a1': '    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n',
'a2': '    pending = D_802D37FC = 3 - (stats[0] & mask);\n',
'a3': '    value = 3 - stats[0];\n    pending = D_802D37FC = value & mask;\n',
'a4': '    pending = D_802D37FC = (3 - stats[0]) & mask;\n',
'a5': '    value = (3 - stats[0]) & mask;\n    D_802D37FC = value;\n    pending = value;\n',
'a6': '    value = (3 - stats[0]) & mask;\n    D_802D37FC = pending = value;\n',
}
TAILS = {
'z1': '    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n    return 0;\n',
'z2': '    if (pending > 0 && D_802D3800[pending - 1] != 0) return (u8) pending;\n    return 0;\n',
'z3': '    if (pending > 0 && ((u32 *) D_802D3800)[2 * pending - 2] != 0) return pending;\n    return 0;\n',
'z4': '    if (pending > 0) return D_802D3800[pending - 1] != 0 ? pending : 0;\n    return 0;\n',
}
RETS = {
'r1': '        return result & 255;',
'r2': '        return (u8) result;',
'r3': '        return result;',
}

BASE_BODY = BASE.split('u8 func_801C1990(s32 *stats) {')[1]

def variants():
    for tk, t in TESTS.items():
        for ak, a in ASGS.items():
            b = BASE_BODY.replace('    if (pending == 3) {', t)
            b = b.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n', a)
            yield f'{tk}_{ak}', b
    for tk, t in TESTS.items():
        for zk, z in TAILS.items():
            b = BASE_BODY.replace('    if (pending == 3) {', t)
            b = b.replace('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n    return 0;\n', z)
            yield f'{tk}_{zk}', b
    for rk, r in RETS.items():
        for zk, z in TAILS.items():
            b = BASE_BODY.replace('        return result & 255;', r)
            b = b.replace('    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;\n    return 0;\n', z)
            yield f'{rk}_{zk}', b

n = 0
for tag, b in variants():
    (OUT / f'{tag}.c').write_text(HEAD + 'u8 func_801C1990(s32 *stats) {' + b)
    n += 1
print(n)
