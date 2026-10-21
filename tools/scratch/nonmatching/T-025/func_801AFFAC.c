/* T-121 DRAFT: see T-121/REPORT.md for measurements and remaining differences. */
f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
/* DRAFT. Remaining diff: Interpolation/control-flow temporaries and unsigned color-conversion/packing scheduling differ. */
typedef struct { u32 w0, w1; } T025GfxFFAC;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern s32 D_801D2EAC;
extern f64 D_802928A8;
extern f64 D_802928B0;

s32 func_801AFFAC(T025GfxFFAC **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    f64 temp_f0;
    s32 temp_a1;
    s32 var_a3;
    T025GfxFFAC *temp_a0;
    T025GfxFFAC *temp_v1;

    if (arg3 >= 0x4CU) {
        if (arg3 >= 0x97U) {
            D_801D2EAC = (s32) func_801AFA80(255.0f, 10.0f, arg3 - 0x96, 0x36);
        }
    } else {
        D_801D2EAC = (s32) func_801AFA80(0.0f, 255.0f, arg3, 0x4B);
    }
    guTranslate(arg2, 0.0f, 135.0f, 0.0f);
    var_a3 = D_801D2EAC;
    temp_a0 = *arg0;
    *arg0 = temp_a0 + 1;
    temp_f0 = (f64) var_a3;
    temp_a0->w0 = 0xFB000000;
    temp_a1 = var_a3 & 0xFF;
    temp_a0->w1 = (s32) (((u32) (temp_f0 * D_802928A8) << 0x18) | (((u32) (temp_f0 * D_802928B0) & 0xFF) << 0x10) | (temp_a1 << 8));
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w1 = (s32) (temp_a1 << 0x18);
    temp_v1->w0 = 0xFA000000;
    return 1;
}
