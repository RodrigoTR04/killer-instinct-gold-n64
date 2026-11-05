f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
typedef struct { u32 w0, w1; } T025GfxFFAC;
extern void guTranslate(void *, f32, f32, f32);
extern s32 func_8002F6F4();
extern s32 D_801D2EAC;
extern f64 D_802928A8;
extern f64 D_802928B0;

s32 func_801AFFAC(T025GfxFFAC **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    f64 temp_f0;
    f64 a, b;
    s32 var_a3;
    s32 temp_a1;
    s32 mid;
    s32 low;
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
    temp_a0->w0 = 0xFB000000;
    temp_f0 = (f64) var_a3;
    a = temp_f0 * D_802928A8;
    b = temp_f0 * D_802928B0;
    temp_a1 = (u32) a;
    mid = (u32) b;
    low = (var_a3 & 0xFF) << 8;
    temp_a0->w1 = (temp_a1 << 24) | ((mid & 0xFF) << 16) | low;
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFA000000;
    temp_v1->w1 = (var_a3 & 0xFF) << 24;
    return 1;
}
