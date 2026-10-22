/* T-130: separate y0 (scale*0xB4) and y1 (scale*0x350); matched-sibling Gfx cursor. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BAA78;
typedef struct { u32 w0, w1; } T023GfxBAA78;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3A50[];
extern u8 D_801F3A58[];
extern u8 D_801F3A5C[];

void func_801BAA78(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BAA78 *arg4, s32 arg5) {
    T023GfxBAA78 **dl;
    T023GfxBAA78 *g;
    s32 *counter;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 frame;
    u16 scale;

    scale = arg4->scale;
    x0 = (arg1 * 4) + ((s32)(((arg5 * 0x16) + 0x165) * scale) >> 0xA);
    y0 = (arg2 * 4) + ((s32)(scale * 0xB4) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32)(((arg5 * 0x13) + 0x71) * scale) >> 0xA);
    y1 = (arg2 * 4) + ((s32)(scale * 0x350) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    counter = &D_801F3A50[arg5];
    frame = *counter + 1;
    *counter = frame;
    if (frame >= 0x22) {
        *counter = 0;
        frame = 0;
    }
    if (frame >= 0x14) {
        func_801BC1B0(arg0, *(s32 *)(D_801F3A58 + (((s32)(frame - 0x14) >> 1) * 8)), 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32)x0, (f32)y0, (s32)(arg4->scale * 4) / 3, arg5);
    } else {
        func_801BC1B0(arg0, *(s32 *)D_801F3A58, 2, 0x20, 0x12, 0x20, 0x12, 0, 0, 0x1F, 0x11, (f32)x0, (f32)y0, (s32)(arg4->scale * 4) / 3, arg5);
    }
    dl = (T023GfxBAA78 **)arg0;
    g = (*dl)++;
    g->w0 = 0xFCFFFFFF;
    g->w1 = 0xFFFCF279;
    g = (*dl)++;
    g->w0 = 0xF9000000;
    g->w1 = 0xFA;
    g = (*dl)++;
    g->w0 = 0xB9000002;
    g->w1 = 1;
    func_801BC1B0(arg0, *(s32 *)(D_801F3A5C + (((s32)*counter >> 2) * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32)x1, (f32)y1, (s32)(arg4->scale * 4) / 3, arg5);
    g = (*dl)++;
    g->w0 = 0xB9000002;
    g->w1 = 0;
}
