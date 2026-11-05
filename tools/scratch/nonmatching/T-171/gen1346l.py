#!/usr/bin/env python3
"""func_8001346C: shrink the frame to 0x58 so a0/a1/a2 land at 0x58/0x5C/0x60.

The target spills only part (0x44), mode (0x50) and i (0x54); everything else
stays in registers. Each extra named local that survives the switch costs a
slot. Try removing g, a, b and the k block in every combination.
"""
import itertools
from pathlib import Path
OUT = Path('/tmp/v1346l')
OUT.mkdir(exist_ok=True)
for f in OUT.glob('*.c'): f.unlink()

HEAD = '''typedef struct { void *display; s16 flags, pad; s32 transform; } T033DrawPart;
extern void *D_8004A4C0[];
extern u8 D_8004A5D4, D_8004AC8E[], D_8004AC92[], D_8004AC95;
extern s8 D_8004A984;
extern u8 D_8004AC88;
extern s32 D_800698C4;
extern f32 D_8004A740[], D_8004A800[], D_8004A860[], D_8004A8C0[], D_8004A920[], D_8004A7A0;
extern void func_8001BB64(T033RenderCommand **);
extern void func_8001BDE0(u8 **, s32, f32);
extern void func_80028A00(T033RenderCommand **, s32);
extern void func_8001C5AC(T033RenderCommand **, s32, void *, s32, s32, f32, f32, f32, f32, f32, f32, s32);
'''

def build(scoped_g, no_ab, scoped_k, copy_style):
    decls = ['    T033DrawPart *part;', '    s32 palette, mode, i;']
    if not scoped_g: decls.append('    T033RenderCommand *g;')
    if not no_ab: decls.append('    u8 *a, *b;')
    copy = {
    'ii': '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) { D_8004AC8E[i] = a[i]; D_8004AC92[i] = b[i]; }
''',
    'ip': '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
''',
    'ii_block': '''        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = ((u8 *) &D_8004AC98[palette])[i];
            D_8004AC92[i] = ((u8 *) &D_8004ACB0[palette])[i];
        }
''',
    }[copy_style]
    if no_ab:
        copy = copy.replace('        a = (u8 *) &D_8004AC98[palette];\n        b = (u8 *) &D_8004ACB0[palette];\n', '')
        copy = copy.replace('a[i]', '((u8 *) &D_8004AC98[palette])[i]').replace('b[i]', '((u8 *) &D_8004ACB0[palette])[i]')
    gstmt = ('            T033RenderCommand *g = (*arg0)++;\n            g->command = 0x06000000;\n            g->value = (u32)part->display;\n'
             if scoped_g else
             '            g = (*arg0)++;\n            g->command = 0x06000000;\n            g->value = (u32)part->display;\n')
    if scoped_k:
        tail = '''        { s32 k = part->transform;
          func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[k], (&D_8004A7A0)[k], D_8004A800[k], D_8004A860[k], D_8004A8C0[k], D_8004A920[k], 0); }
'''
    else:
        tail = '''        palette = part->transform;
        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);
'''
    clear = ('        a = D_8004AC92; b = D_8004AC8E;\n        do { *a++ = 0; *b++ = 0; } while (a != D_8004AC92 + 3);\n'
             if not no_ab else
             '        { u8 *x = D_8004AC92, *y = D_8004AC8E;\n          do { *x++ = 0; *y++ = 0; } while (x != D_8004AC92 + 3); }\n')
    return HEAD + 'void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {\n' + '\n'.join(decls) + f'''
    part = &((T033DrawPart *)D_8004A4C0)[arg1];
    palette = part->flags & 0xF0;
    if (palette >= 16) {{
        palette = (palette - 16) >> 4;
{copy}        func_8001BB64(arg0);
    }}
    mode = part->flags & 15;
    switch (mode) {{
    case 4:
        if (D_800698C4 == 0) break;
    case 0:
        if (part->display != 0) {{
{gstmt}        }}
        break;
    case 1: i = 0; break;
    case 2: i = 1; break;
    case 3: func_80028A00(arg0, part->transform); break;
    case 5: func_8001BDE0((u8 **)arg0, arg1, arg2); break;
    }}
    if (mode == 1 || mode == 2) {{
        if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1;
{tail}        D_8004A984 = 0;
    }}
    if ((part->flags & 0xF0) >= 16) {{
{clear}        func_8001BB64(arg0);
    }}
}}
'''

n = 0
for sg, na, sk in itertools.product((False, True), repeat=3):
    for cs in ('ii', 'ip'):
        if na and cs == 'ip': continue
        tag = f'g{int(sg)}{"noab" if na else "ab"}{"k" if sk else "p"}{cs}'
        (OUT / f'{tag}.c').write_text(build(sg, na, sk, cs))
        n += 1
print(n)
