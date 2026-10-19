/* DRAFT. Remaining diff: 358 positional differing words; 1368/1488 bytes */
typedef struct { u32 command, value; } T03315594Command;
extern u8 D_80044A24;
extern f64 D_80048828;
extern u32 D_8004A428[];
extern u8 D_8004AA28;
extern u8 D_80068930;

void func_80015594(T03315594Command **arg0, s32 *arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 var_f0;
    s32 temp_a1;
    s32 temp_f4;
    s32 temp_t0;
    s32 temp_t7;
    s32 temp_t8;
    s32 temp_t9;
    s32 temp_v0;
    s32 var_s0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_t4;
    s32 var_t4_2;
    s32 var_v0;
    s32 var_v0_2;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v1;
    s32 var_v1_2;
    T03315594Command *temp_a2;
    T03315594Command *temp_a2_10;
    T03315594Command *temp_a2_11;
    T03315594Command *temp_a2_12;
    T03315594Command *temp_a2_13;
    T03315594Command *temp_a2_14;
    T03315594Command *temp_a2_15;
    T03315594Command *temp_a2_16;
    T03315594Command *temp_a2_2;
    T03315594Command *temp_a2_3;
    T03315594Command *temp_a2_4;
    T03315594Command *temp_a2_5;
    T03315594Command *temp_a2_6;
    T03315594Command *temp_a2_7;
    T03315594Command *temp_a2_8;
    T03315594Command *temp_a2_9;
    T03315594Command *temp_v1;
    T03315594Command *temp_v1_2;
    T03315594Command *var_a2;
    T03315594Command *var_a2_2;
    T03315594Command *var_a2_3;

    temp_a2 = (T03315594Command *)(&D_80068930 + D_80044A24 * 0x640);
    *arg0 = temp_a2;
    if (arg6 < 180.0f) {
        var_v0 = (s32) ((f32) (s32) ((f64) arg2 / 10.0) + (arg6 * 14.0f));
    } else {
        var_v0 = (s32) ((f64) (s32) ((f64) arg2 / 10.0) - ((D_80048828 - (f64) arg6) * 14.0));
    }
    var_f0 = arg5;
    if (var_f0 < 0.0f) {
        do {
            var_f0 += 360.0f;
        } while (var_f0 < 0.0f);
    }
    if (var_f0 > 180.0f) {
        var_f0 -= 360.0f;
    }
    if (var_v0 < 0) {
        var_s0 = var_v0 * -2;
        var_v0 = 0;
    } else {
        var_s0 = ((var_v0 / 2) * 2) - var_v0;
    }
    temp_a2[0].command = 0xED000000;
    temp_a2_2 = temp_a2 + 1;
    temp_a2_3 = temp_a2_2 + 1;
    temp_a2_4 = temp_a2_3 + 1;
    temp_a2_5 = temp_a2_4 + 1;
    temp_a2_6 = temp_a2_5 + 1;
    temp_a2[0].value = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
    temp_a2_2[0].value = 0x5003C0;
    temp_a2[1].command = 0xED000000;
    temp_a2_3[0].value = 0xFFFE793C;
    temp_a2_2[1].command = 0xFCFFFFFF;
    temp_a2_3[1].command = 0xFF10013F;
    temp_f4 = (s32) (-var_f0 * 8.0f);
    temp_a2_4[0].value = (s32) D_8004A428[D_80044A24];
    temp_a2_5[0].value = 0;
    temp_a2_4[1].command = 0x2F300000;
    temp_a2_5[1].command = 0xF7000000;
    temp_a2_6[0].value = 0;
    var_a2 = temp_a2_6 + 1;
    if (temp_f4 > 0) {
        temp_a2_7 = var_a2 + 1;
        temp_a2_6[1].command = (s32) (((temp_f4 & 0x3FF) * 4) | 0xF64FC000);
        var_a2[0].value = 0;
        var_a2[1].command = 0xE7000000;
        temp_a2_7[0].value = 0;
        var_a2 = temp_a2_7 + 1;
    }
    temp_a2_8 = var_a2 + 1;
    var_a2[0].value = 0xFFFCF87C;
    var_a2[0].command = 0xFCFFFFFF;
    temp_a2_9 = temp_a2_8 + 1;
    var_a2[1].command = 0x2F002CC0;
    temp_a2_8[0].value = 0;
    temp_a2_10 = temp_a2_9 + 1;
    temp_a2_9[0].value = 0x94290;
    temp_a2_8[1].command = 0xF5106400;
    temp_a2_11 = temp_a2_10 + 1;
    temp_a2_10[0].value = 0x01094290;
    temp_a2_9[1].command = 0xF5106400;
    temp_a2_10[1].command = 0xF2000000;
    temp_a2_11[0].value = 0x0131C024;
    temp_t7 = (s32) (var_s0 << 9) >> 7;
    var_a2_2 = temp_a2_11 + 1;
    var_t1 = 0;
    var_t2 = 0x24;
    var_t4 = 0;
    var_t3 = 0;
    do {
        temp_a2_12 = var_a2_2 + 1;
        temp_t0 = var_t3 + temp_f4;
        temp_a2_13 = temp_a2_12 + 1;
        var_a2_2[0].command = 0xFD1000C7;
        var_a2_2[0].value = 0x803A4208;
        temp_t9 = (temp_t0 + 0x14) * 4;
        temp_a2_12[0].value = (s32) ((((var_v0 + 0x31C) & 0xFFF) << 0xC) | (var_t2 & 0xFFF));
        var_a2_2[1].command = (s32) (((var_v0 & 0xFFF) << 0xC) | 0xF4000000 | (var_t1 & 0xFFF));
        temp_a2_14 = temp_a2_13 + 1;
        if (temp_t9 > 0) {
            var_v0_2 = temp_t9;
        } else {
            var_v0_2 = 0;
        }
        temp_a2_12[1].command = (s32) ((var_v0_2 & 0xFFF) | 0xE4500000);
        if (var_s0 > 0) {
            var_v1 = var_s0;
        } else {
            var_v1 = 0;
        }
        temp_a1 = temp_t0 * 4;
        if (temp_a1 > 0) {
            var_v0_3 = temp_a1;
        } else {
            var_v0_3 = 0;
        }
        temp_a2_13[0].value = (s32) ((var_v0_3 & 0xFFF) | 0x01000000 | ((var_v1 & 0xFFF) << 0xC));
        var_a2_2 = temp_a2_14 + 1;
        if (temp_t7 < 0) {
            var_v1_2 = temp_t7;
        } else {
            var_v1_2 = 0;
        }
        temp_t8 = (s32) (temp_a1 << 9) >> 7;
        var_t4 += 1;
        if (temp_t8 < 0) {
            var_v0_4 = temp_t8;
        } else {
            var_v0_4 = 0;
        }
        var_t1 += 0x28;
        var_t2 += 0x28;
        var_t3 += 0x14;
        temp_a2_13[1].command = (s32) ((-var_v0_4 & 0xFFFF) | (var_v1_2 * -0x10000));
        temp_a2_14[0].value = 0x02000200;
    } while (var_t4 < 0xA);
    temp_a2_15 = var_a2_2 + 1;
    temp_a2_14[1].command = 0xE7000000;
    var_a2_2[0].value = 0;
    temp_a2_16 = temp_a2_15 + 1;
    var_a2_2[1].command = 0x2F300000;
    temp_a2_15[0].value = 0;
    var_t4_2 = (var_t3 + temp_f4) - 1;
    temp_a2_15[1].command = 0xF7000000;
    temp_a2_16[0].value = 0;
    var_a2_3 = temp_a2_16 + 1;
    if (var_t4_2 < 0) {
        var_t4_2 = 0;
    }
    temp_v0 = var_s0 / 4;
    temp_v1 = var_a2_3;
    if (temp_v0 >= 2) {
        temp_a2_16[1].command = (s32) ((((temp_v0 - 1) & 0x3FF) << 0xE) | 0xF6000000 | ((var_t4_2 & 0x3FF) * 4));
        var_a2_3 += 1;
        temp_v1[0].value = 0;
    }
    var_a2_3[0].command = 0xF64FC3BC;
    var_a2_3[0].value = (s32) ((var_t4_2 & 0x3FF) * 4);
    temp_v1_2 = var_a2_3 + 1;
    var_a2_3[1].command = 0xE9000000;
    temp_v1_2[0].value = 0;
    *arg1 = (temp_v1_2 + 1 - *arg0) * 8;
}
