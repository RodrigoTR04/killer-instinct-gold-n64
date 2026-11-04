f32 func_801B19F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
/* T-146 draft: 8 differing words, 872/872 bytes in full TU. The original completed-animation branch reads alpha before initialization. */
typedef struct { u32 w0, w1; } T025Gfx2B8C;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
typedef struct { s32 fade, timer; } AnimationState;
extern AnimationState D_801D30B8;
extern f64 D_80292968;
extern f64 D_80292970;
extern s16 D_802C87D0;
extern u8 D_802C87D8[];
extern u8 D_802C87E8[];

typedef struct { f32 x, y, z; } CameraEye;
s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3)
{
    u8 alpha;
AnimationState *state = &D_801D30B8; u8 matrix[64];
    u32 value;
    u8 color;
    T025Gfx2B8C *p3, *p0, *p1, *p2;
    CameraEye eye;
    if ((s32)D_801D3088 <= 0) return 0;
    eye.x = sinf((f32)((f64)state->timer * D_80292968)); arg3 = state->timer; eye.y = (f32)((f64)arg3 * D_80292970); state->timer = ++arg3; eye.y = cosf(eye.y);
    eye.z = 220.0f;
    guLookAtReflect(&matrix, &D_802C87D8, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); arg1 = state->fade;
    p3 = (*arg0)++;
    p3->w0 = 0x03840010; p3->w1 = (u32)&D_802C87D8;
    p0 = (*arg0)++;
    p0->w0 = 0x03820010; p0->w1 = (u32)&D_802C87E8;
    if (arg1++ < 10) {
        value = (u32)func_801B19F0(0.0f, 255.0f, state->fade = arg1, 10); color = (u16)value;
        alpha = value;
        value = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF); p1 = (*arg0)++;
        p1->w0 = 0xFA000000; p1->w1 = value;
    }
    else
    {
        state->fade = arg1;
        do {
            p3 = (*arg0)++;
            p3->w0 = 0xFA000000;
            value = D_802C87D0 & 0xFF;
            p3->w1 = (value << 24) | (value << 16) | (value << 8) | (alpha & 0xFF);
            alpha = 0xFF;
            if ((s32)D_801D308C >= 1) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, -175.0f, 0.0f, (f32)D_801D3094);
    if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255; p1 = (*arg0)++; p1->w0 = 0xB900031D; p1->w1 = 0x0F0A4000;
    p2 = (*arg0)++; p2->w0 = 0xFB000000; p2->w1 = (alpha + D_801D3094) & 0xFF;
    p3 = (*arg0)++; p3->w0 = 0x06000000; p3->w1 = (u32)&D_801D3030;
    return 1; }
