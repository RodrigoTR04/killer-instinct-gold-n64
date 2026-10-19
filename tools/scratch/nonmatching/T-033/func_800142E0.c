/* DRAFT. Remaining diff: 593 positional differing words; 2100/2400 bytes */
typedef struct { u32 command, value; } T033142E0Command;
extern u8 D_80044A24;
extern u32 D_8004A428[];
extern u8 D_8004AA28;
extern u8 D_80068930;
extern u8 D_801D7DF8;
extern u16 D_801D876C;

void func_800142E0(T033142E0Command **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    s32 sp18;
    f32 var_f0;
    f32 var_f12;
    s32 temp_a0_3;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_s4;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a1;
    s32 var_a1_2;
    s32 var_a1_3;
    s32 var_a1_4;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_s0;
    s32 var_s2;
    s32 var_s3;
    s32 var_t1;
    s32 var_t1_2;
    s32 var_t2;
    s32 var_t3;
    s32 var_t3_2;
    s32 var_t4;
    s32 var_t4_2;
    s32 var_v0;
    s32 var_v0_10;
    s32 var_v0_11;
    s32 var_v0_12;
    s32 var_v0_13;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1;
    T033142E0Command *temp_a0;
    T033142E0Command *temp_a0_2;
    T033142E0Command *temp_a0_4;
    T033142E0Command *temp_a2;
    T033142E0Command *temp_a2_10;
    T033142E0Command *temp_a2_11;
    T033142E0Command *temp_a2_12;
    T033142E0Command *temp_a2_13;
    T033142E0Command *temp_a2_14;
    T033142E0Command *temp_a2_15;
    T033142E0Command *temp_a2_16;
    T033142E0Command *temp_a2_17;
    T033142E0Command *temp_a2_18;
    T033142E0Command *temp_a2_19;
    T033142E0Command *temp_a2_20;
    T033142E0Command *temp_a2_21;
    T033142E0Command *temp_a2_22;
    T033142E0Command *temp_a2_23;
    T033142E0Command *temp_a2_24;
    T033142E0Command *temp_a2_25;
    T033142E0Command *temp_a2_26;
    T033142E0Command *temp_a2_27;
    T033142E0Command *temp_a2_28;
    T033142E0Command *temp_a2_29;
    T033142E0Command *temp_a2_2;
    T033142E0Command *temp_a2_30;
    T033142E0Command *temp_a2_31;
    T033142E0Command *temp_a2_3;
    T033142E0Command *temp_a2_4;
    T033142E0Command *temp_a2_5;
    T033142E0Command *temp_a2_6;
    T033142E0Command *temp_a2_7;
    T033142E0Command *temp_a2_8;
    T033142E0Command *temp_a2_9;
    T033142E0Command *temp_v1_6;
    T033142E0Command *var_a2;
    T033142E0Command *var_a2_2;
    T033142E0Command *var_a2_3;

    temp_a2 = (T033142E0Command *)(&D_80068930 + D_80044A24 * 0x640);
    var_f12 = arg6;
    *arg0 = temp_a2;
    temp_a2_2 = temp_a2 + 1;
    temp_a2[0].command = 0xE7000000;
    temp_a2[0].value = 0;
    temp_a2[1].command = 0xED000000;
    temp_a2_3 = temp_a2_2 + 1;
    temp_a2_4 = temp_a2_3 + 1;
    temp_a2_5 = temp_a2_4 + 1;
    var_s0 = 0;
    var_s2 = 0;
    var_s3 = 0x74;
    temp_a2_2[0].value = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
    temp_a2_3[0].value = 0xFFFE793C;
    temp_a2_2[1].command = 0xFCFFFFFF;
    temp_a2_3[1].command = (s32) ((((0x140 << D_8004AA28) - 1) & 0xFFF) | 0xFF100000);
    temp_a2_4[0].value = (s32) D_8004A428[D_80044A24];
    var_f0 = arg5;
    if (var_f12 < 0.0f) {
        do {
            var_f12 += 360.0f;
        } while (var_f12 < 0.0f);
    }
    if (var_f0 < 0.0f) {
        do {
            var_f0 += 360.0f;
        } while (var_f0 < 0.0f);
    }
    var_v0 = (s32) (var_f12 * 4.0f) % 240;
    if (var_v0 < 0) {
        var_v0 = 0;
    }
    temp_a2_6 = temp_a2_5 + 1;
    temp_a2_7 = temp_a2_6 + 1;
    if (var_f0 > 180.0f) {
        var_f0 -= 360.0f;
    }
    temp_a2_4[1].command = 0x2F300000;
    temp_a2_5[0].value = 0;
    temp_a2_5[1].command = 0xF7000000;
    temp_a2_6[0].value = 0;
    temp_a2_8 = temp_a2_7 + 1;
    temp_a2_7[0].value = 0;
    temp_a2_9 = temp_a2_8 + 1;
    temp_a2_10 = temp_a2_9 + 1;
    temp_s4 = (s32) (-var_f0 * 8.0f) + 0x28;
    temp_a2_6[1].command = (s32) (((temp_s4 & 0x3FF) * 4) | 0xF64FC000);
    temp_a2_8[0].value = 0x94290;
    temp_a2_7[1].command = 0xF5102200;
    temp_a2_8[1].command = 0xF5102200;
    sp18 = var_v0;
    temp_a2_9[0].value = 0x01094290;
    temp_a2_11 = temp_a2_10 + 1;
    temp_a2_9[1].command = 0xF2000000;
    temp_a2_10[0].value = 0x0110C074;
    temp_a2_12 = temp_a2_11 + 1;
    temp_a2_10[1].command = 0x2F002CC0;
    temp_a2_11[0].value = 0;
    temp_a2_12[0].value = 0xFFFCF279;
    temp_a2_11[1].command = 0xFCFFFFFF;
    temp_a2_13 = temp_a2_12 + 1;
    var_t3 = 0x12C - ((s32) (sp18 * 0xA) / 6);
    temp_a2_13[0].value = 0x803AC910;
    temp_a2_12[1].command = 0xFD100043;
    var_a2 = temp_a2_13 + 1;
    do {
        var_a2[0].value = (s32) ((var_s3 & 0xFFF) | 0x10C000);
        var_a2[0].command = (s32) ((var_s2 & 0xFFF) | 0xF4000000);
        var_a2_2 = var_a2 + 1;
        if (var_t3 > 0) {
            temp_v1 = var_t3 * 4;
            temp_a2_14 = var_a2_2 + 1;
            if (temp_v1 > 0) {
                var_a1 = temp_v1;
            } else {
                var_a1 = 0;
            }
            temp_v1_2 = var_s0 + temp_s4;
            temp_t9 = (temp_v1_2 + 0x3C) * 4;
            if (temp_t9 > 0) {
                var_v0_2 = temp_t9;
            } else {
                var_v0_2 = 0;
            }
            temp_a3 = temp_v1_2 * 4;
            var_a2[1].command = (s32) ((var_v0_2 & 0xFFF) | 0xE4000000 | ((var_a1 & 0xFFF) << 0xC));
            if (temp_a3 > 0) {
                var_v0_3 = temp_a3;
            } else {
                var_v0_3 = 0;
            }
            var_a2_2[0].value = (s32) ((var_v0_3 & 0xFFF) | 0x01000000);
            temp_t9_2 = (s32) (temp_a3 << 9) >> 7;
            temp_a0 = temp_a2_14;
            var_a2_2 = temp_a2_14 + 1;
            if (temp_t9_2 < 0) {
                var_v0_4 = temp_t9_2;
            } else {
                var_v0_4 = 0;
            }
            temp_a0[0].value = 0x200;
            temp_a0[0].command = (s32) (-var_v0_4 & 0xFFFF);
        }
        temp_v1_3 = var_s0 + temp_s4;
        temp_a3_2 = temp_v1_3 * 4;
        temp_t6 = (temp_v1_3 + 0x3C) * 4;
        temp_t9_3 = (s32) (temp_a3_2 << 9) >> 7;
        if ((var_t3 >= -0x87) && (var_f12 < 240.0f) && (temp_v1_4 = var_t3 * 4, temp_v0 = temp_v1_4 + 0x220, (var_f12 > 180.0f))) {
            temp_t7 = (s32) (var_t3 << 0xB) >> 7;
            var_t1 = (var_t3 + 0x87) * 4;
            temp_a2_15 = var_a2_2 + 1;
            if (temp_v0 > 0) {
                var_a1_2 = temp_v0;
            } else {
                var_a1_2 = 0;
            }
            if (temp_t6 > 0) {
                var_v0_5 = temp_t6;
            } else {
                var_v0_5 = 0;
            }
            var_a2_2[0].command = (s32) ((var_v0_5 & 0xFFF) | 0xE4000000 | ((var_a1_2 & 0xFFF) << 0xC));
            if (temp_v1_4 > 0) {
                var_a1_3 = temp_v1_4;
            } else {
                var_a1_3 = 0;
            }
            if (temp_a3_2 > 0) {
                var_v0_6 = temp_a3_2;
            } else {
                var_v0_6 = 0;
            }
            var_a2_2[0].value = (s32) ((var_v0_6 & 0xFFF) | 0x01000000 | ((var_a1_3 & 0xFFF) << 0xC));
            temp_a0_2 = temp_a2_15;
            var_a2_2 = temp_a2_15 + 1;
            if (temp_t7 < 0) {
                var_a1_4 = temp_t7;
            } else {
                var_a1_4 = 0;
            }
            if (temp_t9_3 < 0) {
                var_v0_7 = temp_t9_3;
            } else {
                var_v0_7 = 0;
            }
            temp_a0_2[0].command = (s32) ((-var_v0_7 & 0xFFFF) | (var_a1_4 * -0x10000));
            temp_a0_2[0].value = 0x02000200;
        } else {
            var_t3 -= 0x88;
            var_t1 = (var_t3 + 0x87) * 4;
        }
        temp_a2_16 = var_a2_2 + 1;
        if (temp_t6 > 0) {
            var_v0_8 = temp_t6;
        } else {
            var_v0_8 = 0;
        }
        var_a2_2[0].command = (s32) ((var_v0_8 & 0xFFF) | 0xE44FC000);
        if (var_t1 > 0) {
            var_a1_5 = var_t1;
        } else {
            var_a1_5 = 0;
        }
        if (temp_a3_2 > 0) {
            var_v0_9 = temp_a3_2;
        } else {
            var_v0_9 = 0;
        }
        var_a2_2[0].value = (s32) ((var_v0_9 & 0xFFF) | 0x01000000 | ((var_a1_5 & 0xFFF) << 0xC));
        temp_a2_17 = temp_a2_16 + 1;
        if (0 < 0) {
            var_a1_6 = 0;
        } else {
            var_a1_6 = 0;
        }
        if (temp_t9_3 < 0) {
            var_v0_10 = temp_t9_3;
        } else {
            var_v0_10 = 0;
        }
        var_s0 += 0x3C;
        temp_a2_16[0].value = 0x200;
        var_a2_2[1].command = (s32) ((-var_v0_10 & 0xFFFF) | (var_a1_6 * -0x10000));
        var_s2 += 0x78;
        var_s3 += 0x78;
        temp_a2_16[1].command = 0xE7000000;
        temp_a2_17[0].value = 0;
        var_a2 = temp_a2_17 + 1;
    } while (var_s0 < 0x78);
    temp_a2_18 = var_a2 + 1;
    temp_v1_5 = var_s0 + temp_s4;
    temp_a2_17[1].command = 0x2F300000;
    var_a2[0].value = 0;
    temp_a2_19 = temp_a2_18 + 1;
    var_a2[1].command = 0xF7000000;
    temp_a2_18[0].value = 0;
    temp_a2_20 = temp_a2_19 + 1;
    temp_a2_19[0].value = (s32) ((temp_v1_5 & 0x3FF) * 4);
    temp_a2_18[1].command = (s32) ((((temp_v1_5 + 0x3C) & 0x3FF) * 4) | 0xF64FC000);
    temp_a2_20[0].value = 0x94290;
    temp_a2_21 = temp_a2_20 + 1;
    temp_a2_19[1].command = 0xF5107800;
    temp_a2_22 = temp_a2_21 + 1;
    temp_a2_21[0].value = 0x01094290;
    temp_a2_20[1].command = 0xF5107800;
    temp_a2_23 = temp_a2_22 + 1;
    temp_a2_21[1].command = 0xF2000000;
    temp_a2_22[0].value = 0x013BC01C;
    temp_a2_24 = temp_a2_23 + 1;
    temp_a2_22[1].command = 0xE7000000;
    temp_a2_23[0].value = 0;
    temp_a2_25 = temp_a2_24 + 1;
    temp_a2_24[0].value = 1;
    temp_a2_23[1].command = 0x2F002CC0;
    temp_a2_26 = temp_a2_25 + 1;
    temp_a2_24[1].command = 0xF9000000;
    temp_a2_25[0].value = 0x7F;
    temp_a2_25[1].command = 0xFD1000EF;
    temp_a2_26[0].value = 0x803A4208;
    temp_t6_2 = sp18 * 4;
    var_a2_3 = temp_a2_26 + 1;
    var_t1_2 = 0;
    var_t4 = 0;
    var_t2 = 0x1C;
    var_t3_2 = 0;
    do {
        temp_t0 = var_t3_2 + temp_s4;
        temp_a2_27 = var_a2_3 + 1;
        temp_t8 = (temp_t0 + 0x10) * 4;
        var_a2_3[0].value = (s32) ((((temp_t6_2 + 0x3BC) & 0xFFF) << 0xC) | (var_t2 & 0xFFF));
        var_a2_3[0].command = (s32) (((temp_t6_2 & 0xFFF) << 0xC) | 0xF4000000 | (var_t1_2 & 0xFFF));
        temp_a2_28 = temp_a2_27 + 1;
        if (temp_t8 > 0) {
            var_v0_11 = temp_t8;
        } else {
            var_v0_11 = 0;
        }
        temp_a0_3 = temp_t0 * 4;
        var_a2_3[1].command = (s32) ((var_v0_11 & 0xFFF) | 0xE44FC000);
        if (temp_a0_3 > 0) {
            var_v0_12 = temp_a0_3;
        } else {
            var_v0_12 = 0;
        }
        temp_a2_27[0].value = (s32) ((var_v0_12 & 0xFFF) | 0x01000000 | ((0 & 0xFFF) << 0xC));
        temp_t9_4 = (s32) (temp_a0_3 << 9) >> 7;
        temp_a2_29 = temp_a2_28 + 1;
        if (temp_t9_4 < 0) {
            var_v0_13 = temp_t9_4;
        } else {
            var_v0_13 = 0;
        }
        var_t4 += 1;
        temp_a2_28[0].value = 0x02000200;
        temp_a2_27[1].command = (s32) ((-var_v0_13 & 0xFFFF) | (0 * -0x10000));
        var_t1_2 += 0x20;
        var_t2 += 0x20;
        var_t3_2 += 0x10;
        temp_a2_28[1].command = 0xE7000000;
        temp_a2_29[0].value = 0;
        var_a2_3 = temp_a2_29 + 1;
    } while (var_t4 < 9);
    temp_a2_29[1].command = 0x2F300000;
    var_a2_3[0].value = 0;
    temp_a2_30 = var_a2_3 + 1;
    var_t4_2 = var_t3_2 + temp_s4;
    if (D_801D876C != 0) {
        if ((s32) D_801D7DF8 < 0x20) {
            var_v1 = D_801D7DF8 * 8;
        } else {
            var_v1 = 0xFF;
        }
    } else {
        var_v1 = 0;
    }
    temp_t7_2 = (var_v1 << 8) & 0xF800;
    temp_a2_30[0].value = (s32) ((temp_t7_2 << 0x10) | temp_t7_2);
    var_a2_3[1].command = 0xF7000000;
    temp_a2_31 = temp_a2_30 + 1;
    if (var_t4_2 < 0) {
        var_t4_2 = 0;
    }
    temp_a2_30[1].command = 0xFCFFFFFF;
    temp_a2_31[0].value = 0xFFFE793C;
    temp_v1_6 = temp_a2_31 + 1;
    temp_a2_31[1].command = 0xF64FC3BC;
    temp_v1_6[0].value = (s32) ((var_t4_2 & 0x3FF) * 4);
    temp_a0_4 = temp_v1_6 + 1;
    temp_v1_6[1].command = 0xE9000000;
    temp_a0_4[0].value = 0;
    *arg1 = (temp_a0_4 + 1 - *arg0) * 8;
}
