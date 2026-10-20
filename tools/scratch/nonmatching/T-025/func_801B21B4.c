/* T-071 DRAFT: 17 differing words; layout-sensitive scheduling. */
extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx21B4;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30A0;
extern u8 D_802C13E0[];
extern u8 D_802C2020[];

s32 func_801B21B4(T025Gfx21B4 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    T025Gfx21B4 *env;
    if ((s32) D_801D308C >= 3)
    {
        return 0;
    }
    arg1 = D_801D30A0;
    arg3 = arg1 < 1;
    arg1++;
    D_801D30A0 = arg1;
    if (arg3 == 1)
    {
        position = func_801B19F0(44.0f, -100.0f, D_801D30A0, 1);
    }
    else
    {
        position = -100.0f;
    }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C13E0, &D_802C2020, position, 0xC3);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 3))
    {
        D_801D3088 += 1;
    }
    return 1;
}
