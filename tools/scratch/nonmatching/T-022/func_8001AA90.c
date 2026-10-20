/* T-052 DRAFT: 61 relocation-masked positional words differ; 488/496 bytes. */
extern u8 D_8004AC88;
extern f32 cosf(f32);
extern f32 sinf(f32);

extern f64 D_80048930;
extern f64 D_80048938;
extern u8 D_8004AD09;
extern f32 D_8004AD0C;
extern f32 D_8004AD10;

void func_8001AA90(f32 arg0) {
    f32 sp24;
    f32 sp18;
    f32 temp_f0;
    f32 temp_f12;
    f32 var_f12;
    f32 var_f14;
    f32 var_f2;
    s32 var_v0;
    u8 temp_t8;

    var_f14 = arg0;
    if (D_8004AC88 == 0) {
        var_f14 = arg0 - 90.0f;
    }
    temp_f12 = (f32) (((f64) var_f14 * D_80048930) / D_80048938);
    sp18 = temp_f12;
    sp24 = sinf(temp_f12);
    temp_f0 = cosf(temp_f12);
    var_f2 = sp24;
    var_f12 = temp_f0;
    if (D_8004AC88 == 0xB) {
        var_f2 *= 4.0f;
        var_f12 = temp_f0 * 4.0f;
    }
    if ((D_8004AC88 == 0) || (D_8004AC88 == 4)) {
        var_v0 = 4;
    } else {
        var_v0 = 1;
    }
    temp_t8 = ++D_8004AD09;
    if (var_v0 < (temp_t8 & 0xFF)) {
        D_8004AD09 = 0;
        D_8004AD0C += var_f2;
        D_8004AD10 -= var_f12;
    }
    if (D_8004AD0C > 255.0f) {
        do {
            D_8004AD0C -= 256.0f;
        } while (D_8004AD0C > 255.0f);
    }
    if (D_8004AD0C < 0.0f) {
        do {
            D_8004AD0C += 256.0f;
        } while (D_8004AD0C < 0.0f);
    }
    if (D_8004AD10 > 255.0f) {
        do {
            D_8004AD10 -= 256.0f;
        } while (D_8004AD10 > 255.0f);
    }
    if (D_8004AD10 < 0.0f) {
        do {
            D_8004AD10 += 256.0f;
        } while (D_8004AD10 < 0.0f);
    }
}
