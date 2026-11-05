#!/usr/bin/env python3
"""func_8001346C: get the u8 index into a1 by using it before any spill."""
from pathlib import Path
OUT = Path('/tmp/v1346e')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

BASE = Path('/tmp/v1346d/base.c').read_text()
HDR = BASE.split('void func_8001346C')[0]
BODY = 'void func_8001346C' + BASE.split('void func_8001346C', 1)[1]

# T1: part pointer computed inside the condition test itself
t = BODY.replace("    part = &((T033DrawPart *) D_8004A4C0)[arg1];\n    palette = part->flags & 0xF0;\n    if (palette >= 16) {",
                 "    palette = ((T033DrawPart *) D_8004A4C0)[arg1].flags & 0xF0;\n    part = &((T033DrawPart *) D_8004A4C0)[arg1];\n    if (palette >= 16) {")
(OUT / 't1.c').write_text(HDR + t)

# T2: two locals, part from arg1 in the initializer, palette from the flags load
t2 = BODY.replace("    part = &((T033DrawPart *) D_8004A4C0)[arg1];\n    palette = part->flags & 0xF0;",
                  "    palette = ((T033DrawPart *) &D_8004A4C0[arg1 * 3 - arg1])->flags & 0xF0;\n    part = (T033DrawPart *) &D_8004A4C0[arg1 * 3 - arg1];")
(OUT / 't2.c').write_text(HDR + t2)

# T3: byte arithmetic on the index expression, exactly as the target
t3 = BODY.replace("    part = &((T033DrawPart *) D_8004A4C0)[arg1];",
                  "    part = (T033DrawPart *) ((u8 *) D_8004A4C0 + ((u32) (arg1 * 3) << 2));")
(OUT / 't3.c').write_text(HDR + t3)

# T4: keep the index in a u8 local used only where the target uses a1
t4 = BODY.replace("void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {",
                  "void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {\n    u8 index = arg1;")
t4 = t4.replace('D_8004A4C0)[arg1]', 'D_8004A4C0)[index]')
t4 = t4.replace('func_8001BDE0((u8 **) arg0, arg1, arg2)', 'func_8001BDE0((u8 **) arg0, index, arg2)')
(OUT / 't4.c').write_text(HDR + t4)
print(4)
