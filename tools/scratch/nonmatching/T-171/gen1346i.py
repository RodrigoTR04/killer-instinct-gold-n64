#!/usr/bin/env python3
"""func_8001346C: ptrloop base plus the other single-axis levers."""
from pathlib import Path
OUT = Path('/tmp/v1346i')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('tools/scratch/nonmatching/T-171/func_8001346C-ptrloop.c').read_text()

V = {}
V['base'] = BASE
# i1: split the shared declaration list
V['i1'] = BASE.replace('    s32 palette, mode, i;', '    s32 palette;\n    s32 mode;\n    s32 i;')
# i2: mode read through the global expression again
V['i2'] = BASE.replace('    mode = part->flags & 15;',
                       '    mode = ((T033DrawPart *) D_8004A4C0)[arg1].flags & 15;')
# i3: palette local only for the first block
V['i3'] = BASE.replace('    palette = part->flags & 0xF0;\n    if (palette >= 16) {',
                       '    if ((part->flags & 0xF0) >= 16) {\n        palette = part->flags & 0xF0;')
# i4: a/b declared inside the palette block
V['i4'] = BASE.replace('    u8 *a, *b;\n', '').replace(
    '    if (palette >= 16) {\n        palette = (palette - 16) >> 4;',
    '    if (palette >= 16) {\n        u8 *a, *b;\n        palette = (palette - 16) >> 4;')
# i5: i declared in the block that uses it
V['i5'] = BASE.replace('    s32 palette, mode, i;', '    s32 palette, mode;\n    s32 i;')

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
