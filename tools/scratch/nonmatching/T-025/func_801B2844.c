/* DRAFT. Remaining diff: Counter update/branch form, temporary registers and display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx2844;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30B0;
extern u8 D_802C6420[];
extern u8 D_802C6AE0[];

s32 func_801B2844(T025Gfx2844 **arg0, s32 arg1, void *arg2, s32 arg3) {
    f32 position;
    s32 alpha;
    T025Gfx2844 *env;
    T025Gfx2844 *prim;
    T025Gfx2844 *list;

    if ((s32) D_801D308C >= 7) {
        return 0;
    }
    if (D_801D30B0++ < 1) {
        position = func_801B19F0(247.0f, 103.0f, D_801D30B0, 1);
    } else {
        position = 103.0f;
    }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C6420, &D_802C6AE0, position, 0x6B);
    env = (*arg0)++;
    env->w0 = 0xFB000000;
    env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    prim = *arg0;
    *arg0 = prim + 1;
    prim->w1 = 0x64000000;
    prim->w0 = 0xFA000000;
    list = *arg0;
    *arg0 = list + 1;
    list->w0 = 0x06000000;
    list->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 7)) {
        D_801D3088 += 1;
    }
    return 1;
}
