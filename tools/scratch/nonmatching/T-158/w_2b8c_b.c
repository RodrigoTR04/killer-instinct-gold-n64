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
    T025Gfx2B8C *p1;
    u8 color;
    T025Gfx2B8C *p0;
    f64 phase; CameraEye eye;
    if ((s32)D_801D3088 <= 0) return 0;
    eye.x = sinf((f32)((f64)state->timer * D_80292968)); arg1 = state->timer; phase = (f64)arg1; eye.y = (f32)(phase * D_80292970); state->timer = ++arg1; eye.y = cosf(eye.y);
    eye.z = 220.0f;
    guLookAtReflect(&matrix, &D_802C87D8, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); arg3 = state->fade;
    { T025Gfx2B8C *first = (*arg0)++;
    first->w0 = 0x03840010; first->w1 = (u32)&D_802C87D8;
    }
    p0 = (*arg0)++;
    p0->w0 = 0x03820010; p0->w1 = (u32)&D_802C87E8;
    if (arg3++ < 10) {
        arg1 = (u32)func_801B19F0(0.0f, 255.0f, state->fade = arg3, 10); color = (u16)arg1;
        alpha = arg1;
        arg1 = ((color & 0xFF) << 24) | ((color & 0xFF) << 16) | ((color & 0xFF) << 8) | (color & 0xFF); p1 = (*arg0)++;
        p1->w0 = 0xFA000000; p1->w1 = arg1;
    }
    else
    {
        state->fade = arg3; p0 = (*arg0)++;
        p0->w0 = 0xFA000000;
    arg1 = D_802C87D0 & 0xFF;
        p0->w1 = (arg1 << 24) | (arg1 << 16) | (arg1 << 8) | (alpha & 0xFF);
        alpha = 0xFF;
        if ((s32)D_801D308C <= 0) D_801D308C += 1;
    }
    guTranslate(arg2, -175.0f, 0.0f, (f32)D_801D3094);
    if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255; p0 = (*arg0)++; p0->w0 = 0xB900031D; p0->w1 = 0x0F0A4000;
    p0 = (*arg0)++; p0->w0 = 0xFB000000; p0->w1 = (alpha + D_801D3094) & 0xFF;
    p0 = (*arg0)++; p0->w0 = 0x06000000; p0->w1 = (u32)&D_801D3030;
    return 1; }
