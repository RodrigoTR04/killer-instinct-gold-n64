/* DRAFT. Remaining diff: Float temporaries, matrix local stack layout and call/display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx0A40;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern s8 D_801CD454;
extern u8 D_801D2DF8[];
extern f64 D_802928E8;
extern f64 D_802928F0;
extern f64 D_802928F8;
extern f32 D_80292900;
extern u8 D_802C8780[];
extern u8 D_802C8790[];
extern s32 D_802CA064;

s32 func_801B0A40(T025Gfx0A40 **arg0, s32 arg1, u8 *arg2, s32 arg3) {
    u8 sp70[0x40];
    f32 sp58;
    f32 sp54;
    f32 temp_f0;
    f32 temp_f12;
    f32 height;
    f64 var_f10;
    T025Gfx0A40 *temp_v1;
    T025Gfx0A40 *temp_v1_2;
    T025Gfx0A40 *temp_v1_3;

    temp_f0 = func_801AFA80(300.0f, 0.0f, arg3, 0x28);
    if (temp_f0 > 0.0f) {
        if (temp_f0 <= 60.0f) {
            height = (f32) (120.0 - ((f64) (cosf((f32) ((f64) temp_f0 * D_802928E8 * 0.75)) * 60.0f) / D_802928F0)) - 35.0f;
        } else {
            D_801CD454 = 0;
            D_802CA064 = 0x280;
            height = temp_f0 - 35.0f;
        }
    } else {
        height = 0.0f;
    }
    var_f10 = (f64) arg3;
    if (arg3 < 0) {
        var_f10 += 4294967296.0;
    }
    temp_f12 = (f32) ((var_f10 * D_802928F8) / 2.0);
    sp54 = temp_f12;
    sp58 = sinf(temp_f12);
    guLookAtReflect(&sp70, &D_802C8780, sp58 * 60.0f, cosf(temp_f12) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guScale(arg2, D_80292900, D_80292900, 1.0f);
    guTranslate(arg2 + 0x40, (f32) ((f64) (height + 75.0f) - 8.0), 28.0f, 170.0f);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0x03840010;
    temp_v1->w1 = (u32)&D_802C8780;
    temp_v1_2 = *arg0;
    *arg0 = temp_v1_2 + 1;
    temp_v1_2->w0 = 0x03820010;
    temp_v1_2->w1 = (u32)&D_802C8790;
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3->w0 = 0x06000000;
    temp_v1_3->w1 = (u32)&D_801D2DF8;
    return 2;
}
