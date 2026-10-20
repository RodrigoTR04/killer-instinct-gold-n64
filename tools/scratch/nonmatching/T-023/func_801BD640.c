/* T-076: nonmatching, 191 differing words including size penalty; 1068 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
typedef struct { u32 w0, w1; } T023801BD640Gfx;
typedef struct { u32 image; f32 width; } T023801BD640Glyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern T023801BD640Glyph D_80282A70[];

s32 func_801BD640(T023801BD640Gfx **arg0, u8 *arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9) {
    f32 var_f20;
    f64 var_f0;
    f64 var_f0_2;
    f64 var_f18;
    u8 *temp_s1;
    s32 temp_t2;
    s32 var_s3;
    s32 var_s5;
    u8 *var_s4;
    u8 temp_t1;
    u32 var_v1;
    T023801BD640Glyph *temp_s0;
    T023801BD640Gfx *temp_v0;

    temp_v0 = *arg0;
    var_f20 = arg3;
    *arg0 = temp_v0 + 1;
    ((T023801BD640Gfx *)temp_v0)->w0 = 0xE7000000;
    ((T023801BD640Gfx *)temp_v0)->w1 = 0;
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    ((T023801BD640Gfx *)temp_v0)->w0 = 0xFA000000;
    ((T023801BD640Gfx *)temp_v0)->w1 = (s32) ((arg6 << 0x18) | (arg7 << 0x10) | (arg8 << 8) | arg9);
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    ((T023801BD640Gfx *)temp_v0)->w0 = 0xFCFFFFFF;
    ((T023801BD640Gfx *)temp_v0)->w1 = 0xFFFDF6FB;
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    var_s3 = 0;
    ((T023801BD640Gfx *)temp_v0)->w1 = 0x20000;
    ((T023801BD640Gfx *)temp_v0)->w0 = 0xB6000000;
    if (arg9 == 0xFF) {
        temp_v0 = *arg0;
        *arg0 = temp_v0 + 1;
        ((T023801BD640Gfx *)temp_v0)->w0 = 0xB900031D;
        ((T023801BD640Gfx *)temp_v0)->w1 = 0x552048;
    } else {
        temp_v0 = *arg0;
        *arg0 = temp_v0 + 1;
        ((T023801BD640Gfx *)temp_v0)->w0 = 0xB900031D;
        ((T023801BD640Gfx *)temp_v0)->w1 = 0x5041C8;
    }
    guScale(arg1, 0.75f, 0.75f, 1.0f);
    temp_v0 = *arg0;
    *arg0 = temp_v0 + 1;
    ((T023801BD640Gfx *)temp_v0)->w0 = 0x01020040;
    ((T023801BD640Gfx *)temp_v0)->w1 = (u32)arg1;
    temp_t1 = *arg2;
    var_s5 = 1;
    var_s4 = arg2;
    var_v1 = temp_t1 & 0xFF;
    if (temp_t1 != 0) {
        do {
            temp_t2 = (var_v1 - 0x20) & 0xFF;
            if ((temp_t2 < 0x3B) && (temp_t2 > 0)) {
                temp_s0 = &D_80282A70[temp_t2];
                if (((T023801BD640Glyph *)temp_s0)->image != 0) {
                    if (var_s3 != 0) {
                        var_f0 = (f64) var_s3 * 5.0;
                    } else {
                        var_f0 = (f64) (((T023801BD640Glyph *)temp_s0)->width * 10.0f);
                    }
                    temp_s1 = (var_s5 << 6) + arg1;
                    var_f20 = (f32) ((f64) var_f20 + var_f0);
                    guTranslate(temp_s1, var_f20, arg4, arg5);
                    temp_v0 = *arg0;
                    *arg0 = temp_v0 + 1;
                    ((T023801BD640Gfx *)temp_v0)->w1 = (u32)temp_s1;
                    ((T023801BD640Gfx *)temp_v0)->w0 = 0x01040040;
                    temp_v0 = *arg0;
                    *arg0 = temp_v0 + 1;
                    ((T023801BD640Gfx *)temp_v0)->w0 = 0x06000000;
                    ((T023801BD640Gfx *)temp_v0)->w1 = (s32) ((T023801BD640Glyph *)temp_s0)->image;
                    temp_v0 = *arg0;
                    *arg0 = temp_v0 + 1;
                    var_s5 += 1;
                    ((T023801BD640Gfx *)temp_v0)->w0 = 0xBD000000;
                    ((T023801BD640Gfx *)temp_v0)->w1 = 0;
                    if (var_s3 != 0) {
                        var_f18 = (f64) var_f20 + 25.0;
                    } else {
                        var_f18 = (f64) var_f20 + (f64) (((T023801BD640Glyph *)temp_s0)->width * 10.0f);
                    }
                    goto block_24;
                }
            }
            if (var_v1 == 9) {
                var_f20 = (f32) ((f64) arg3 + ((f64) (((s32) (f32) ((f64) (var_f20 - arg3) / 400.0) * 0x14) + 0x14) * 2.5 * 8.0));
            } else if (var_v1 == 0x6A) {
                var_s3 = 5;
            } else if (var_v1 == 0x6B) {
                var_s3 = 2;
            } else {
                if (var_s3 != 0) {
                    var_f0_2 = 50.0;
                } else {
                    var_f0_2 = 30.0;
                }
                var_f18 = (f64) var_f20 + var_f0_2;
block_24:
                var_f20 = (f32) var_f18;
            }
            var_v1 = *(u8 *)(var_s4 + 0x1);
            var_s4 += 1;
        } while (var_v1 != 0);
    }
    return var_s5;
}
