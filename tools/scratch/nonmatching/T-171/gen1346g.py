#!/usr/bin/env python3
"""func_8001346C: combine the pointer palette copy with the per-array cursor."""
from pathlib import Path
OUT = Path('/tmp/v1346g')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346f/f2.c').read_text()

OLD = """        a = (u8 *)&D_8004AC98[palette];
        b = (u8 *)&D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }"""
assert OLD in BASE
NEW = """        a = (u8 *)&D_8004AC98[palette];
        b = (u8 *)&D_8004ACB0[palette];
        {
            u8 *src = a, *dst = D_8004AC8E;
            u8 *src2 = b, *dst2 = D_8004AC92;
            for (i = 0; i != 3; i++) {
                *dst++ = *src++;
                *dst2++ = *src2++;
            }
        }"""

V = {}
V['g1'] = BASE.replace(OLD, NEW)
V['g2'] = BASE
# g3: per-array cursor without the block (plain statements)
V['g3'] = BASE.replace(
  "        { f32 *a = &D_8004A740[palette], *b = &D_8004A7A0; \n"
  "          func_8001C5AC(arg0, i, part->display, 0, 0, a[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0); }",
  "        a = (u8 *) &D_8004A740[palette];\n"
  "        func_8001C5AC(arg0, i, part->display, 0, 0, (f32) a, (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);")

for k, v in V.items():
    (OUT / f'{k}.c').write_text(v)
print(len(V))
