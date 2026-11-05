#!/usr/bin/env python3
"""func_801C1990 round 16: target the three residual clusters on the 89 base.

Clusters from the regmask diff:
  A. lui/addiu of D_802D37FC is emitted before the bnez, target emits it after.
  B. andi/bne vs bne/andi around the pending==3 test (delay slot).
  C. the second call reloads through a copy of D_802D37FC.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1990p')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801C1990.c').read_text()
HEAD, BODY = BASE.split('u8 func_801C1990(s32 *stats) {', 1)

FIRST = {
'f1': '    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n',
'f2': '    value = (3 - stats[0]) & mask;\n    D_802D37FC = value;\n    pending = value;\n',
'f3': '    pending = (3 - stats[0]) & mask;\n    value = pending;\n    D_802D37FC = value;\n',
'f4': '    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n    mask = mask;\n',
'f5': '    D_802D37FC = pending = (3 - stats[0]) & mask;\n    value = pending;\n',
}
TESTS = {
't1': '    if (pending == 3) {',
't2': '    if (D_802D37FC == 3) {',
't3': '    if (pending == 3 && 1) {',
}
RELOADS = {
'r1': '        pending = D_802D37FC;',
'r2': '        pending = value = D_802D37FC;',
'r3': '        value = D_802D37FC;\n        pending = value;',
'r4': '        pending = (3 - stats[0]) & mask;',
}

def build(fk, tk, rk):
    b = BODY
    b = b.replace('    value = (3 - stats[0]) & mask;\n    pending = D_802D37FC = value;\n', FIRST[fk])
    b = b.replace('    if (pending == 3) {', TESTS[tk])
    b = b.replace('        pending = D_802D37FC;', RELOADS[rk])
    return HEAD + 'u8 func_801C1990(s32 *stats) {' + b

n = 0
for fk in FIRST:
    for tk in TESTS:
        for rk in RELOADS:
            (OUT / f'{fk}_{tk}_{rk}.c').write_text(build(fk, tk, rk))
            n += 1
print(n)
