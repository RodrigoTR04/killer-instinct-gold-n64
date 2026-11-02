/* T-149 DRAFT: 266 differing words, 1324/1320 bytes in the full TU. */
typedef struct { u32 w0, w1; } T023801BDA6CGfx;
typedef struct { u32 image; f32 width; } T023801BDA6CGlyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
f32 sinf(f32);
s32 strlen(u8 *);
extern T023801BDA6CGlyph D_80282A70[];
extern f32 D_80282D20;
extern f64 D_80292B50;

s32 func_801BDA6C(T023801BDA6CGfx **arg0, s32 arg1, u8 *arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, f32 arg10) {
    s32 spD0;
    s32 spCC;
    u32 alpha;
    s32 sp74;
    f32 temp_f10;
    f32 temp_f12;
    f32 var_f22;
    f64 temp_f20;

    f64 var_f0;
    u8 *temp_s1;
    s32 var_s4;
    s32 var_s6;
    s32 var_s7;
    s8 temp_v0_2;
    u8 *var_s5;
    T023801BDA6CGlyph *temp_s3;
    T023801BDA6CGfx *cmd;

    var_f22 = arg3;
    spCC = 0x7D0;
    var_s6 = 0;
    var_s7 = 0;
    spD0 = strlen(arg2);
    if (spD0 == 0) {
        return 0;
    }
    if (arg10 < 0.0f) {
        spCC = (s32) (-arg10 - 1.0f);
        arg10 = 1.0f;
    }
    if (arg10 != 1.0f) {
        guScale(arg1, arg10, arg10, 1.0f);
        var_s7 = 1;
    }
    alpha = arg9;
    cmd = (*arg0)++;
    cmd->w1 = 0;
    cmd->w0 = 0xE7000000;
    cmd = (*arg0)++;
    cmd->w0 = 0xFA000000;
    sp74 = (arg6 << 0x18) | (arg7 << 0x10) | (arg8 << 8) | alpha;
    cmd->w1 = sp74;
    cmd = (*arg0)++;
    cmd->w1 = 0xFFFDF6FB;
    cmd->w0 = 0xFCFFFFFF;
    cmd = (*arg0)++;
    cmd->w0 = 0xB6000000;
    cmd->w1 = 0x22000;
    if (alpha == 0xFF) {
        cmd = (*arg0)++;
        cmd->w0 = 0xB900031D;
        cmd->w1 = 0x0F0A4000;
    } else {
        cmd = (*arg0)++;
        cmd->w0 = 0xB900031D;
        cmd->w1 = 0x5041C8;
    }
    var_s4 = 0;
    if (spD0 > 0) {
        var_s5 = arg2;
        do {
            temp_v0_2 = *var_s5 - 0x20;
            if ((temp_v0_2 < 0x3B) && (temp_v0_2 >= 0) && (temp_s3 = &D_80282A70[temp_v0_2], (temp_s3->image != 0))) {
                temp_f20 = (f64) arg10;
                if (var_s6 != 0) {
                    var_f0 = 25.0;
                } else {
                    var_f0 = (f64) (temp_s3->width * 10.0f);
                }
                temp_s1 = (var_s7 << 6) + arg1;
                var_f22 = (f32) ((f64) var_f22 + (temp_f20 * var_f0));
                guTranslate(temp_s1, var_f22, arg4, arg5);
                cmd = (*arg0)++;
                var_s7 += 1;
                cmd->w0 = 0x01020040;
                cmd->w1 = (u32)temp_s1;
                if (arg10 != 1.0f) {
                    cmd = (*arg0)++;
                    cmd->w0 = 0x01000040;
                    cmd->w1 = (u32)arg1;
                }
                if (var_s4 == spCC) {
                    temp_f12 = D_80282D20;
                    cmd = (*arg0)++;
                    cmd->w1 = 0;
                    cmd->w0 = 0xE7000000;
                    temp_f12 = (f32) ((f64) temp_f12 + D_80292B50);
                    D_80282D20 = temp_f12;
                    temp_f10 = sinf(temp_f12) * 63.0f;
                    cmd = (*arg0)++;
                    cmd->w0 = 0xFA000000;
                    cmd->w1 = (s32) (((u32) (temp_f10 + 192.0f) << 0x18) | alpha);
                }
                cmd = (*arg0)++;
                cmd->w0 = 0x06000000;
                cmd->w1 = (s32) temp_s3->image;
                if (var_s4 == spCC) {
                    cmd = (*arg0)++;
                    cmd->w1 = 0;
                    cmd->w0 = 0xE7000000;
                    cmd = (*arg0)++;
                    cmd->w0 = 0xFA000000;
                    cmd->w1 = sp74;
                }
                if (var_s6 != 0) {
                    var_f0 = 25.0;
                } else {
                    var_f0 = (f64) (temp_s3->width * 10.0f);
                }
                var_f22 = (f32) ((f64) var_f22 + (temp_f20 * var_f0));
            } else if (temp_v0_2 == 0x4A) {
                var_s6 = 1;
            } else {
                if (var_s6 != 0) {
                    var_f0 = 50.0;
                } else {
                    var_f0 = 30.0;
                }
                var_f22 = (f32) ((f64) var_f22 + ((f64) arg10 * var_f0));
            }
            var_s4 += 1;
            var_s5 += 1;
        } while (var_s4 != spD0);
    }
    return var_s7;
}
