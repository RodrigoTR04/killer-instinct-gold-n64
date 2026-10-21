/* T-120 DRAFT: 7 differing words; 536 bytes. Not matching.
 * Original late-path uninitialized alpha read retained; scratch only. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx2EF4;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30C0;
extern s16 D_802C87D0;

s32 func_801B2EF4(T025Gfx2EF4 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30C0;
    T025Gfx2EF4 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 2)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        p1 = (*arg0)++;
        p1->w0 = primitive;
        color2 = D_802C87D0 & 0xFF;
        p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
        alpha = 0xFF;
        if ((s32) D_801D308C < 2)
        {
            D_801D308C += 1;
        }
    }
    guTranslate(arg2, -125.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}
