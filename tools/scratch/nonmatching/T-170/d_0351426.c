/* T-164: look-at intro. Target frame is 0xB0 with the 0x40 matrix at sp+0x70. */
typedef struct { u32 w0, w1; } T164Gfx01EC;
extern f32 cosf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4(s32, s32, void *);
extern void func_801AF5EC(s32);
extern void func_801AF5D4(s32);
extern f32 func_801AFA80(f32, f32, s32, s32);
typedef struct { u8 bytes[4]; } T164Sample01EC;
extern T164Sample01EC D_8004A258[];
extern s32 D_80066C40;
extern u8 D_801D2DF8[];
extern f32 D_801D2EB0;
extern f32 D_801D2EB4;
extern f32 D_801D2EB8;
extern f64 D_802928B8;
extern s32 D_8029571C;
extern u8 D_802C8730[];
extern u8 D_802C8740[];
extern s32 D_802C8750;

s32 func_801B01EC(T164Gfx01EC **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    u8 lookat[0x40];
    f32 angle;
    s32 alpha[1];
    T164Gfx01EC *g;
    f32 rise;
    s32 result;
    u32 elapsed;





    s32 alpha;


    result = 1;
    alpha[0] = 0xFF;
    if (arg3 < 0x78) {
        alpha[0] = (s32) func_801AFA80(255.0f, 2.0f, (s32) arg3, 0x78);
        D_802C8750 = 0;
    } else {
        arg3 = 0x10E - arg3;
        rise = (-cosf((f32) ((f64) func_801AFA80(110.0f, 0.0f, (s32) arg3, 0x96) * D_802928B8)) * 100.0f) + 100.0f;
        elapsed = (arg3 * 4) + 0x96;
        D_801D2EB4 = 3.0f * rise;
        D_801D2EB0 = rise;
        angle = func_801AFA80(270.0f, -1080.0f, (s32) arg3, (s32) elapsed);
        guRotate(arg2 + 0x40, angle, 0.0f, 1.0f, 0.0f);
        result = 2;
        if ((angle > 60.0f && D_802C8750 <= 0) || (angle > 230.0f && D_802C8750 < 2)) {
            func_8002F6F4(D_80066C40, 0x15C, &D_8004A258[D_802C8750]);
            D_802C8750 += 1;
        }
        if (elapsed < 0xBE) {
            D_8029571C = 3;
            func_801AF5D4(8);
            if (elapsed < 0x9A) {
                func_801AF5EC(4);
            }
        }
    }
    guTranslate(arg2, D_801D2EB0, D_801D2EB8, D_801D2EB4);
    guLookAtReflect(lookat, &D_802C8730, 0.0f, 0.0f, 0.0f, D_801D2EB0, 0.0f, 100.0f, 0.0f, 1.0f, 0.0f);
    g = (*arg0)++;
    g->w0 = 0x03840010;
    g->w1 = (u32) &D_802C8730;
    g = (*arg0)++;
    g->w0 = 0x03820010;
    g->w1 = (u32) &D_802C8740;
    g = (*arg0)++;
    g->w0 = 0x06000000;
    g->w1 = (u32) &D_801D2DF8;
    g = (*arg0)++;
    g->w0 = 0xFB000000;
    alpha[0] &= 0xFF;
    g->w1 = (alpha[0] << 24) | (alpha[0] << 16) | (alpha[0] << 8) | 0xFF;
    g = (*arg0)++;
    g->w1 = 0xFF;
    g->w0 = 0xFA000000;
    return result;
}
