#!/usr/bin/env python3
"""func_801B0668: force the target's `lui` + `lbu %lo` address mode.

The target re-materialises the state byte's address at every use (lui then a
%lo load, no addiu). The draft keeps a full address in a register. Try honest
spellings that change the addressing mode.
"""
from pathlib import Path
OUT = Path('/tmp/v0668f')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_801B0668.c').read_text()

DECLS = {
'd1': 'extern u8 D_801D2FC0;\n',
'd2': 'extern u8 D_801D2FC0[1];\n',
'd3': 'extern u8 D_801D2FC0[2];\n',
}
ACCESS = {
'a1': ('D_801D2FC0', None),
'a2': ('D_801D2FC0[0]', None),
'a3': ('*statep', '    u8 *statep = &D_801D2FC0;\n'),
'a4': ('statep[0]', '    u8 *statep = D_801D2FC0;\n'),
}

for dk, decl in DECLS.items():
    for ak, (use, extra) in ACCESS.items():
        if ak in ('a3', 'a4') and dk != 'd1':
            continue
        t = BASE.replace('extern u8 D_801D2FC0;\n', decl)
        t = t.replace('D_801D2FC0', use)
        if extra:
            t = t.replace('    f64 temp_f2;\n', '    f64 temp_f2;\n' + extra)
        (OUT / f'{dk}_{ak}.c').write_text(t)
print('ok')
