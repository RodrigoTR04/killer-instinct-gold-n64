extern f32 func_801B19F0(f32, f32, s32, s32);
/* DRAFT. Remaining diff: Counter update/branch form, temporary registers and display-list scheduling differ. */
typedef struct { s32 w0, w1; } T025Gfx2010;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D309C;
extern u8 D_802C03E0[];
extern u8 D_802C0BE0[];

s32 func_801B2010(T025Gfx2010 **arg0, s32 arg1, void *arg2, s32 arg3) {
    f32 position;
    s32 alpha;
    T025Gfx2010 *env;

    if ((s32) D_801D308C >= 2) {
        return 0;
    }
    if (D_801D309C < 1) {
        D_801D309C++;
        position = func_801B19F0(-6.0f, -150.0f, D_801D309C, 1);
    } else {
        D_801D309C++;
        position = -150.0f;
    }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C03E0, &D_802C0BE0, position, 0x7F);
    env = (*arg0)++;
    env->w0 = 0xFB000000;
    env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w1 = 0x64000000;
    env->w0 = 0xFA000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000;
    env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 2)) {
        D_801D3088 += 1;
    }
    return 1;
}
