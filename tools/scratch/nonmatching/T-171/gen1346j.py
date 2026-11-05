#!/usr/bin/env python3
"""func_8001346C: s32 second parameter (callers pass a promoted u8, so the ABI is
identical) + the target's indexed-source / pointer-dest palette copy."""
from pathlib import Path
OUT = Path('/tmp/v1346j')
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

COPY = {
# indexed source, pointer destination (the target's shape)
'ip': '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *d1 = D_8004AC8E, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = a[i]; *d2++ = b[i]; } }
''',
# both pointer
'pp': '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        { u8 *s1 = a, *d1 = D_8004AC8E, *s2 = b, *d2 = D_8004AC92;
          for (i = 0; i != 3; i++) { *d1++ = *s1++; *d2++ = *s2++; } }
''',
# both indexed (original draft)
'ii': '''        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }
''',
}

TAIL_K = '''        { s32 k = part->transform;
          func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[k], (&D_8004A7A0)[k], D_8004A800[k], D_8004A860[k], D_8004A8C0[k], D_8004A920[k], 0); }
'''
TAIL_P = '''        palette = part->transform;
        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);
'''

def build(copy, tail, param):
    return HEAD + f'''void func_8001346C(T033RenderCommand **arg0, {param} arg1, f32 arg2) {{
    T033DrawPart *part;
    T033RenderCommand *g;
    s32 palette, mode, i;
    u8 *a, *b;
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
            g = (*arg0)++;
            g->command = 0x06000000;
            g->value = (u32)part->display;
        }}
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
        a = D_8004AC92; b = D_8004AC8E;
        do {{ *a++ = 0; *b++ = 0; }} while (a != D_8004AC92 + 3);
        func_8001BB64(arg0);
    }}
}}
'''

n = 0
for ck, copy in COPY.items():
    for tk, tail in (('k', TAIL_K), ('p', TAIL_P)):
        for param in ('u8', 's32'):
            (OUT / f'{ck}_{tk}_{param}.c').write_text(build(copy, tail, param))
            n += 1
print(n)
