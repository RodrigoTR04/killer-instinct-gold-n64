/* T-122 nonmatching: 202 differing words; 1336 compiled bytes. See T-122/REPORT.md. */
/* T-076: nonmatching, 204 differing words including size penalty; 1336 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
typedef struct { u32 w0, w1; } T025Gfx0CDC;
typedef struct { u8 pad[0x10]; s32 state; } T070State0CDC;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern void func_801C3580(T025Gfx0CDC **, s32);
extern s32 func_801BBC84(void);
extern void func_801BC1B0(T025Gfx0CDC **, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern u8 D_8008EA20[];
extern s8 D_801CD454;
extern u8 D_801D2DF8[];
extern u8 D_801D2FC8[];
extern s8 D_801F3D64;
extern s32 D_801F3D6C;
extern s32 D_801F3D70;
extern f32 D_80292904;
extern f32 D_80292908;
extern f64 D_80292910;
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern u8 D_8029571A;
extern s32 D_8029571C;
extern u8 D_802C87A0[];
extern u8 D_802C87B0[];
extern s32 D_802C9F64;
extern s8 D_802C9F69;
extern s32 D_802C9F74;
extern s32 D_802D36A0;

s32 func_801B0CDC(T025Gfx0CDC **arg0, T070State0CDC *arg1, u8 *arg2, u32 arg3) {
    u8 sp98[0x40];
    s32 sp94;
    f32 eye[3];
    f32 up[3];
    f64 ratio;
    f32 temp_f0; f32 temp_f12;
    f64 var_f18;
    u32 alpha;
    T025Gfx0CDC *temp_v1;

    sp94 = 1;
    func_801C3580(arg0, (s32) (arg3 >> 1) % 360);
    if (arg3 < 0x28U) {
        temp_f0 = (f32) (arg3 / 40U);
        if (temp_f0 <= 0.0f) {
            guScale(arg2 + 0x80, 0.0f, 0.0f, 0.0f); } else {
            guScale(arg2 + 0x80, 1.0f, temp_f0, 1.0f);
        }
        sp94 = 2;
    } else {
        temp_v1 = *arg0;
        alpha = (arg3 - 0x1E) * 4;
        *arg0 = temp_v1 + 1;
    temp_v1->w1 = (u32)&D_801D2FC8; do { 
        temp_v1->w0 = 0x06000000; } while (0); 
        if (alpha >= 0x100U) {
            temp_v1 = (*arg0)++;
            alpha = 0xFF;
            temp_v1->w0 = 0xB900031D; temp_v1->w1 = 0x0F0A4000; } else {
            temp_v1 = (*arg0)++;
            temp_v1->w0 = 0xB900031D;
            temp_v1->w1 = 0x504240;
        }
        temp_v1 = (*arg0)++;
        temp_v1->w1 = 1;
        temp_v1->w0 = 0xB9000002;
        temp_v1 = (*arg0)++;
        temp_v1->w1 = 0;
        temp_v1->w0 = 0xFA000000;
        temp_v1 = (*arg0)++;
        temp_v1->w1 = (alpha & 0xFF); temp_v1->w0 = 0xFB000000;
        func_801BC1B0(arg0, &D_8008EA20, 0, 0x1F8, 0x46, 0x1F8, 2, 0, 0, 0x1F7, 0x45, 270.0f, D_80292904, 0x400, 0); temp_v1 = (*arg0)++; temp_v1->w1 = 0x80000; temp_v1->w0 = 0xBA001301;
        if ((u32) (D_802C9F74 - D_802D36A0) >= 0x3E9U) {
            D_8029571A += 1;
            arg1->state = -1; }
    }
    guScale(arg2, D_80292908, D_80292908, 1.0f);
    sp94 += 1;
    guTranslate(arg2 + 0x40, 4.0f, -90.0f, 50.0f); do { 
    var_f18 = (f64) arg3; } while (0); 
    temp_f12 = (f32) ((var_f18 * D_80292910) / 2);
    eye[0] = sinf(temp_f12);
    eye[1] = cosf(temp_f12);
    eye[2] = 220.0f;
    guLookAtReflect(&sp98, &D_802C87A0, eye[0] * 60.0f, eye[1] * 60.0f, eye[2], 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    if ((u8)D_801CD454 == 0) { D_801CD454 = 1;
        D_802C9F64 = 0;
        D_801F3D6C = 0; D_801F3D70 = 0x27F; if (arg3 < 0x28U) {
            D_802C9F69 = 1;
            D_801F3D64 = 1;
            func_801BBC84();
            func_801BBC84();
            func_801BBC84();
            func_801BBC84();
            func_801BBC84();
        }
    }
    if (arg3 >= 0x24U) {
        D_801F3D64 = 0xC;
        if (D_802956F8 == 0)
    { D_802956F8 = 0xFF; D_802956FC = 0xFF;
            D_80295700 = 0xFF;
            D_801CD454 = 0;
            D_802C9F69 = 1; D_801F3D64 = 0x1B; } else if (D_802956F8 != 1) {
            D_80295700 -= 0x80;
            D_802956FC -= 0x80;
            D_802956F8 -= 0x80;
            func_801BBC84();
            if (D_802956F8 == 0x7F) {
                D_802956F8 = 1;
                D_802956FC = 1;
                D_80295700 = 1;
                D_801CD454 = 1;
                D_8029571C = 1; } }
    } temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x03840010; temp_v1->w1 = (u32)&D_802C87A0;
    temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x03820010;
    temp_v1->w1 = (u32)&D_802C87B0;
    temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x06000000;
    temp_v1->w1 = (u32)&D_801D2DF8;
    return sp94;
}
