/* DRAFT. Remaining diff: Frame/local alpha slot, counter update, unsigned float conversion and display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx353C;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30CC;
extern s16 D_802C87D0;

s32 func_801B353C(T025Gfx353C **arg0, s32 arg1, void *arg2, s32 arg3) {
    s32 color;
    s32 color2;
    s32 packed;
    u32 value;
    u8 alpha;
    T025Gfx353C *temp_v1;
    T025Gfx353C *temp_v1_2;
    T025Gfx353C *temp_v1_3;
    T025Gfx353C *temp_v1_4;

    if ((s32) D_801D3088 < 5) {
        return 0;
    }
    if (D_801D30CC++ < 10) {
        value = (u32) func_801B19F0(0.0f, 255.0f, D_801D30CC, 10);
        color = value & 0xFF;
        temp_v1 = *arg0;
        packed = (color << 0x18) | (color << 0x10) | (color << 8);
        *arg0 = temp_v1 + 1;
        alpha = value & 0xFF;
        temp_v1->w1 = (s32) (packed | color);
        temp_v1->w0 = 0xFA000000;
    } else {
        temp_v1_2 = *arg0;
        *arg0 = temp_v1_2 + 1;
        temp_v1_2->w0 = 0xFA000000;
        color2 = D_802C87D0 & 0xFF;
        temp_v1_2->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | alpha);
        alpha = 0xFF;
        if ((s32) D_801D308C < 5) {
            D_801D308C += 1;
        }
    }
    guTranslate(arg2, 14.0f, 0.0f, (f32) D_801D3094);
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3->w0 = 0xFB000000;
    temp_v1_3->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    temp_v1_4 = *arg0;
    *arg0 = temp_v1_4 + 1;
    temp_v1_4->w1 = (s32) &D_801D3030;
    temp_v1_4->w0 = 0x06000000;
    return 1;
}
