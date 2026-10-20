/* T-076: nonmatching, 156 differing words including size penalty; 984 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
/* DRAFT. Remaining diff: Float temporaries, matrix stack layout and call/display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx0668;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4(s32, s16, void *);
extern void func_801ADAD4(s32);
extern void func_801C35AC(T025Gfx0668 **, s32);
extern u8 D_8004A258;
extern u8 D_8004A25C[];
extern s32 D_80066C40;
extern u8 D_801D2DF8[];
extern u8 D_801D2FC0;
extern f64 D_802928C0;
extern f64 D_802928C8;
extern f32 D_802928D0;
extern f64 D_802928D8;
extern f64 D_802928E0;
extern u8 D_802C8760[];
extern u8 D_802C8770[];

s32 func_801B0668(T025Gfx0668 **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    u8 sp60[0x40];
    f32 sp48;
    f32 temp_f0;
    f32 angle;
    f32 height;
    u32 state;
    f64 temp_f2;
    f64 var_f8;
    u8 temp_t4;
    T025Gfx0668 *temp_v1;
    T025Gfx0668 *temp_v1_2;
    T025Gfx0668 *temp_v1_3;

    height = func_801AFA80(300.0f, 0.0f, arg3, 40);
    if (height > 0.0f) {
        if (height <= 60.0f) {
            height = 120.0 - cosf(height * D_802928C0 * 0.75) * 60.0f / D_802928C8;
        }
        height -= 35.0f;
        if (height <= 200.0f) {
            state = D_801D2FC0;
            if (!(state & 0x7F)) {
                func_8002F6F4(D_80066C40, 0x135, &D_8004A258);
                state = D_801D2FC0;
                D_801D2FC0 = state | 1;
            }
        } else {
            state = D_801D2FC0;
            D_801D2FC0 = state & 0x80;
        }
    } else {
        state = D_801D2FC0;
        height = 0.0f;
        if ((state & 0x7F) == 1) {
            func_8002F6F4(D_80066C40, 11, &D_8004A258);
            func_801ADAD4(40);
            state = D_801D2FC0;
            D_801D2FC0 = state | 3;
        } else if (state >= 3 && state < 128) {
            state++;
            D_801D2FC0 = state;
            if (state >= 21) {
                func_8002F6F4(D_80066C40, 0x1AE, &D_8004A25C);
                D_801D2FC0 = 0x82;
            }
        }
    }
    guScale(arg2, D_802928D0, D_802928D0, 1.0f);
    guTranslate(arg2 + 0x40, (f32) ((((f64) -height + 50.0) - D_802928D8) - 8.0), 8.0f, 170.0f);
    var_f8 = (f64) arg3;
    temp_f2 = var_f8 * D_802928E0;
    sp48 = sinf((f32) (temp_f2 / 2.0));
    guLookAtReflect(&sp60, &D_802C8760, sp48 * 60.0f, cosf((f32) temp_f2) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    func_801C35AC(arg0, (s32) ((u32) arg3 >> 1) % 360);
    temp_v1 = (*arg0)++;
    temp_v1->w1 = (u32)&D_802C8760;
    temp_v1->w0 = 0x03840010;
    temp_v1_2 = (*arg0)++;
    temp_v1_2->w0 = 0x03820010;
    temp_v1_2->w1 = (u32)&D_802C8770;
    temp_v1_3 = (*arg0)++;
    temp_v1_3->w0 = 0x06000000;
    temp_v1_3->w1 = (u32)&D_801D2DF8;
    return 2;
}
