#!/usr/bin/env python3
"""func_801B0668: state byte as a struct member / union alias.

The target never hoists the byte's address: it emits `lui $v1, %hi(sym)` then
`lbu $v1, %lo(sym)($v1)`, or `lui $at` + `sb %lo($at)`, at each of six sites.
Try spellings that defeat address CSE honestly.
"""
from pathlib import Path
OUT = Path('/tmp/v0668i')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()
DECL = 'extern u8 D_801D2FC0;\n'
assert DECL in BASE

V = {}
# i1: union alias over the same address
V['u1'] = BASE.replace(DECL, 'typedef union { u8 b; s8 sb; } StateByte;\nextern StateByte D_801D2FC0;\n')
V['u1'] = V['u1'].replace('D_801D2FC0', 'D_801D2FC0.b')
V['u1'] = V['u1'].replace('extern StateByte D_801D2FC0.b;', 'extern StateByte D_801D2FC0;')
# i2: struct with one member
V['u2'] = BASE.replace(DECL, 'typedef struct { u8 state; } StateByte;\nextern StateByte D_801D2FC0;\n')
V['u2'] = V['u2'].replace('D_801D2FC0', 'D_801D2FC0.state')
V['u2'] = V['u2'].replace('extern StateByte D_801D2FC0.state;', 'extern StateByte D_801D2FC0;')
# i3: s8 instead of u8
V['u3'] = BASE.replace(DECL, 'extern s8 D_801D2FC0;\n')
# i4: second symbol alias at the same address, declared after a blank line each use
V['u4'] = BASE.replace(DECL, 'extern u8 D_801D2FC0;\nextern u8 D_801D2FC4[];\n')

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
