/* DRAFT. Remaining diff: Float/global temporaries, matrix stack layout and call/display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx01EC;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern u8 D_8004A258;
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

s32 func_801B01EC(T025Gfx01EC **arg0, s32 arg1, u8 *arg2, u32 arg3) {
    u8 sp70[0x40];
    s32 sp68;
    s32 sp64;
    f32 sp60;
    u32 sp48;
    f32 temp_f0;
    f32 temp_f10;
    f32 temp_f2;
    s32 temp_f4;
    s32 temp_t3;
    u32 temp_a1;
    u32 temp_a2;
    u32 temp_v0;
    T025Gfx01EC *temp_v1;
    T025Gfx01EC *temp_v1_2;
    T025Gfx01EC *temp_v1_3;
    T025Gfx01EC *temp_v1_4;
    T025Gfx01EC *temp_v1_5;

    temp_a1 = arg3;
    sp68 = 1;
    sp64 = 0xFF;
    if (arg3 < 0x78U) {
        temp_f4 = (s32) func_801AFA80(255.0f, 2.0f, arg3, 0x78);
        D_802C8750 = 0;
        sp64 = temp_f4;
    } else {
        temp_a2 = 0x10E - temp_a1;
        arg3 = temp_a2;
        temp_f2 = (-cosf((f32) ((f64) func_801AFA80(110.0f, 0.0f, temp_a2, 0x96) * D_802928B8)) * 100.0f) + 100.0f;
        temp_v0 = (arg3 * 4) + 0x96;
        temp_f10 = 3.0f * temp_f2;
        sp48 = temp_v0;
        D_801D2EB4 = temp_f10;
        D_801D2EB0 = temp_f2;
        temp_f0 = func_801AFA80(270.0f, -1080.0f, arg3, temp_v0);
        sp60 = temp_f0;
        guRotate(arg2 + 0x40, temp_f0, 0.0f, 1.0f, 0.0f);
        sp68 = 2;
        if (((sp60 > 60.0f) && (D_802C8750 <= 0)) || ((sp60 > 230.0f) && (D_802C8750 < 2))) {
            func_8002F6F4(D_80066C40, 0x15C, (D_802C8750 * 4) + &D_8004A258);
            D_802C8750 += 1;
        }
        if (sp48 < 0xBEU) {
            D_8029571C = 3;
            func_801AF5D4(8);
            if (sp48 < 0x9AU) {
                func_801AF5EC(4);
            }
        }
    }
    guTranslate(arg2, D_801D2EB0, D_801D2EB8, D_801D2EB4);
    guLookAtReflect(&sp70, &D_802C8730, 0.0f, 0.0f, 0.0f, D_801D2EB0, 0.0f, 100.0f, 0.0f, 1.0f, 0.0f);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0x03840010;
    temp_v1->w1 = (u32)&D_802C8730;
    temp_v1_2 = *arg0;
    *arg0 = temp_v1_2 + 1;
    temp_v1_2->w0 = 0x03820010;
    temp_v1_2->w1 = (u32)&D_802C8740;
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3->w0 = 0x06000000;
    temp_v1_3->w1 = (u32)&D_801D2DF8;
    temp_v1_4 = *arg0;
    *arg0 = temp_v1_4 + 1;
    temp_v1_4->w0 = 0xFB000000;
    temp_t3 = sp64 & 0xFF;
    temp_v1_4->w1 = ((temp_t3 << 0x18) | (temp_t3 << 0x10) | (temp_t3 << 8) | 0xFF);
    temp_v1_5 = *arg0;
    *arg0 = temp_v1_5 + 1;
    temp_v1_5->w1 = 0xFF;
    temp_v1_5->w0 = 0xFA000000;
    return sp68;
}
