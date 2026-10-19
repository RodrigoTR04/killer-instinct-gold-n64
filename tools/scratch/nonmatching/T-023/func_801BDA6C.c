/* DRAFT. Remaining diff: Glyph/matrix pointers, float/double arithmetic and rendering scheduling differ. */
typedef struct { u32 w0, w1; } T023801BDA6CGfx;
typedef struct { u32 image; f32 width; } T023801BDA6CGlyph;
extern void guScale();
extern void guTranslate();
f32 sinf(f32);
s32 strlen(u8 *);
extern u8 D_80282A70[];
extern f32 D_80282D20;
extern f64 D_80292B50;

s32 func_801BDA6C(u8 **arg0, s32 arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 arg10) {
    s32 spD0;
    s32 spCC;
    s32 sp78;
    s32 sp74;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f22;
    f32 temp_f6;
    f32 var_f22;
    f32 var_f26;
    f64 temp_f20;
    f64 temp_f28;
    f64 var_f0;
    f64 var_f0_2;
    s32 temp_s1;
    s32 temp_t6;
    s32 temp_v0;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s8 temp_v0_2;
    u8 *var_s5;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_11;
    u8 *temp_s0_12;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_s3;
    u8 *temp_v0_3;
    f64 advance;

    var_f22 = arg3;
    spCC = 0x7D0;
    var_s6 = 0;
    var_s7 = 0;
    temp_v0 = strlen(arg2);
    spD0 = temp_v0;
    if (temp_v0 == 0) {
        return 0;
    }
    var_f26 = arg10;
    if (var_f26 < 0.0f) {
        temp_f6 = -var_f26;
        var_f26 = 1.0f;
        spCC = (s32) (temp_f6 - 1.0f);
    }
    if (var_f26 != 1.0f) {
        guScale(arg1, var_f26, var_f26, 1.0f);
        var_s7 = 1;
    }
    temp_s0 = *arg0;
    *arg0 = temp_s0 + 8;
    ((T023801BDA6CGfx *)temp_s0)->w1 = 0;
    ((T023801BDA6CGfx *)temp_s0)->w0 = 0xE7000000;
    temp_s0_2 = *arg0;
    *arg0 = temp_s0_2 + 8;
    ((T023801BDA6CGfx *)temp_s0_2)->w0 = 0xFA000000;
    sp78 = (s32) arg9;
    temp_t6 = (arg6 << 0x18) | (arg7 << 0x10) | (arg8 << 8) | sp78;
    sp74 = temp_t6;
    ((T023801BDA6CGfx *)temp_s0_2)->w1 = temp_t6;
    temp_s0_3 = *arg0;
    *arg0 = temp_s0_3 + 8;
    ((T023801BDA6CGfx *)temp_s0_3)->w1 = 0xFFFDF6FB;
    ((T023801BDA6CGfx *)temp_s0_3)->w0 = 0xFCFFFFFF;
    temp_s0_4 = *arg0;
    *arg0 = temp_s0_4 + 8;
    ((T023801BDA6CGfx *)temp_s0_4)->w0 = 0xB6000000;
    ((T023801BDA6CGfx *)temp_s0_4)->w1 = 0x22000;
    if (arg9 == 0xFF) {
        temp_s0_5 = *arg0;
        *arg0 = temp_s0_5 + 8;
        ((T023801BDA6CGfx *)temp_s0_5)->w0 = 0xB900031D;
        ((T023801BDA6CGfx *)temp_s0_5)->w1 = 0x0F0A4000;
    } else {
        temp_s0_6 = *arg0;
        *arg0 = temp_s0_6 + 8;
        ((T023801BDA6CGfx *)temp_s0_6)->w0 = 0xB900031D;
        ((T023801BDA6CGfx *)temp_s0_6)->w1 = 0x5041C8;
    }
    var_s4 = 0;
    if (spD0 > 0) {
        temp_f28 = D_80292B50;
        var_s5 = arg2;
        do {
            temp_v0_2 = *var_s5 - 0x20;
            if ((temp_v0_2 < 0x3B) && (temp_v0_2 >= 0) && (temp_s3 = (temp_v0_2 * 8) + &D_80282A70, (((T023801BDA6CGlyph *)temp_s3)->image != 0))) {
                temp_f20 = (f64) var_f26;
                if (var_s6 != 0) {
                    var_f0 = 25.0;
                } else {
                    var_f0 = (f64) (((T023801BDA6CGlyph *)temp_s3)->width * 10.0f);
                }
                temp_s1 = (var_s7 << 6) + arg1;
                temp_f22 = (f32) ((f64) var_f22 + (temp_f20 * var_f0));
                guTranslate(temp_s1, temp_f22, arg4, arg5);
                temp_s0_7 = *arg0;
                *arg0 = temp_s0_7 + 8;
                var_s7 += 1;
                ((T023801BDA6CGfx *)temp_s0_7)->w0 = 0x01020040;
                ((T023801BDA6CGfx *)temp_s0_7)->w1 = temp_s1;
                if (var_f26 != 1.0f) {
                    temp_s0_8 = *arg0;
                    *arg0 = temp_s0_8 + 8;
                    ((T023801BDA6CGfx *)temp_s0_8)->w0 = 0x01000040;
                    ((T023801BDA6CGfx *)temp_s0_8)->w1 = arg1;
                }
                if (var_s4 == spCC) {
                    temp_s0_9 = *arg0;
                    *arg0 = temp_s0_9 + 8;
                    ((T023801BDA6CGfx *)temp_s0_9)->w1 = 0;
                    ((T023801BDA6CGfx *)temp_s0_9)->w0 = 0xE7000000;
                    temp_f12 = (f32) ((f64) D_80282D20 + temp_f28);
                    D_80282D20 = temp_f12;
                    temp_f10 = sinf(temp_f12) * 63.0f;
                    temp_v0_3 = *arg0;
                    *arg0 = temp_v0_3 + 8;
                    ((T023801BDA6CGfx *)temp_v0_3)->w0 = 0xFA000000;
                    ((T023801BDA6CGfx *)temp_v0_3)->w1 = (s32) (((u32) (temp_f10 + 192.0f) << 0x18) | sp78);
                }
                temp_s0_10 = *arg0;
                *arg0 = temp_s0_10 + 8;
                ((T023801BDA6CGfx *)temp_s0_10)->w0 = 0x06000000;
                ((T023801BDA6CGfx *)temp_s0_10)->w1 = (s32) ((T023801BDA6CGlyph *)temp_s3)->image;
                if (var_s4 == spCC) {
                    temp_s0_11 = *arg0;
                    *arg0 = temp_s0_11 + 8;
                    ((T023801BDA6CGfx *)temp_s0_11)->w1 = 0;
                    ((T023801BDA6CGfx *)temp_s0_11)->w0 = 0xE7000000;
                    temp_s0_12 = *arg0;
                    *arg0 = temp_s0_12 + 8;
                    ((T023801BDA6CGfx *)temp_s0_12)->w0 = 0xFA000000;
                    ((T023801BDA6CGfx *)temp_s0_12)->w1 = sp74;
                }
                if (var_s6 != 0) {
                    var_f0_2 = 25.0;
                } else {
                    var_f0_2 = (f64) (((T023801BDA6CGlyph *)temp_s3)->width * 10.0f);
                }
                var_f22 = (f32) ((f64) temp_f22 + (temp_f20 * var_f0_2));
            } else if (temp_v0_2 == 0x4A) {
                var_s6 = 1;
            } else {
                if (var_s6 != 0) {
                    advance = 50.0;
                } else {
                    advance = 30.0;
                }
                var_f22 = (f32) ((f64) var_f22 + ((f64) var_f26 * advance));
            }
            var_s4 += 1;
            var_s5 += 1;
        } while (var_s4 != spD0);
    }
    return var_s7;
}
