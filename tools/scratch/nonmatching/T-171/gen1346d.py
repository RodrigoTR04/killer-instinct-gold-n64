#!/usr/bin/env python3
"""func_8001346C: keep the ptrloop body but re-read part->flags for the trailing test."""
from pathlib import Path
OUT = Path('/tmp/v1346d')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346c/ptrloop.c').read_text()

V = {}
V['base'] = BASE
# r1: trailing test reads part->flags again (already does); instead re-read for
#     the first test after the palette block
V['r1'] = BASE.replace("    mode = part->flags & 15;",
                       "    mode = ((T033DrawPart *) D_8004A4C0)[arg1].flags & 15;")
# r2: the mode test itself on flags
V['r2'] = BASE.replace("    if (mode == 1 || mode == 2) {",
                       "    if ((part->flags & 15) == 1 || (part->flags & 15) == 2) {")
# r3: the trailing palette test on part->flags (already); use a fresh part
V['r3'] = BASE.replace("    if ((part->flags & 0xF0) >= 16) {\n        a = D_8004AC92; b = D_8004AC8E;",
                       "    part = &((T033DrawPart *) D_8004A4C0)[arg1];\n    if ((part->flags & 0xF0) >= 16) {\n        a = D_8004AC92; b = D_8004AC8E;")
# r4: both clamps read as flags masks
V['r4'] = BASE.replace("    mode = part->flags & 15;", "    mode = part->flags & 0x0F;\n")
# r5: read flags once into a local, then mask
V['r5'] = BASE.replace("    mode = part->flags & 15;",
                       "    palette = part->flags;\n    mode = palette & 15;")
# r6: split declarations (mode after i)
V['r6'] = BASE.replace("    s32 palette, mode, i;", "    s32 palette;\n    s32 mode;\n    s32 i;")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
