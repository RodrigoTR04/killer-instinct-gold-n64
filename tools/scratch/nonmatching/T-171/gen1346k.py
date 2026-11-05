#!/usr/bin/env python3
"""func_8001346C: reduce the frame from 0x68/0x70 toward the target's 0x58.

Target spills exactly three words: part at 0x44, mode at 0x50, i at 0x54, and
keeps the six float args at 0x10..0x28. Anything else in the draft is extra
live range. Try: block-scoped i, no cached palette, fewer cursors.
"""
from pathlib import Path
OUT = Path('/tmp/v1346k')
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

# k1: i block-scoped in the palette block, mode used as the case index
BODY_K1 = '''void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {
    T033DrawPart *part;
    T033RenderCommand *g;
    s32 palette, mode, i;
    part = &((T033DrawPart *)D_8004A4C0)[arg1];
    palette = part->flags & 0xF0;
    if (palette >= 16) {
        s32 n;
        palette = (palette - 16) >> 4;
        {
            u8 *src = (u8 *) &D_8004AC98[palette];
            u8 *dst = D_8004AC8E;
            for (n = 0; n != 3; n++) *dst++ = src[n];
        }
        {
            u8 *src = (u8 *) &D_8004ACB0[palette];
            u8 *dst = D_8004AC92;
            for (n = 0; n != 3; n++) *dst++ = src[n];
        }
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    i = 0;
    switch (mode) {
    case 4:
        if (D_800698C4 == 0) break;
    case 0:
        if (part->display != 0) {
            g = (*arg0)++;
            g->command = 0x06000000;
            g->value = (u32)part->display;
        }
        break;
    case 1: break;
    case 2: i = 1; break;
    case 3: func_80028A00(arg0, part->transform); break;
    case 5: func_8001BDE0((u8 **)arg0, arg1, arg2); break;
    }
    if (mode == 1 || mode == 2) {
        if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1;
        palette = part->transform;
        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);
        D_8004A984 = 0;
    }
    if ((part->flags & 0xF0) >= 16) {
        u8 *a = D_8004AC92, *b = D_8004AC8E;
        do { *a++ = 0; *b++ = 0; } while (a != D_8004AC92 + 3);
        func_8001BB64(arg0);
    }
}
'''

# k2: one shared cursor pair, no separate src/dst blocks
BODY_K2 = '''void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {
    T033DrawPart *part;
    T033RenderCommand *g;
    s32 palette, mode, i;
    u8 *a, *b;
    part = &((T033DrawPart *)D_8004A4C0)[arg1];
    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        i = 0;
        do { D_8004AC8E[i] = a[i]; D_8004AC92[i] = b[i]; i++; } while (i != 3);
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    switch (mode) {
    case 4:
        if (D_800698C4 == 0) break;
    case 0:
        if (part->display != 0) {
            g = (*arg0)++;
            g->command = 0x06000000;
            g->value = (u32)part->display;
        }
        break;
    case 1: i = 0; break;
    case 2: i = 1; break;
    case 3: func_80028A00(arg0, part->transform); break;
    case 5: func_8001BDE0((u8 **)arg0, arg1, arg2); break;
    }
    if (mode == 1 || mode == 2) {
        if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1;
        palette = part->transform;
        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);
        D_8004A984 = 0;
    }
    if ((part->flags & 0xF0) >= 16) {
        a = D_8004AC92; b = D_8004AC8E;
        do { *a++ = 0; *b++ = 0; } while (a != D_8004AC92 + 3);
        func_8001BB64(arg0);
    }
}
'''

# k3: no i at all outside the switch (separate mode index local)
BODY_K3 = '''void func_8001346C(T033RenderCommand **arg0, u8 arg1, f32 arg2) {
    T033DrawPart *part;
    T033RenderCommand *g;
    s32 palette, mode, i;
    u8 *a, *b;
    part = &((T033DrawPart *)D_8004A4C0)[arg1];
    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = (u8 *) &D_8004AC98[palette];
        b = (u8 *) &D_8004ACB0[palette];
        for (i = 0; i != 3; i++) { D_8004AC8E[i] = a[i]; D_8004AC92[i] = b[i]; }
        func_8001BB64(arg0);
    }
    mode = part->flags & 15;
    i = 0;
    if (mode == 2) i = 1;
    switch (mode) {
    case 4:
        if (D_800698C4 == 0) break;
    case 0:
        if (part->display != 0) {
            g = (*arg0)++;
            g->command = 0x06000000;
            g->value = (u32)part->display;
        }
        break;
    case 1: break;
    case 2: break;
    case 3: func_80028A00(arg0, part->transform); break;
    case 5: func_8001BDE0((u8 **)arg0, arg1, arg2); break;
    }
    if (mode == 1 || mode == 2) {
        if (D_8004AC88 == 8 && part == (T033DrawPart *)&D_8004A5D4) D_8004A984 = 1;
        palette = part->transform;
        func_8001C5AC(arg0, i, part->display, 0, 0, D_8004A740[palette], (&D_8004A7A0)[palette], D_8004A800[palette], D_8004A860[palette], D_8004A8C0[palette], D_8004A920[palette], 0);
        D_8004A984 = 0;
    }
    if ((part->flags & 0xF0) >= 16) {
        a = D_8004AC92; b = D_8004AC8E;
        do { *a++ = 0; *b++ = 0; } while (a != D_8004AC92 + 3);
        func_8001BB64(arg0);
    }
}
'''

for k, body in (('k1', BODY_K1), ('k2', BODY_K2), ('k3', BODY_K3)):
    (OUT / f'{k}.c').write_text(HEAD + body)
print(3)
