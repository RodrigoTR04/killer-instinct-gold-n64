/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx2B8C;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30B8;
extern s32 D_801D30BC;
extern f64 D_80292968;
extern f64 D_80292970;
extern s16 D_802C87D0;
extern u8 D_802C87D8[];
extern u8 D_802C87E8[];

typedef struct { f32 x, y, z; } CameraEye;

s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3)
{
    u8 alpha;
    T025Gfx2B8C *p0, *p1, *p2, *p3, *p4, *p5;
    u8 color;
    u32 value;
    u8 matrix[64];
    f32 ex; f32 ey;
    if ((s32) D_801D3088 <= 0)
    {
        return 0;
    }
    ex = sinf((f32)((f64)D_801D30BC * D_80292968));
    arg3 = D_801D30BC;
    ey = (f32)((f64)arg3 * D_80292970);
    D_801D30BC = ++arg3;
    ey = cosf(ey);
    guLookAtReflect(&matrix, &D_802C87D8, ex * 60.0f, ey * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    arg1 = D_801D30B8;
    p0 = (*arg0)++;
    p0->w0 = 0x03840010; p0->w1 = (s32) &D_802C87D8;
    p1 = (*arg0)++;
    p1->w0 = 0x03820010; p1->w1 = (s32) &D_802C87E8;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, D_801D30B8 = arg1, 10);
        color = (u16)value;
        alpha = value;
        value = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        p2 = (*arg0)++;
        p2->w0 = 0xFA000000; p2->w1 = (s32) value;
    }
    else
    {
        D_801D30B8 = arg1;
        do {
            p2 = (*arg0)++;
            p2->w0 = 0xFA000000;
            value = D_802C87D0 & 0xFF;
            p2->w1 = (s32) ((value << 0x18) | (value << 0x10) | (value << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 1) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, -175.0f, 0.0f, (f32) D_801D3094);
    if (D_801D3094 < 0)
    {
        D_802C87D0 = D_801D3094 + 255;
    }
    else
    {
        D_802C87D0 = 255;
    }
    p3 = (*arg0)++;
    p3->w0 = 0xB900031D; p3->w1 = 0x0F0A4000;
    p4 = (*arg0)++;
    p4->w0 = 0xFB000000;
    p4->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p5 = (*arg0)++;
    p5->w0 = 0x06000000; p5->w1 = (s32) &D_801D3030;
    return 1;
}
