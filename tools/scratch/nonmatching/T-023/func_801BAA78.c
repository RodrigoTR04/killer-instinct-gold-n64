/* T-138 DRAFT: 15 differing words, 884/884 B; scale and command cursor follow matched siblings. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BAA78;
typedef struct { u32 w0, w1; } T023GfxBAA78;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3A50[];
extern u8 D_801F3A58[];
extern u8 D_801F3A5C[];

void func_801BAA78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BAA78 *arg4, s32 arg5) {
    s32 *counter;
    T023GfxBAA78 **dl;
    s32 x1;
    s32 y1;
    s32 x0;
    T023GfxBAA78 *g;
    s32 yOffsetScaled;
    s32 y0;
    x0 = (arg1 * 4) + ((s32)(((arg5 * 0x16) + 0x165) * arg4->scale) >> 0xA);
    arg3 = arg2 * 4;
    yOffsetScaled = arg4->yOffset * 4; y0 = arg3 + ((s32)(arg4->scale * 0xB4) >> 0xA) + yOffsetScaled;
    x1 = (arg1 * 4) + ((s32)(((arg5 * 0x13) + 0x71) * arg4->scale) >> 0xA);
    y1 = arg3 + ((s32)(arg4->scale * 0x350) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    counter = &D_801F3A50[arg5];
    if (++*counter >= 0x22) *counter = 0;
    if (*counter >= 0x14) {
        func_801BC1B0(arg0, *(s32 *)(D_801F3A58 + (((s32)(*counter - 0x14) >> 1) * 8)), 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32)x0, (f32)y0, (s32)(arg4->scale * 4) / 3, arg5);
    } else {
        func_801BC1B0(arg0, *(s32 *)D_801F3A58, 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32)x0, (f32)y0, (s32)(arg4->scale * 4) / 3, arg5);
    }
    dl = (T023GfxBAA78 **)arg0;
    g = *dl; *dl = g + 1;
    g->w0 = 0xFCFFFFFF; g->w1 = 0xFFFCF279;
    g = *dl; *dl = g + 1;
    g->w0 = 0xF9000000; g->w1 = 0xFA;
    g = *dl; *dl = g + 1;
    g->w0 = 0xB9000002;
    g->w1 = 1;
    func_801BC1B0(arg0, *(s32 *)(D_801F3A5C + (((s32)*counter >> 2) * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32)x1, (f32)y1, (s32)(arg4->scale * 4) / 3, arg5);
    g = *dl; *dl = g + 1;
    g->w1 = 0;
    g->w0 = 0xB9000002;
}
