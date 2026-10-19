/* DRAFT. Remaining diff: Matrix stack layout, counter/unsigned alpha conversion, temporary registers and display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx2B8C;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30B8;
extern s32 D_801D30BC;
extern f64 D_80292968;
extern f64 D_80292970;
extern s16 D_802C87D0;
extern u8 D_802C87D8[];
extern u8 D_802C87E8[];

s32 func_801B2B8C(T025Gfx2B8C **arg0, s32 arg1, u8 *arg2, s32 arg3) {
    u8 sp70[0x40];
    f32 sp4C;
    f32 temp_f0;
    f64 temp_f18;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_t8_2;
    u32 temp_a0;
    u8 alpha;
    T025Gfx2B8C *temp_v1;
    T025Gfx2B8C *temp_v1_2;
    T025Gfx2B8C *temp_v1_3;
    T025Gfx2B8C *temp_v1_4;
    T025Gfx2B8C *temp_v1_5;
    T025Gfx2B8C *temp_v1_6;
    T025Gfx2B8C *temp_v1_7;

    if ((s32) D_801D3088 <= 0) {
        return 0;
    }
    temp_f0 = sinf((f32) ((f64) D_801D30BC * D_80292968));
    temp_f18 = (f64) D_801D30BC;
    D_801D30BC += 1;
    sp4C = temp_f0;
    guLookAtReflect(&sp70, &D_802C87D8, sp4C * 60.0f, cosf((f32) (temp_f18 * D_80292970)) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0x03840010;
    temp_v1->w1 = (u32)&D_802C87D8;
    temp_v1_2 = *arg0;
    *arg0 = temp_v1_2 + 1;
    temp_a1 = D_801D30B8 < 0xA;
    temp_a2 = D_801D30B8 + 1;
    temp_v1_2->w0 = 0x03820010;
    temp_v1_2->w1 = (u32)&D_802C87E8;
    if (temp_a1 != 0) {
        D_801D30B8 = temp_a2;
        temp_a0 = (u32) func_801B19F0(0.0f, 255.0f, temp_a2, 0xA);
        temp_t8 = temp_a0 & 0xFF;
        temp_v1_3 = *arg0;
        temp_t4 = (temp_t8 << 0x18) | (temp_t8 << 0x10) | (temp_t8 << 8);
        *arg0 = temp_v1_3 + 1;
        alpha = temp_a0 & 0xFF;
        temp_v1_3->w1 = (temp_t4 | temp_t8);
        temp_v1_3->w0 = 0xFA000000;
    } else {
        D_801D30B8 = temp_a2;
        temp_v1_4 = *arg0;
        *arg0 = temp_v1_4 + 1;
        temp_v1_4->w0 = 0xFA000000;
        temp_t8_2 = D_802C87D0 & 0xFF;
        temp_v1_4->w1 = ((temp_t8_2 << 0x18) | (temp_t8_2 << 0x10) | (temp_t8_2 << 8) | alpha);
        alpha = 0xFF;
        if ((s32) D_801D308C <= 0) {
            D_801D308C += 1;
        }
    }
    guTranslate(arg2, -175.0f, 0.0f, (f32) D_801D3094);
    if (D_801D3094 < 0) {
        D_802C87D0 = D_801D3094 + 0xFF;
    } else {
        D_802C87D0 = 0xFF;
    }
    temp_v1_5 = *arg0;
    *arg0 = temp_v1_5 + 1;
    temp_v1_5->w1 = 0x0F0A4000;
    temp_v1_5->w0 = 0xB900031D;
    temp_v1_6 = *arg0;
    *arg0 = temp_v1_6 + 1;
    temp_v1_6->w0 = 0xFB000000;
    temp_v1_6->w1 = ((alpha + D_801D3094) & 0xFF);
    temp_v1_7 = *arg0;
    *arg0 = temp_v1_7 + 1;
    temp_v1_7->w1 = (u32)&D_801D3030;
    temp_v1_7->w0 = 0x06000000;
    return 1;
}
