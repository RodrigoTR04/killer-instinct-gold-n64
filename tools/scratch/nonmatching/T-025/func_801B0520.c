/* T-095 DRAFT: remaining differences recorded in T-095/REPORT.md. */
typedef struct { u32 w0, w1; } T025Gfx0520;
typedef struct { s32 pad; void *list; } T025ListState;
extern void guTranslate(void *, f32, f32, f32);
extern void func_801C3AA0(f32, f32, f32, f32, f32);
extern s32 D_801D2EBC;
extern u8 D_801D2F40[];
extern s32 D_802956F8, D_802956FC, D_80295700;
s32 func_801B0520(T025Gfx0520 **arg0, T025ListState *arg1, void *arg2, s32 arg3)
{
    s32 y;
    s32 frame;
    s32 *frameState;
    T025Gfx0520 *g;
    frame = arg3 * 2;
    if (frame < 230)
    {
        D_801D2EBC = frame;
        guTranslate(arg2, 0.0f, (f32) frame, 0.0f);
        arg1->list = D_801D2F40;
        frameState = &D_801D2EBC;
        if (D_802956F8 >= 16)
        {
            g = (*arg0)++;
            g->w0 = 0xFB000000;
            g->w1 = (((D_802956F8 << 24) | ((D_802956FC & 255) << 16)) | ((D_80295700 & 255) << 8)) | 255;
        }
        else
        {
            g = (*arg0)++;
            g->w1 = 255;
            g->w0 = 0xFB000000;
        }
        if ((*frameState) < 220)
        {
            y = (*frameState) - 105;
            D_801D2EBC = *frameState;
            func_801C3AA0(0.0f, (f32) y, 0.0f, 80.0f, -90.0f);
        }
        return 1;
    }
    D_801D2EBC = frame;
    return 0;
}
