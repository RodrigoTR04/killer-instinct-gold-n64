/* T-098 DRAFT: 57 differing words; 536 bytes. Not matching.
 * The late branch retains the inherited uninitialized alpha read; scratch only. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx396C;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30D4;
extern s16 D_802C87D0;

s32 func_801B396C(T025Gfx396C **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30D4;
    T025Gfx396C *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    if ((s32) D_801D3088 < 7)
    {
        return 0;
    }
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        p0 = *arg0;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8);
        *arg0 = p0 + 1;
        /* Keep alpha assignment separate from the command store for IDO scheduling. */
        alpha = color;
        p0->w1 = (s32) (packed | (color & 0xFF));
        p0->w0 = 0xFA000000;
    }
    else
    {
        *counter = arg1;
        p1 = (*arg0)++;
        p1->w0 = 0xFA000000;
        color2 = D_802C87D0 & 0xFF;
        p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | alpha);
        alpha = 0xFF;
        if ((s32) D_801D308C < 7)
        {
            D_801D308C += 1;
        }
    }
    guTranslate(arg2, 128.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}
