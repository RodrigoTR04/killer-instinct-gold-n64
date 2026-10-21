/* T-101 DRAFT: 19 differing words; 536 bytes. Not matching.
 * The late branch retains the inherited uninitialized alpha read; scratch only. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx3754;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30D0;
extern s16 D_802C87D0;

s32 func_801B3754(T025Gfx3754 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30D0;
    T025Gfx3754 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    if ((s32) D_801D3088 < 6)
    {
        return 0;
    }
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = color;
        p0 = (*arg0)++;
        p0->w1 = (s32) packed;
        p0->w0 = 0xFA000000;
    }
    else
    {
        *counter = arg1;
        p1 = (*arg0)++;
        color2 = D_802C87D0 & 0xFF;
        p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | alpha);
        /* This source store order keeps the stale alpha load in the late block. */
        p1->w0 = 0xFA000000;
        alpha = 0xFF;
        if ((s32) D_801D308C < 6)
        {
            D_801D308C += 1;
        }
    }
    guTranslate(arg2, 70.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}
