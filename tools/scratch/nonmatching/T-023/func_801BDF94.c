/* DRAFT. Remaining diff: Matrix/vector buffer types, float arguments, stack and rendering scheduling differ. */
typedef struct { u32 w0, w1; } T023801BDF94Gfx;
typedef struct { u32 image; f32 width; } T023801BDF94Glyph;
f32 cosf(f32);
extern void guLookAtReflect();
extern void guRotate();
extern void guScale();
extern void guTranslate();
f32 sinf(f32);
extern u8 D_80282C48[];
extern u8 D_80282D28[];
extern s32 D_80282DC0;
extern f32 D_80292B58;
extern f64 D_80292B60;
extern f64 D_80292B68;
extern f64 D_80292B70;
extern f64 D_80292B78;
extern f64 D_80292B80;
extern u8 D_802D36B0[];
extern u8 D_802D36C0[];

s32 func_801BDF94(u8 **arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, f32 arg7, f32 arg8) {
    u8 spE8[64];
    f32 spD4;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    f32 var_f12;
    f32 var_f22;
    f32 var_f28;
    f32 var_f30;
    f64 temp_f20_2;
    f64 temp_f24;
    f64 var_f0;
    f64 var_f0_2;
    f64 var_f0_3;
    s32 var_s3;
    s32 var_s5;
    s32 var_s7;
    s32 var_v1;
    s8 var_v0_2;
    u8 *var_s4;
    u8 *var_v0;
    u8 temp_a3;
    u8 temp_t1;
    u8 var_v1_2;
    u8 *temp_s2;
    u8 *temp_v0;
    u8 *temp_v0_10;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v0_8;
    u8 *temp_v0_9;

    var_f28 = arg7;
    var_f22 = arg3;
    var_s7 = 0;
    var_s3 = 0;
    if ((var_f28 != 1.0f) && (var_f28 != -1.0f)) {
        if (var_f28 < 0.0f) {
            guScale(arg1, 1.0f, -var_f28, 1.0f);
            var_f28 = D_80292B58;
        } else {
            guScale(arg1, var_f28, var_f28, 1.0f);
        }
        var_s3 = 1;
    }
    if (arg6 == 2) {
        temp_s0 = (var_s3 << 6) + arg1;
        guRotate(temp_s0, arg8, 0.0f, 1.0f, 0.0f);
        temp_v0 = *arg0;
        *arg0 = temp_v0 + 8;
        var_s3 += 1;
        ((T023801BDF94Gfx *)temp_v0)->w1 = temp_s0;
        ((T023801BDF94Gfx *)temp_v0)->w0 = 0x01020040;
    }
    temp_f24 = D_80292B60;
    temp_f20 = sinf((f32) ((f64) D_80282DC0 * temp_f24));
    guLookAtReflect(&spE8, &D_802D36B0, temp_f20 * 60.0f, cosf((f32) ((f64) D_80282DC0 * temp_f24)) * 60.0f, 220.0f, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    temp_v0_2 = *arg0;
    *arg0 = temp_v0_2 + 8;
    ((T023801BDF94Gfx *)temp_v0_2)->w1 = &D_802D36B0;
    ((T023801BDF94Gfx *)temp_v0_2)->w0 = 0x03840010;
    temp_v0_3 = *arg0;
    *arg0 = temp_v0_3 + 8;
    ((T023801BDF94Gfx *)temp_v0_3)->w0 = 0x03820010;
    ((T023801BDF94Gfx *)temp_v0_3)->w1 = &D_802D36C0;
    temp_v0_4 = *arg0;
    *arg0 = temp_v0_4 + 8;
    ((T023801BDF94Gfx *)temp_v0_4)->w0 = 0x06000000;
    ((T023801BDF94Gfx *)temp_v0_4)->w1 = &D_80282D28;
    var_v0 = arg2;
    D_80282DC0 += 1;
    temp_a3 = *arg2;
    var_v1 = 0;
    var_s4 = arg2;
    if (temp_a3 != 0) {
        do {
            temp_t1 = *(u8 *)(var_v0 + 0x1);
            var_v1 += 1;
            var_v0 += 1;
        } while (temp_t1 != 0);
    }
    var_s5 = 0;
    var_f30 = arg5;
    arg8 -= (f32) (var_v1 * 0x1E);
    if (temp_a3 != 0) {
        var_v1_2 = *arg2;
        do {
            var_v0_2 = var_v1_2 - 0x41;
            if (var_v0_2 == -0x13) {
                var_v0_2 = 0x1A;
            }
            if ((var_v0_2 < 0x1B) && (var_v0_2 >= 0) && (temp_s2 = (var_v0_2 * 8) + &D_80282C48, temp_s0_2 = (var_s3 << 6) + arg1, (((T023801BDF94Glyph *)temp_s2)->image != 0))) {
                var_f12 = 0.0f;
                temp_f20_2 = (f64) var_f28;
                if (var_s7 != 0) {
                    var_f0 = D_80292B68;
                } else {
                    var_f0 = (f64) (((T023801BDF94Glyph *)temp_s2)->width * 9.0f);
                }
                temp_f22 = (f32) ((f64) var_f22 + (temp_f20_2 * var_f0));
                if (arg6 == 1) {
                    temp_f2 = (f32) (var_s5 * 0x1E) + arg8;
                    var_f12 = temp_f2;
                    if (temp_f2 < 360.0f) {
                        temp_f0 = temp_f2 - 360.0f;
                        var_f30 -= temp_f0 / 8.0f;
                        arg4 += temp_f0 / 32.0f;
                    }
                }
                spD4 = var_f12;
                guTranslate(temp_s0_2, temp_f22, arg4, var_f30);
                if (arg6 == 2) {
                    temp_v0_5 = *arg0;
                    *arg0 = temp_v0_5 + 8;
                    var_s3 += 1;
                    ((T023801BDF94Gfx *)temp_v0_5)->w1 = temp_s0_2;
                    ((T023801BDF94Gfx *)temp_v0_5)->w0 = 0x01040040;
                } else {
                    temp_v0_6 = *arg0;
                    *arg0 = temp_v0_6 + 8;
                    var_s3 += 1;
                    ((T023801BDF94Gfx *)temp_v0_6)->w1 = temp_s0_2;
                    ((T023801BDF94Gfx *)temp_v0_6)->w0 = 0x01020040;
                }
                if ((var_f12 < 360.0f) && (arg6 == 1)) {
                    temp_s0_3 = (var_s3 << 6) + arg1;
                    guRotate(temp_s0_3, var_f12, 1.0f, 0.0f, 0.0f);
                    temp_v0_7 = *arg0;
                    *arg0 = temp_v0_7 + 8;
                    var_s3 += 1;
                    ((T023801BDF94Gfx *)temp_v0_7)->w1 = temp_s0_3;
                    ((T023801BDF94Gfx *)temp_v0_7)->w0 = 0x01000040;
                }
                if (var_f28 != 1.0f) {
                    temp_v0_8 = *arg0;
                    *arg0 = temp_v0_8 + 8;
                    ((T023801BDF94Gfx *)temp_v0_8)->w1 = arg1;
                    ((T023801BDF94Gfx *)temp_v0_8)->w0 = 0x01000040;
                }
                temp_v0_9 = *arg0;
                *arg0 = temp_v0_9 + 8;
                ((T023801BDF94Gfx *)temp_v0_9)->w0 = 0x06000000;
                ((T023801BDF94Gfx *)temp_v0_9)->w1 = (u8 *) ((T023801BDF94Glyph *)temp_s2)->image;
                if (var_s7 != 0) {
                    var_f0_2 = D_80292B70;
                } else {
                    var_f0_2 = (f64) (((T023801BDF94Glyph *)temp_s2)->width * 10.0f);
                }
                var_f22 = (f32) ((f64) temp_f22 + (temp_f20_2 * var_f0_2));
                if (arg6 == 2) {
                    temp_v0_10 = *arg0;
                    *arg0 = temp_v0_10 + 8;
                    ((T023801BDF94Gfx *)temp_v0_10)->w1 = 0;
                    ((T023801BDF94Gfx *)temp_v0_10)->w0 = 0xBD000000;
                }
            } else if (var_v0_2 == 0x29) {
                var_s7 = 1;
            } else {
                if (var_s7 != 0) {
                    var_f0_3 = D_80292B78;
                } else {
                    var_f0_3 = D_80292B80;
                }
                var_f22 = (f32) ((f64) var_f22 + ((f64) var_f28 * var_f0_3));
            }
            var_v1_2 = *(u8 *)(var_s4 + 0x1);
            var_s5 += 1;
            var_s4 += 1;
        } while (var_v1_2 != 0);
        arg5 = var_f30;
    }
    return var_s3;
}
