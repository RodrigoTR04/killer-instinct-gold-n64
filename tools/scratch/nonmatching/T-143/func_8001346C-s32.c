/* T-121 DRAFT: 165 differing words; 704/704 bytes. Loop index also carries the transform flag. */
typedef struct { void *display; s16 flags, pad; s32 transform; } T033DrawPart;

extern void *D_8004A4C0[];
extern u8 D_8004A5D4, D_8004AC8E[], D_8004AC92[], D_8004AC95, D_8004AC98[], D_8004ACB0[];
extern s8 D_8004A984;
extern u8 D_8004AC88;
extern s32 D_800698C4;
extern f32 D_8004A740[], D_8004A800[], D_8004A860[], D_8004A8C0[], D_8004A920[], D_8004A7A0;
extern void func_8001BB64(T033RenderCommand **);
extern void func_8001BDE0(T033RenderCommand **, s32, f32);
extern void func_80028A00(T033RenderCommand **, s32);
extern void func_8001C5AC(T033RenderCommand **, s32, void *, s32, s32, f32, f32, f32, f32, f32, f32, s32);

extern f32 D_8004A740[];
extern f32 D_8004A800[];
extern f32 D_8004A860[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
void func_8001346C(T033RenderCommand **arg0, s32 arg1, f32 arg2) {
    T033DrawPart *part;
    T033RenderCommand *g;
    s32 palette, mode, i;
    u8 *a, *b;
    part = &((T033DrawPart *)D_8004A4C0)[arg1];
    palette = part->flags & 0xF0;
    if (palette >= 16) {
        palette = (palette - 16) >> 4;
        a = &D_8004AC98[palette * 3];
        b = &D_8004ACB0[palette * 3];
        for (i = 0; i != 3; i++) {
            D_8004AC8E[i] = a[i];
            D_8004AC92[i] = b[i];
        }
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
    case 5: func_8001BDE0(arg0, arg1, arg2); break;
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
