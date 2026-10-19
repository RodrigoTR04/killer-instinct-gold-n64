/* DRAFT. Remaining diff: Clipping arithmetic, stack frame, temporary registers and display-list stores differ. */
typedef struct { u32 w0, w1; } T023801BC1B0Gfx;
void func_801BC1B0(u8 **arg0, s32 arg1, s32 arg2, u32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u32 arg8, s32 arg9, u32 arg10, f32 arg11, f32 arg12, s32 arg13, s32 arg14) {
    u32 sp194;
    s32 sp14C;
    s32 sp148;
    s32 spBC;
    u32 spB8;
    s32 spB4;
    u32 spB0;
    u32 spAC;
    u32 spA4;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp74;
    s32 sp70;
    s32 sp64;
    s32 sp58;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f24;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    f32 var_f8;
    f64 var_f6;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_f10;
    s32 temp_f4;
    s32 temp_lo;
    s32 temp_t0;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_t9_2;
    s32 temp_t9_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_s0;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;
    u32 temp_t8;
    u32 temp_t9;
    u32 temp_v1;
    u32 var_a2;
    u32 var_s1;
    u32 var_t5;
    u8 *temp_v0;
    u8 *temp_v0_10;
    u8 *temp_v0_11;
    u8 *temp_v0_12;
    u8 *temp_v0_13;
    u8 *temp_v0_14;
    u8 *temp_v0_15;
    u8 *temp_v0_16;
    u8 *temp_v0_17;
    u8 *temp_v0_18;
    u8 *temp_v0_19;
    u8 *temp_v0_20;
    u8 *temp_v0_21;
    u8 *temp_v0_22;
    u8 *temp_v0_23;
    u8 *temp_v0_24;
    u8 *temp_v0_25;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v0_8;
    u8 *temp_v0_9;
    u8 *var_v0;
    u8 *var_v0_2;

    temp_f12 = (f32) arg13;
    temp_f0 = ((f32) arg5 * temp_f12) / 256.0f;
    var_v0 = *arg0;
    sp148 = 1;
    temp_f2 = temp_f0;
    if (arg14 != 0) {
        sp14C = 0x2010 - (arg5 << 5);
        arg5 = -arg5;
        var_f14 = -temp_f2;
        var_f16 = arg11 - ((f32) -((s32) (arg13 * 0x10) >> 8) - var_f14);
    } else {
        var_f14 = temp_f0;
        sp148 = 2;
        sp14C = 0;
        var_f16 = arg11;
    }
    var_f0 = 0.0f;
    sp194 = 0;
    temp_t8 = arg9 - arg7;
    spB8 = temp_t8;
    if (temp_t8 != 0) {
        do {
            var_a2 = arg8;
            var_f18 = arg12;
            if (arg8 < arg10) {
                temp_lo = 0x100000 / arg13;
                temp_f4 = (s32) (var_f0 + var_f16);
                spB0 = sp194 + arg5 + arg7;
                spA4 = arg10 - 1;
                spAC = arg9 - 1;
                spBC = temp_lo;
                sp58 = temp_lo;
                sp9C = temp_f4;
                sp98 = (s32) ((f32) temp_f4 + temp_f2);
                var_f6 = (f64) arg7;
                sp94 = (arg3 - 1) & 0xFFF;
                if (arg7 < 0) {
                    var_f6 += 4294967296.0;
                }
                sp74 = (((s32) (f32) (((f64) (f32) sp194 - 0.5) + var_f6) << 5) + sp14C) & 0xFFFF;
                temp_a0 = sp58 & 0xFFFF;
                sp70 = (temp_a0 << 0x10) | temp_a0;
                var_f8 = (f32) arg6;
                if (arg6 < 0) {
                    var_f8 += 4294967296.0f;
                }
                spB4 = sp194 + arg7;
                sp64 = (s32) (temp_f4 * sp58) >> 7;
                do {
                    temp_f24 = (f32) (s32) ((var_f8 * temp_f12) / 256.0f) + var_f18;
                    var_s6 = sp98;
                    var_s0 = 0;
                    var_s4 = 0;
                    var_s5 = (s32) temp_f24;
                    temp_f10 = (s32) var_f18;
                    var_f18 = temp_f24;
                    if (spB4 != 0) {
                        var_s0 = spB4;
                    }
                    temp_v1_2 = var_a2 - 1;
                    if (spB0 < spAC) {
                        var_t5 = spB0;
                    } else {
                        var_t5 = spAC;
                    }
                    if (temp_v1_2 > 0) {
                        var_s4 = temp_v1_2;
                    }
                    temp_v1 = var_a2 + arg6;
                    if (temp_v1 < spA4) {
                        var_s1 = temp_v1;
                    } else {
                        var_s1 = spA4;
                    }
                    if (sp98 >= 0xA00) {
                        var_s6 = 0xA00;
                    }
                    if (var_s5 >= 0x780) {
                        var_s5 = 0x780;
                    }
                    if (arg2 != 0) {
                        if (arg2 != 2) {
                            temp_v0 = var_v0 + 8;
                            temp_v0_2 = temp_v0 + 8;
                            temp_t2 = var_t5 - var_s0;
                            ((T023801BC1B0Gfx *)var_v0)->w0 = (s32) (sp94 | 0xFD100000);
                            ((T023801BC1B0Gfx *)var_v0)->w1 = arg1;
                            temp_t3 = ((((s32) ((temp_t2 * 2) + 9) >> 3) & 0x1FF) << 9) | 0xF5100000;
                            ((T023801BC1B0Gfx *)temp_v0)->w1 = 0x07080200;
                            *(u32 *)(var_v0 + 0x8) = temp_t3;
                            temp_v1_3 = ((var_s0 * 4) & 0xFFF) << 0xC;
                            temp_t8_2 = (var_s4 * 4) & 0xFFF;
                            temp_v0_3 = temp_v0_2 + 8;
                            *(u32 *)(temp_v0 + 0x8) = 0xE6000000;
                            ((T023801BC1B0Gfx *)temp_v0_2)->w1 = 0;
                            *(u32 *)(temp_v0_2 + 0x8) = (s32) (temp_v1_3 | 0xF4000000 | temp_t8_2);
                            temp_a0_2 = ((var_t5 * 4) & 0xFFF) << 0xC;
                            temp_t9_2 = (var_s1 * 4) & 0xFFF;
                            temp_v0_4 = temp_v0_3 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_3)->w1 = (s32) (temp_a0_2 | 0x07000000 | temp_t9_2);
                            temp_v0_5 = temp_v0_4 + 8;
                            *(u32 *)(temp_v0_3 + 0x8) = 0xE7000000;
                            ((T023801BC1B0Gfx *)temp_v0_4)->w1 = 0;
                            ((T023801BC1B0Gfx *)temp_v0_5)->w1 = 0x80200;
                            *(u32 *)(temp_v0_4 + 0x8) = temp_t3;
                            temp_v0_6 = temp_v0_5 + 8;
                            temp_v0_7 = temp_v0_6 + 8;
                            *(u32 *)(temp_v0_5 + 0x8) = (s32) (temp_v1_3 | 0xF2000000 | temp_t8_2);
                            ((T023801BC1B0Gfx *)temp_v0_6)->w1 = (s32) (temp_a0_2 | temp_t9_2);
                            temp_t0 = (((s32) (((s32) (temp_t2 + 1) >> 1) + 7) >> 3) & 0x1FF) << 9;
                            ((T023801BC1B0Gfx *)temp_v0_7)->w1 = (s32) (arg1 + (arg3 * arg4 * 2));
                            *(u32 *)(temp_v0_6 + 0x8) = (s32) ((((arg3 >> 1) - 1) & 0xFFF) | 0xFD880000);
                            temp_v0_8 = temp_v0_7 + 8;
                            temp_v1_4 = var_s0 + 0x10;
                            *(u32 *)(temp_v0_7 + 0x8) = (s32) (temp_t0 | 0xF5880000 | 0x1C0);
                            temp_v0_9 = temp_v0_8 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_8)->w1 = 0x07080200;
                            temp_t2_2 = var_t5 + 0x10;
                            temp_v0_10 = temp_v0_9 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_9)->w1 = 0;
                            *(u32 *)(temp_v0_8 + 0x8) = 0xE6000000;
                            *(u32 *)(temp_v0_9 + 0x8) = (s32) ((((temp_v1_4 * 2) & 0xFFF) << 0xC) | 0xF4000000 | temp_t8_2);
                            temp_v0_11 = temp_v0_10 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_10)->w1 = (s32) ((((temp_t2_2 * 2) & 0xFFF) << 0xC) | 0x07000000 | temp_t9_2);
                            *(u32 *)(temp_v0_10 + 0x8) = 0xE7000000;
                            temp_v0_12 = temp_v0_11 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_11)->w1 = 0;
                            *(u32 *)(temp_v0_11 + 0x8) = (s32) (temp_t0 | 0xF5800000 | 0x1C0);
                            ((T023801BC1B0Gfx *)temp_v0_12)->w1 = 0x01080200;
                            var_v0_2 = temp_v0_12 + 8;
                            *(u32 *)(temp_v0_12 + 0x8) = (s32) ((((temp_v1_4 * 4) & 0xFFF) << 0xC) | 0xF2000000 | temp_t8_2);
                            ((T023801BC1B0Gfx *)var_v0_2)->w1 = (s32) ((((temp_t2_2 * 4) & 0xFFF) << 0xC) | 0x01000000 | temp_t9_2);
                        } else {
                            temp_a0_3 = (arg2 & 7) << 0x15;
                            ((T023801BC1B0Gfx *)var_v0)->w0 = (s32) (temp_a0_3 | 0xFD000000 | 0x80000 | sp94);
                            ((T023801BC1B0Gfx *)var_v0)->w1 = arg1;
                            temp_v0_13 = var_v0 + 8;
                            temp_t1 = temp_a0_3 | 0xF5000000 | 0x80000 | ((((s32) ((var_t5 - var_s0) + 8) >> 3) & 0x1FF) << 9);
                            *(u32 *)(var_v0 + 0x8) = temp_t1;
                            temp_t9_3 = (sp148 & 3) << 8;
                            ((T023801BC1B0Gfx *)temp_v0_13)->w1 = (s32) (temp_t9_3 | 0x07080000 | 0x70);
                            temp_v0_14 = temp_v0_13 + 8;
                            temp_v1_5 = ((var_s0 * 4) & 0xFFF) << 0xC;
                            temp_t6 = (var_s4 * 4) & 0xFFF;
                            temp_v0_15 = temp_v0_14 + 8;
                            *(u32 *)(temp_v0_13 + 0x8) = 0xE6000000;
                            ((T023801BC1B0Gfx *)temp_v0_14)->w1 = 0;
                            *(u32 *)(temp_v0_14 + 0x8) = (s32) (temp_v1_5 | 0xF4000000 | temp_t6);
                            temp_a0_4 = ((var_t5 * 4) & 0xFFF) << 0xC;
                            temp_t8_3 = (var_s1 * 4) & 0xFFF;
                            temp_v0_16 = temp_v0_15 + 8;
                            ((T023801BC1B0Gfx *)temp_v0_15)->w1 = (s32) (temp_a0_4 | 0x07000000 | temp_t8_3);
                            temp_v0_17 = temp_v0_16 + 8;
                            var_v0_2 = temp_v0_17 + 8;
                            *(u32 *)(temp_v0_15 + 0x8) = 0xE7000000;
                            ((T023801BC1B0Gfx *)temp_v0_16)->w1 = 0;
                            ((T023801BC1B0Gfx *)temp_v0_17)->w1 = (s32) (temp_t9_3 | 0x80000 | 0x70);
                            *(u32 *)(temp_v0_16 + 0x8) = temp_t1;
                            ((T023801BC1B0Gfx *)var_v0_2)->w1 = (s32) (temp_a0_4 | temp_t8_3);
                            *(u32 *)(temp_v0_17 + 0x8) = (s32) (temp_v1_5 | 0xF2000000 | temp_t6);
                        }
                    } else {
                        temp_v0_18 = var_v0 + 8;
                        temp_a0_5 = (arg2 & 7) << 0x15;
                        ((T023801BC1B0Gfx *)var_v0)->w0 = (s32) (temp_a0_5 | 0xFD000000 | 0x100000 | sp94);
                        ((T023801BC1B0Gfx *)var_v0)->w1 = arg1;
                        temp_t1_2 = temp_a0_5 | 0xF5000000 | 0x100000 | ((((s32) (((var_t5 - var_s0) * 2) + 9) >> 3) & 0x1FF) << 9);
                        ((T023801BC1B0Gfx *)temp_v0_18)->w1 = 0x07080200;
                        temp_v0_19 = temp_v0_18 + 8;
                        *(u32 *)(var_v0 + 0x8) = temp_t1_2;
                        temp_v1_6 = ((var_s0 * 4) & 0xFFF) << 0xC;
                        temp_t7 = (var_s4 * 4) & 0xFFF;
                        ((T023801BC1B0Gfx *)temp_v0_19)->w1 = 0;
                        *(u32 *)(temp_v0_18 + 0x8) = 0xE6000000;
                        temp_v0_20 = temp_v0_19 + 8;
                        *(u32 *)(temp_v0_19 + 0x8) = (s32) (temp_v1_6 | 0xF4000000 | temp_t7);
                        temp_a0_6 = ((var_t5 * 4) & 0xFFF) << 0xC;
                        temp_t8_4 = (var_s1 * 4) & 0xFFF;
                        temp_v0_21 = temp_v0_20 + 8;
                        ((T023801BC1B0Gfx *)temp_v0_20)->w1 = (s32) (temp_a0_6 | 0x07000000 | temp_t8_4);
                        temp_v0_22 = temp_v0_21 + 8;
                        *(u32 *)(temp_v0_20 + 0x8) = 0xE7000000;
                        var_v0_2 = temp_v0_22 + 8;
                        ((T023801BC1B0Gfx *)temp_v0_21)->w1 = 0;
                        ((T023801BC1B0Gfx *)temp_v0_22)->w1 = 0x80200;
                        *(u32 *)(temp_v0_21 + 0x8) = temp_t1_2;
                        ((T023801BC1B0Gfx *)var_v0_2)->w1 = (s32) (temp_a0_6 | temp_t8_4);
                        *(u32 *)(temp_v0_22 + 0x8) = (s32) (temp_v1_6 | 0xF2000000 | temp_t7);
                    }
                    temp_v0_23 = var_v0_2 + 8;
                    temp_v0_24 = temp_v0_23 + 8;
                    if (var_s6 > 0) {
                        var_a1 = var_s6;
                    } else {
                        var_a1 = 0;
                    }
                    if (var_s5 > 0) {
                        var_v1 = var_s5;
                    } else {
                        var_v1 = 0;
                    }
                    *(u32 *)(var_v0_2 + 0x8) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_a1 & 0xFFF) << 0xC));
                    if (sp9C > 0) {
                        var_a1_2 = sp9C;
                    } else {
                        var_a1_2 = 0;
                    }
                    if (temp_f10 > 0) {
                        var_v1_2 = temp_f10;
                    } else {
                        var_v1_2 = 0;
                    }
                    ((T023801BC1B0Gfx *)temp_v0_23)->w1 = (s32) ((var_v1_2 & 0xFFF) | ((var_a1_2 & 0xFFF) << 0xC));
                    *(u32 *)(temp_v0_23 + 0x8) = 0xB3000000;
                    temp_v0_25 = temp_v0_24 + 8;
                    var_a1_3 = 0;
                    if (sp64 < 0) {
                        var_a1_3 = sp64;
                    }
                    var_v1_3 = 0;
                    temp_t6_2 = (s32) (temp_f10 * spBC) >> 7;
                    if (temp_t6_2 < 0) {
                        var_v1_3 = temp_t6_2;
                    }
                    ((T023801BC1B0Gfx *)temp_v0_24)->w1 = (s32) ((((s32) ((f32) ((f64) (f32) var_a2 - 0.5) * 32.0f) - var_v1_3) & 0xFFFF) | ((sp74 - var_a1_3) << 0x10));
                    *(u32 *)(temp_v0_24 + 0x8) = 0xB2000000;
                    var_a2 = temp_v1;
                    var_v0 = temp_v0_25 + 8;
                    ((T023801BC1B0Gfx *)temp_v0_25)->w1 = sp70;
                } while (temp_v1 < arg10);
            }
            var_f0 += var_f14;
            temp_t9 = sp194 + arg5;
            sp194 = temp_t9;
        } while (temp_t9 < spB8);
    }
    *arg0 = var_v0;
}
