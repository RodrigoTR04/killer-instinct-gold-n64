/* DRAFT. Remaining diff: Alpha/global/display-list temporary registers and store/call scheduling differ; same body size. */
typedef struct { u32 w0, w1; } T025Gfx1210;
extern s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);
extern u8 D_802927F0[];
extern f32 D_80292918;
extern u32 D_802C87C0;
s32 func_801B1210(T025Gfx1210 **arg0, s32 arg1, s32 arg2, s32 arg3) {
    u32 alpha;
    T025Gfx1210 *g;
    if (func_801AF67C(8) != 0) {
        if (D_802C87C0 >= 9U) alpha = D_802C87C0 - 8;
        else return 0;
    } else alpha = arg3 * 16;
    if (alpha >= 0x100U) alpha = 0xFF;
    g = (*arg0)++;
    g->w0 = 0xBA000402;
    g->w1 = 0x30;
    g = (*arg0)++;
    g->w1 = 0;
    g->w0 = 0xB9000002;
    D_802C87C0 = alpha;
    return func_801BE540((s32)arg0, arg2, (s32)D_802927F0, 0, -470.0f, D_80292918, 0x14, 0x28, 0xC8, alpha, 1.0f) & 0xFF;
}
