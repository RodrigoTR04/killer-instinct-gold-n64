/* DRAFT. Remaining diff: Mask pointer types, clipping arithmetic, stack and display-list scheduling differ. */
typedef struct { u32 w0, w1; } T023801BCB70Gfx;
void func_801BCB70(T023801BCB70Gfx **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u32 arg6, u32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, u8 arg14, u16 *arg15) {
    u32 sp12C;
    f32 spF4;
    f32 spF0;
    u16 spE6;
    s32 spE0;
    u32 sp94;
    s32 sp6C;
    s32 sp64;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 var_f10_2;
    f32 var_f12;
    f32 var_f14;
    f32 var_f26;
    f32 var_f2;
    f32 var_f6;
    f64 var_f10;
    s32 temp_a0;
    s32 temp_f4;
    s32 temp_f4_2;
    s32 temp_f6;
    s32 temp_f6_2;
    s32 temp_lo;
    s32 temp_t1_2;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t7_3;
    s32 temp_t7_4;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a1;
    u32 var_a3;
    s32 var_ra;
    s32 var_s3;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    u16 temp_t6_2;
    u16 var_v0;
    u32 temp_a1;
    u32 temp_a2;
    u32 temp_t1;
    u32 temp_t7;
    u32 temp_t7_2;
    u32 temp_v1_3;
    u32 var_s1;
    u32 var_s2;
    u32 var_s4;
    T023801BCB70Gfx *temp_t0;
    T023801BCB70Gfx *temp_t0_10;
    T023801BCB70Gfx *temp_t0_2;
    T023801BCB70Gfx *temp_t0_3;
    T023801BCB70Gfx *temp_t0_4;
    T023801BCB70Gfx *temp_t0_5;
    T023801BCB70Gfx *temp_t0_6;
    T023801BCB70Gfx *temp_t0_7;
    T023801BCB70Gfx *temp_t0_8;
    T023801BCB70Gfx *temp_t0_9;
    T023801BCB70Gfx *var_t0;

    temp_f2 = (f32) arg13;
    temp_f12 = ((f32) arg5 * temp_f2) / 1024.0f;
    temp_t0 = *arg0;
    var_v0 = 1;
    var_t0 = temp_t0 + 1;
    var_f6 = (f32) arg6;
    ((T023801BCB70Gfx *)temp_t0)->w0 = 0xFA000000;
    temp_f24 = (var_f6 * temp_f2) / 1024.0f;
    ((T023801BCB70Gfx *)temp_t0)->w1 = (s32) ((arg14 << 0x18) | (arg14 << 0x10) | (arg14 << 8) | 0xFF);
    if (temp_f12 < 0.0f) {
        spF0 = -temp_f12;
        spE0 = 0x200;
        arg5 = -arg5;
    } else {
        spF0 = temp_f12;
        spE0 = 0;
    }
    sp12C = 0;
    var_f26 = 0.0f;
    temp_t7 = arg9 - arg7;
    sp94 = temp_t7;
    if (temp_t7 != 0) {
        spF4 = temp_f12;
        do {
            var_s4 = arg8;
            var_f12 = arg12;
            var_ra = 0;
            if (var_s4 < arg10) {
                spE6 = var_v0;
                do {
                    temp_v1 = var_ra * 2;
                    var_a3 = 1;
                    if (arg15[var_ra] & var_v0) {
                        temp_f0 = var_f26 + arg11;
                        temp_lo = 0x100000 / arg13;
                        temp_f2_2 = temp_f0 + spF0;
                        temp_a1 = sp12C + arg5 + arg7;
                        var_f14 = temp_f2_2;
                        temp_a0 = sp12C + arg7;
                        var_f10 = (f64) arg7;
                        temp_a2 = arg9 - 1;
                        temp_t1 = arg10 - 1;

                        temp_v0 = temp_lo & 0xFFFF;
                        var_s3 = 0;
                        var_s1 = temp_a2;
                        var_s2 = temp_t1;
                        temp_f4 = (s32) (temp_f0 * 4.0f);
                        sp6C = ((s32) ((f32) (((f64) (f32) sp12C - 0.5) + var_f10) * 32.0f) + spE0) & 0xFFFF;
                        sp64 = (temp_v0 << 0x10) | temp_v0;
                        temp_t6 = (s32) (temp_f4 * temp_lo) >> 7;
                        if (arg15[var_ra + 1] & var_v0) {
loop_13:
                            temp_v0_2 = (var_a3 + 1) & 0xFFFF;
                            temp_t6_2 = arg15[var_ra + temp_v0_2];
                            var_a3 = temp_v0_2;
                            if (temp_t6_2 & var_v0) {
                                if (temp_v0_2 < 5) {
                                    goto loop_13;
                                }
                            }
                        }
                        if (temp_a0 != 0) {
                            var_s3 = temp_a0;
                        }
                        temp_v1_2 = var_s4 - 1;
                        if (temp_a1 < temp_a2) {
                            var_s1 = temp_a1;
                        }
                        if (temp_v1_2 > 0) {
                            var_a1 = temp_v1_2;
                        } else {
                            var_a1 = 0;
                        }
                        temp_t0_2 = var_t0 + 1;
                        temp_v1_3 = var_s4 + (arg6 * var_a3);
                        if (temp_v1_3 < temp_t1) {
                            var_s2 = temp_v1_3;
                        }
                        temp_t0_3 = temp_t0_2 + 1;
                        if (!(temp_f2_2 < 640.0f)) {
                            var_f14 = 640.0f;
                        }
                        temp_t0_4 = temp_t0_3 + 1;
                        temp_t1_2 = ((((s32) ((var_s1 - var_s3) + 8) >> 3) & 0x1FF) << 9) | 0xF5480000;
                        temp_f0_2 = ((f32) var_a3 * temp_f24) + var_f12;
                        var_f2 = temp_f0_2;
                        temp_t0_5 = temp_t0_4 + 1;
                        if (!(temp_f0_2 < 480.0f)) {
                            var_f2 = 480.0f;
                        }
                        ((T023801BCB70Gfx *)var_t0)->w0 = (s32) (((arg3 - 1) & 0xFFF) | 0xFD480000);
                        temp_t3 = ((var_s3 * 4) & 0xFFF) << 0xC;
                        ((T023801BCB70Gfx *)var_t0)->w1 = arg1;
                        ((T023801BCB70Gfx *)temp_t0_2)->w1 = 0x07080140;
                        var_t0[1].w0 = temp_t1_2;
                        temp_t0_2[1].w0 = 0xE6000000;
                        temp_t7_3 = (var_a1 * 4) & 0xFFF;
                        ((T023801BCB70Gfx *)temp_t0_3)->w1 = 0;
                        temp_t0_3[1].w0 = (s32) (temp_t3 | 0xF4000000 | temp_t7_3);
                        temp_v0_3 = ((var_s1 * 4) & 0xFFF) << 0xC;
                        temp_t9 = (var_s2 * 4) & 0xFFF;
                        temp_f6 = (s32) (var_f14 * 4.0f);
                        temp_t0_6 = temp_t0_5 + 1;
                        ((T023801BCB70Gfx *)temp_t0_4)->w1 = (s32) (temp_v0_3 | 0x07000000 | temp_t9);
                        temp_t0_4[1].w0 = 0xE7000000;
                        temp_t0_7 = temp_t0_6 + 1;
                        ((T023801BCB70Gfx *)temp_t0_5)->w1 = 0;
                        temp_t0_5[1].w0 = temp_t1_2;
                        temp_t0_8 = temp_t0_7 + 1;
                        ((T023801BCB70Gfx *)temp_t0_6)->w1 = 0x80140;
                        temp_t0_6[1].w0 = (s32) (temp_t3 | 0xF2000000 | temp_t7_3);
                        ((T023801BCB70Gfx *)temp_t0_7)->w1 = (s32) (temp_v0_3 | temp_t9);
                        temp_t0_9 = temp_t0_8 + 1;
                        if (temp_f6 > 0) {
                            var_a0 = temp_f6;
                        } else {
                            var_a0 = 0;
                        }
                        temp_t0_10 = temp_t0_9 + 1;
                        var_a0_2 = 0;
                        var_v0_2 = 0;
                        temp_f4_2 = (s32) (var_f2 * 4.0f);
                        temp_f6_2 = (s32) (var_f12 * 4.0f);
                        if (temp_f4_2 > 0) {
                            var_v0_2 = temp_f4_2;
                        }
                        temp_t0_7[1].w0 = (s32) ((var_v0_2 & 0xFFF) | 0xE4000000 | ((var_a0 & 0xFFF) << 0xC));
                        if (temp_f4 > 0) {
                            var_a0_2 = temp_f4;
                        }
                        if (temp_f6_2 > 0) {
                            var_v0_3 = temp_f6_2;
                        } else {
                            var_v0_3 = 0;
                        }
                        ((T023801BCB70Gfx *)temp_t0_8)->w1 = (s32) ((var_v0_3 & 0xFFF) | ((var_a0_2 & 0xFFF) << 0xC));
                        temp_t0_8[1].w0 = 0xB3000000;
                        if (temp_t6 < 0) {
                            var_a0_3 = temp_t6;
                        } else {
                            var_a0_3 = 0;
                        }
                        var_v0_4 = 0;
                        temp_t7_4 = (s32) (temp_f6_2 * temp_lo) >> 7;
                        if (temp_t7_4 < 0) {
                            var_v0_4 = temp_t7_4;
                        }
                        ((T023801BCB70Gfx *)temp_t0_9)->w1 = (s32) ((((s32) ((f32) ((f64) (f32) var_s4 - 0.5) * 32.0f) - var_v0_4) & 0xFFFF) | ((sp6C - var_a0_3) << 0x10));
                        temp_t0_9[1].w0 = 0xB2000000;
                        var_t0 = temp_t0_10 + 1;
                        ((T023801BCB70Gfx *)temp_t0_10)->w1 = sp64;
                    }
                    var_f10_2 = (f32) var_a3;
                    var_s4 += arg6 * var_a3;

                    var_ra += var_a3;
                    var_f12 += temp_f24 * var_f10_2;
                } while (var_s4 < arg10);
                var_v0 = spE6;
            }
            var_v0 = (var_v0 * 2) & 0xFFFF;
            temp_t7_2 = sp12C + arg5;
            sp12C = temp_t7_2;
            var_f26 += spF4;
        } while (temp_t7_2 < sp94);
    }
    *arg0 = var_t0;
}
