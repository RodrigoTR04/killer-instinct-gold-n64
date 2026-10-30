/* T-138 DRAFT: 27 differing words, 284/284 B. Block-local display commands improve scheduling; alpha allocation remains. */
extern s32 func_801AF67C(s32);
typedef struct { u32 w0, w1; } T025Gfx1210;
extern s32 func_801BE540(s32, s32, s32, f32, f32, f32, s32, s32, s32, s32, f32);


extern u32 D_802C87C0;
s32 func_801B1210(T025Gfx1210 **arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u32 alpha;
    if (func_801AF67C(8) != 0)
    {
        if (D_802C87C0 >= 9U)
        {
            alpha = D_802C87C0 - 8;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        alpha = arg3 * 16;
    }
    if (alpha >= 0x100U)
    {
        alpha = 0xFF;
    }
    { T025Gfx1210 *q = (*arg0)++; q->w0 = 0xBA000402; q->w1 = 0x30; }
    { T025Gfx1210 *q = (*arg0)++; q->w0 = 0xB9000002; q->w1 = 0; }
    D_802C87C0 = alpha;
    return func_801BE540((s32) arg0, arg2, (s32) D_802927F0, 0.0f, -470.0f, -1500.0f, 0x14, 0x28, 0xC8, alpha, 1.0f) & 0xFF;
}
