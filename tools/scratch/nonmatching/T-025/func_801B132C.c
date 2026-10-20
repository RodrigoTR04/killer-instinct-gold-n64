/* T-076: nonmatching, 237 differing words including size penalty; 1144 compiled bytes.
 * See T-076/REPORT.md for TU compilation and remaining differences. */
extern s32 func_801BE540(s32, s32, s32, f32, f32, f32, u8, u8, u8, u8, f32);
extern f32 sinf(f32);
extern u8 D_80127D50;
extern s32 D_801D3000[];
extern s32 D_801D3020;
extern f32 D_801D3024;
extern s32 D_80282A60;
extern u8 D_80292878[];
extern f64 D_80292920;
extern f32 D_80292928;
extern f32 D_8029292C;
extern f32 D_80292930;
extern f64 D_80292938;
extern f64 D_80292940;
extern f32 D_80292948;
extern f32 D_8029294C;
extern f64 D_80292950;

s32 func_801B132C(s32 arg0, s32 arg1, s32 arg2, u32 arg3) {
    f32 scale;
    f64 var_f6;
    s32 temp_a0;
    s8 temp_f10;
    s32 temp_v0;
    s32 var_a1;
    s32 position;
    s32 i;
    s32 matrices;
    s32 var_v0;
    s32 var_v0_2;
    s8 pulse;

    matrices = 0;
    var_f6 = (f64) arg3;
    temp_f10 = (s32) (sinf((f32) (var_f6 * D_80292920 * 6.0)) * 63.0f);
    i = 0;
    pulse = (s8) temp_f10;
    if (D_80282A60 == 0) {
        temp_v0 = func_801BE540(arg0, arg2, (s32)D_80292878, 0, D_80292928, D_8029292C, 0, 0, 0, ((s8) temp_f10 * 2) + 0x80, 1.0f) & 0xFF;
        D_801D3024 = D_80292930;
        return temp_v0;
    }
    if (D_801D3024 < 1.0f) {
        D_801D3024 = (f32) ((f64) D_801D3024 + D_80292938);
    }
    if (D_801D3020 == -0x2710) {
        D_801D3020 = (D_80127D50 * 0x10) + 8;
    }
    position = D_801D3020 + 0x10;
    do {
        position -= 0x10;
        var_v0 = 0;
        if (position >= -0x13) {
            scale = D_80292948;
            if (position < -0x10) {
                var_v0 = ((position << 5) + 0x280) & 0xFF;
            } else if (position < 0) {
                var_v0 = 0x80;
            } else if (position < 8) {
                var_v0 = ((position * 0x10) + 0x80) & 0xFF;
                scale = (f32) ((f64) ((f32) position / 20.0f) + D_80292940);
            } else if (position == 8) {
                scale = 1.0f;
                var_v0 = (pulse + 0xBF) & 0xFF;
            } else if (position < 0x10) {
                var_v0 = (0x180 - (position * 0x10)) & 0xFF;
                scale = (f32) (1.5 - (f64) ((f32) position / 20.0f));
            } else if (position < 0x20) {
                var_v0 = 0x80;
            } else if (position < 0x24) {
                var_v0 = (0x480 - (position << 5)) & 0xFF;
            }
        }
        if (var_v0 != 0) {
            matrices = (matrices + func_801BE540(arg0, (matrices << 6) + arg2, D_801D3000[i], 0.0f, (f32) (((s32) (position * 0x17) >> 3) - 0x1F4), D_8029294C, 0, 0, 0, var_v0, scale * D_801D3024)) & 0xFF;
        }
        i += 1;
    } while (i != 8);
    temp_a0 = D_801D3020 - ((D_80127D50 * 0x10) + 8);
    var_a1 = 4;
    var_v0_2 = temp_a0;
    if (temp_a0 >= 0x29) {
        if (temp_a0 >= 0x41) {
            D_801D3020 -= 0x80;
            var_v0_2 = temp_a0 - 0x80;
        } else {
            var_a1 = 8;
        }
    }
    if (var_v0_2 < -0x28) {
        if (var_v0_2 < -0x40) {
            var_v0_2 += 0x80;
            D_801D3020 += 0x80;
        } else {
            var_a1 = 5;
        }
    }
    if ((var_v0_2 < var_a1) && (-var_a1 < var_v0_2)) {
        D_801D3020 -= var_v0_2;
        var_v0_2 = 0;
    }
    if (var_v0_2 < 0) {
        D_801D3020 = (s32) (D_801D3020 + var_a1) % 128;
    } else if (var_v0_2 > 0) {
        D_801D3020 = (s32) (D_801D3020 - var_a1) % 128;
    }
    return matrices;
}
