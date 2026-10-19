/* T-022 DRAFT: Build failed before byte comparison: cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACCC'; previous declaration at line 487 in file 'src/main/main.c'; cfe: Error: src/main/main.c, line 1083: redeclaration of 'D_8004ACD0'; previous declaration at line 488 in file 'src/main/main.c' */




extern u8 D_8004AC88;
extern u8 *D_8004ACD8;
extern u8 D_80044A24;
extern u8 D_80044EC4;
extern u8 D_80044EC8;
extern u8 D_80044ECB;
extern f64 D_80048928;
extern u8 D_8004A403;
extern u8 D_8004A40D;
extern u8 D_8004A428;
extern u8 D_8004ACC5;
extern u8 D_8004ACC6;
extern u8 D_8004ACC7;
extern u8 D_8004ACC8;
extern u8 D_8004ACC9;
extern u8 D_8004ACCA;
extern u8 D_8004ACCC;
extern u8 D_8004ACD0;
extern u8 D_8004ACD3;
extern u8 D_8004ACD4;
extern f32 D_8004AD0C;
extern f32 D_8004AD10;
extern u8 D_80068930;
extern u8 D_801D7DF8;
extern u16 D_801D876C;
extern u8 D_801D87FE;

void func_80019880(u8 **arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg5, f32 arg6) {
    s16 coords[2], spCCpair[2];
    s32 sp10C;
    s32 sp108;
    s32 sp100;
    s32 spF8;
    s16 spE6;
    s16 spE4;
    s16 spE2;
    s16 spE0;
    s16 spDE;
    s16 spDC;
    s16 spDA;
    s16 spD8;
    s16 spD4pair[2];
    s16 spD2;
    s16 spD0;
    s16 spC8pair[2];
    s16 spC0pair[2];
    s16 spBE;
    s16 spBC;
    s16 spBA;
    s16 spB8;
    s32 sp1C;
    f32 temp_f14;
    f32 var_f0;
    f32 var_f2;
    s16 *var_a0;
    s16 *var_a0_2;
    s16 *var_a0_3;
    s16 *var_a3;
    s16 *var_a3_2;
    s16 *var_v0;
    s16 *var_v0_2;
    s16 *var_v0_3;
    s16 *var_v1;
    s16 temp_a1;
    s16 temp_a1_2;
    s16 temp_a2;
    s16 temp_a2_2;
    s16 temp_a2_3;
    s16 temp_a3;
    s32 temp_a0;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t2;
    s32 temp_t8;
    s32 var_s0;
    s32 var_t2;
    s32 var_v1_2;
    s32 var_v1_4;
    u8 *var_a1;
    u8 *var_v1_3;
    u8 temp_t8_2;
    u8 temp_t9;
    u8 *temp_t0;
    u8 *temp_t0_10;
    u8 *temp_t0_11;
    u8 *temp_t0_12;
    u8 *temp_t0_13;
    u8 *temp_t0_14;
    u8 *temp_t0_15;
    u8 *temp_t0_16;
    u8 *temp_t0_17;
    u8 *temp_t0_18;
    u8 *temp_t0_19;
    u8 *temp_t0_20;
    u8 *temp_t0_21;
    u8 *temp_t0_22;
    u8 *temp_t0_23;
    u8 *temp_t0_24;
    u8 *temp_t0_25;
    u8 *temp_t0_26;
    u8 *temp_t0_27;
    u8 *temp_t0_28;
    u8 *temp_t0_29;
    u8 *temp_t0_2;
    u8 *temp_t0_30;
    u8 *temp_t0_31;
    u8 *temp_t0_32;
    u8 *temp_t0_33;
    u8 *temp_t0_34;
    u8 *temp_t0_35;
    u8 *temp_t0_36;
    u8 *temp_t0_37;
    u8 *temp_t0_38;
    u8 *temp_t0_39;
    u8 *temp_t0_3;
    u8 *temp_t0_40;
    u8 *temp_t0_41;
    u8 *temp_t0_42;
    u8 *temp_t0_43;
    u8 *temp_t0_44;
    u8 *temp_t0_45;
    u8 *temp_t0_46;
    u8 *temp_t0_47;
    u8 *temp_t0_48;
    u8 *temp_t0_49;
    u8 *temp_t0_4;
    u8 *temp_t0_50;
    u8 *temp_t0_51;
    u8 *temp_t0_52;
    u8 *temp_t0_53;
    u8 *temp_t0_5;
    u8 *temp_t0_6;
    u8 *temp_t0_7;
    u8 *temp_t0_8;
    u8 *temp_t0_9;
    u8 *var_t0;
    u8 *var_t0_2;
    u8 *var_t0_3;
    u8 *var_t0_4;

    spE0 = (s16) (*(u8 *)((u8 *)(&D_8004ACCC) + 0));
    spD8 = (s16) (*(u8 *)((u8 *)(&D_8004ACD0) + 0));
    spE6 = (s16) D_8004ACD3;
    spE2 = (s16) (*(u8 *)((u8 *)(&D_8004ACCC) + 1));
    spE4 = (s16) (*(u8 *)((u8 *)(&D_8004ACCC) + 2));
    spDA = (s16) (*(u8 *)((u8 *)(&D_8004ACD0) + 1));
    spDC = (s16) (*(u8 *)((u8 *)(&D_8004ACD0) + 2));
    spDE = (s16) D_8004ACD4;
    if (D_801D876C != 0) {
        var_v1 = &spB8;
        if (D_8004AA28 == 0) {
            var_a0 = &spD8;
            if ((s32) D_801D7DF8 < 0x20) {
                spB8 = D_801D7DF8 * 8;
            } else {
                spB8 = 0xFF;
            }
            spBC = 0;
            spBA = 0;
            var_v0 = &spE0;
            spBE = spB8;
            do {
                temp_a1 = *var_v0;
                temp_a3 = *var_v1;
                temp_a2 = *var_a0;
                temp_lo = (temp_a3 - temp_a1) * spB8;
                temp_t8 = temp_a3 - temp_a2;
                var_a0 += 1;
                var_v0 += 1;
                var_v1 += 1;
                (*(s16 *)((u8 *)(var_v0) + -2)) = (s16) (temp_a1 + (temp_lo / 255));
                (*(s16 *)((u8 *)(var_a0) + -2)) = (s16) (temp_a2 + ((s32) (temp_t8 * spB8) / 255));
            } while (var_a0 != &spDE);
        }
    }
    var_f2 = D_8004AD10;
    var_v1_2 = 0;
    var_v0_2 = &spE0;
    var_a3 = &spD0;
    var_f0 = (f32) ((f64) D_8004AD0C - ((f64) arg6 * D_80048928));
    if (var_f0 > 255.0f) {
        do {
            var_f0 -= 256.0f;
        } while (var_f0 > 255.0f);
    }
    if (var_f0 < 0.0f) {
        do {
            var_f0 += 256.0f;
        } while (var_f0 < 0.0f);
    }
    if (var_f2 > 255.0f) {
        do {
            var_f2 -= 256.0f;
        } while (var_f2 > 255.0f);
    }
    if (var_f2 < 0.0f) {
        do {
            var_f2 += 256.0f;
        } while (var_f2 < 0.0f);
    }
    if (arg5 > 270.0f) {
        temp_f14 = 360.0f - arg5;
        spF8 = (s32) (temp_f14 * -7.0f);
        sp100 = (s32) ((f32) 0x26AC + ((f32) 0x17B * temp_f14));
        sp10C = (s32) ((f32) -0x43 + ((temp_f14 * 6.0f) / 10.0f));
        var_t2 = (s32) (-(temp_f14 * 72.0f) / 10.0f);
    } else {
        spF8 = (s32) (arg5 * 7.0f);
        sp100 = (s32) ((f32) 0x26AC - ((f32) 0x1C6 * arg5));
        sp10C = (s32) ((f32) -0x43 - ((arg5 * 6.0f) / 10.0f));
        var_t2 = (s32) ((arg5 * 72.0f) / 10.0f);
    }
    temp_t2 = var_t2 + 2;
    do {
        temp_a1_2 = *var_v0_2;
        *var_a3 = temp_a1_2;
        if (temp_t2 < 0x93) {
            temp_lo_2 = (s32) ((*(&spD8 + var_v1_2) - temp_a1_2) * (0x10000 >> D_8004AA28)) / (s32) (0x93 - temp_t2);
            *(&spC8pair[0] + var_v1_2) = (temp_lo_2 >> 0x10) & 0xFFFF;
            *(&spC0pair[0] + var_v1_2) = temp_lo_2 & 0xFFFF;
        }
        var_a3 += 1;
        var_v1_2 += 2;
        var_v0_2 += 1;
    } while ((u32) var_a3 < (u32) &spD8);
    temp_t0 = (D_80044A24 * 0x640) + &D_80068930;
    sp108 = 0;
    *arg0 = temp_t0;
    (*(s32 *)((u8 *)(temp_t0) + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)(temp_t0) + 4)) = 0;
    temp_t0_2 = temp_t0 + 8;
    if ((D_8004AA28 == 0) && (D_8004A403 != 0) && (D_801D87FE != 0) && (D_8004A40D == 4)) {
        (*(s32 *)((u8 *)(temp_t0_2) + 4)) = 0x4403C0;
        var_t0 = temp_t0_2 + 8;
        (*(s32 *)((u8 *)(temp_t0) + 8)) = 0xED0C0000;
    } else {
        (*(s32 *)((u8 *)(temp_t0) + 8)) = 0xED000000;
        var_t0 = temp_t0_2 + 8;
        (*(s32 *)((u8 *)(temp_t0_2) + 4)) = (s32) ((((s32) ((f32) (0x140 << D_8004AA28) * 4.0f) & 0xFFF) << 0xC) | ((s32) ((f32) (0xF0 << D_8004AA28) * 4.0f) & 0xFFF));
    }
    (*(s32 *)((u8 *)(var_t0) + 0)) = 0x3B000000;
    temp_t0_3 = var_t0 + 8;
    temp_t0_4 = temp_t0_3 + 8;
    (*(s32 *)((u8 *)(var_t0) + 4)) = (s32) ((D_8004ACC5 << 0x18) | (D_8004ACC6 << 0x10) | (D_8004ACC7 << 8));
    (*(s32 *)((u8 *)(var_t0) + 8)) = 0x3A000000;
    (*(s32 *)((u8 *)(temp_t0_3) + 4)) = (s32) ((D_8004ACC8 << 0x18) | (D_8004ACC9 << 0x10) | (D_8004ACCA << 8));
    temp_t0_5 = temp_t0_4 + 8;
    (*(s32 *)((u8 *)(temp_t0_3) + 8)) = (s32) ((((0x140 << D_8004AA28) - 1) & 0xFFF) | 0xFF100000);
    (*(s32 *)((u8 *)(temp_t0_4) + 4)) = (s32) *(&D_8004A428 + (D_80044A24 * 4));
    var_s0 = 0;
    if ((D_8004AC88 == 7) || (D_8004AC88 == 2)) {
        var_t0_2 = temp_t0_5 + 8;
        (*(s32 *)((u8 *)(temp_t0_4) + 8)) = 0xFC15FE2B;
        (*(s32 *)((u8 *)(temp_t0_5) + 4)) = 0x33FFF9FC;
        (*(s32 *)((u8 *)(temp_t0_5) + 8)) = 0x2F082C80;
        (*(s32 *)((u8 *)(var_t0_2) + 4)) = 0x0C084000;
    } else {
        var_t0_2 = temp_t0_5 + 8;
        (*(s32 *)((u8 *)(temp_t0_5) + 4)) = 0x35FDF978;
        (*(s32 *)((u8 *)(temp_t0_4) + 8)) = 0xFC40FE0B;
        (*(s32 *)((u8 *)(temp_t0_5) + 8)) = 0x2F182C80;
        (*(s32 *)((u8 *)(var_t0_2) + 4)) = 0x0F0A4000;
    }
    temp_t0_6 = var_t0_2 + 8;
    (*(s32 *)((u8 *)(var_t0_2) + 8)) = 0xFD900000;
    temp_t0_7 = temp_t0_6 + 8;
    (*(u8 **)((u8 *)(temp_t0_6) + 4)) = (u8 *) D_8004ACD8;
    temp_t0_8 = temp_t0_7 + 8;
    (*(s32 *)((u8 *)(temp_t0_6) + 8)) = 0xF5900000;
    (*(s32 *)((u8 *)(temp_t0_7) + 4)) = 0x06018060;
    (*(s32 *)((u8 *)(temp_t0_8) + 4)) = 0x067FF100;
    temp_t0_9 = temp_t0_8 + 8;
    (*(s32 *)((u8 *)(temp_t0_7) + 8)) = 0xF3000000;
    (*(s32 *)((u8 *)(temp_t0_8) + 8)) = 0xF5881000;
    (*(s32 *)((u8 *)(temp_t0_9) + 4)) = 0x07018060;
    temp_t0_10 = temp_t0_9 + 8;
    (*(s32 *)((u8 *)(temp_t0_9) + 8)) = (s32) (((((s32) var_f0 + 2) & 0xFFF) << 0xC) | 0xF2000000 | (((s32) var_f2 + 2) & 0xFFF));
    (*(s32 *)((u8 *)(temp_t0_10) + 4)) = 0x070FE0FE;
    var_t0_3 = temp_t0_10 + 8;
    if (temp_t2 < 0x93) {
        var_s0 = 0x93 - temp_t2;
        temp_t1 = var_s0 * 4;
        (*(s32 *)((u8 *)(temp_t0_10) + 8)) = (s32) (((temp_t1 << D_8004AA28) & 0x1FFF) | 0x0E870000);
        temp_t0_11 = var_t0_3 + 8;
        (*(s32 *)((u8 *)(var_t0_3) + 4)) = (s32) (((temp_t1 << D_8004AA28) & 0x1FFF) << 0x10);
        (*(s32 *)((u8 *)(var_t0_3) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_11) + 4)) = 0;
        temp_t0_12 = temp_t0_11 + 8;
        (*(s32 *)((u8 *)(temp_t0_11) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_12) + 4)) = 0;
        temp_t0_13 = temp_t0_12 + 8;
        (*(s32 *)((u8 *)(temp_t0_12) + 8)) = (s32) (((0x140 << D_8004AA28) - 1) << 0x10);
        (*(s32 *)((u8 *)(temp_t0_13) + 4)) = 0;
        temp_t0_14 = temp_t0_13 + 8;
        (*(s32 *)((u8 *)(temp_t0_13) + 8)) = (s32) ((spD2 & 0xFFFF) | (spD0 << 0x10));
        temp_t0_15 = temp_t0_14 + 8;
        (*(s32 *)((u8 *)(temp_t0_14) + 4)) = (s32) ((spD4pair[1] & 0xFFFF) | (spD4pair[0] << 0x10));
        (*(s32 *)((u8 *)(temp_t0_14) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_15) + 4)) = 0;
        temp_t0_16 = temp_t0_15 + 8;
        (*(s32 *)((u8 *)(temp_t0_15) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_16) + 4)) = 0;
        temp_t0_17 = temp_t0_16 + 8;
        (*(s32 *)((u8 *)(temp_t0_16) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_17) + 4)) = 0;
        temp_t0_18 = temp_t0_17 + 8;
        (*(s32 *)((u8 *)(temp_t0_17) + 8)) = (s32) ((spC8pair[1] & 0xFFFF) | (spC8pair[0] << 0x10));
        temp_t0_19 = temp_t0_18 + 8;
        (*(s32 *)((u8 *)(temp_t0_18) + 4)) = (s32) ((spCCpair[1] & 0xFFFF) | (spCCpair[0] << 0x10));
        (*(s32 *)((u8 *)(temp_t0_18) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_19) + 4)) = 0;
        temp_t0_20 = temp_t0_19 + 8;
        (*(s32 *)((u8 *)(temp_t0_19) + 8)) = (s32) ((spC0pair[1] & 0xFFFF) | (spC0pair[0] << 0x10));
        temp_t0_21 = temp_t0_20 + 8;
        (*(s32 *)((u8 *)(temp_t0_20) + 4)) = (s32) ((coords[1] & 0xFFFF) | (coords[0] << 0x10));
        (*(s32 *)((u8 *)(temp_t0_20) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_21) + 4)) = 0;
        temp_t0_22 = temp_t0_21 + 8;
        (*(s32 *)((u8 *)(temp_t0_21) + 8)) = (s32) ((spF8 & 0xFFFF) | 0xFF600000);
        temp_t0_23 = temp_t0_22 + 8;
        (*(s32 *)((u8 *)(temp_t0_22) + 4)) = (s32) (sp100 << 0x10);
        (*(s32 *)((u8 *)(temp_t0_23) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_t0_22) + 8)) = (s32) ((1 >> D_8004AA28) << 0x10);
        temp_t0_24 = temp_t0_23 + 8;
        (*(s32 *)((u8 *)(temp_t0_23) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_24) + 4)) = 0;
        temp_t0_25 = temp_t0_24 + 8;
        (*(s32 *)((u8 *)(temp_t0_24) + 8)) = (s32) (D_8004AA28 << 0x1F);
        (*(s32 *)((u8 *)(temp_t0_25) + 4)) = 0;
        temp_t0_26 = temp_t0_25 + 8;
        (*(s32 *)((u8 *)(temp_t0_25) + 8)) = (s32) ((0 << 0x10) | ((1 >> D_8004AA28) & 0xFFFF));
        temp_t0_27 = temp_t0_26 + 8;
        (*(s32 *)((u8 *)(temp_t0_26) + 4)) = (s32) ((sp10C >> D_8004AA28) << 0x10);
        (*(s32 *)((u8 *)(temp_t0_26) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_27) + 4)) = 0;
        temp_t0_28 = temp_t0_27 + 8;
        (*(s32 *)((u8 *)(temp_t0_27) + 8)) = (s32) ((sp108 << 0x10) | ((D_8004AA28 << 0xF) & 0xFFFF));
        (*(s32 *)((u8 *)(temp_t0_28) + 4)) = 0;
        temp_t0_29 = temp_t0_28 + 8;
        temp_t0_30 = temp_t0_29 + 8;
        (*(s32 *)((u8 *)(temp_t0_28) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_29) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_t0_29) + 8)) = 0xE7000000;
        (*(s32 *)((u8 *)(temp_t0_30) + 4)) = 0;
        var_t0_3 = temp_t0_30 + 8;
    }
    if ((D_8004AC88 == 0xB) || (D_8004AC88 == 2)) {
        temp_t1_2 = var_s0 * 4;
        sp1C = sp108 << 0x10;
        if (D_8004AC88 == 2) {
            var_v1_3 = &D_80044EC8;
            var_a1 = &D_80044EC4;
            var_v0_3 = &spE0;
            var_a0_2 = &spD8;
            do {
                temp_t8_2 = *var_a1;
                temp_t9 = *var_v1_3;
                var_v1_3 += 1;
                var_v0_3 += 1;
                var_a0_2 += 1;
                var_a1 += 1;
                (*(s16 *)((u8 *)(var_v0_3) + -2)) = (s16) temp_t8_2;
                (*(s16 *)((u8 *)(var_a0_2) + -2)) = (s16) temp_t9;
            } while (var_v1_3 != &D_80044ECB);
            temp_t0_31 = var_t0_3 + 8;
            (*(s32 *)((u8 *)(var_t0_3) + 0)) = 0xFC40FE0B;
            (*(s32 *)((u8 *)(var_t0_3) + 4)) = 0x35FDF978;
            (*(s32 *)((u8 *)(var_t0_3) + 8)) = 0x2F182C80;
            (*(s32 *)((u8 *)(temp_t0_31) + 4)) = 0x0F0A4000;
            var_t0_3 = temp_t0_31 + 8;
        }
        var_v1_4 = 0;
        var_a0_3 = &spD8;
        var_a3_2 = &spD0;
        do {
            temp_a2_2 = (*(s16 *)((u8 *)(var_a0_3) + 0));
            (*(s16 *)((u8 *)(var_a3_2) + 0)) = temp_a2_2;
            if (temp_t1_2 > 0) {
                temp_lo_3 = (s32) ((*(&spE0 + var_v1_4) - temp_a2_2) * (0x10000 >> D_8004AA28)) / var_s0;
                *(&spC8pair[0] + var_v1_4) = (temp_lo_3 >> 0x10) & 0xFFFF;
                *(&spC0pair[0] + var_v1_4) = temp_lo_3 & 0xFFFF;
            }
            temp_a2_3 = (*(s16 *)((u8 *)(var_a0_3) + 2));
            var_a0_3 += 2;
            (*(s16 *)((u8 *)(var_a3_2) + 2)) = temp_a2_3;
            if (temp_t1_2 > 0) {
                temp_lo_4 = (s32) (((*(s16 *)((u8 *)((&spE0 + var_v1_4)) + 2)) - temp_a2_3) * (0x10000 >> D_8004AA28)) / var_s0;
                (*(s16 *)((u8 *)((&spC8pair[0] + var_v1_4)) + 2)) = (s16) ((temp_lo_4 >> 0x10) & 0xFFFF);
                (*(s16 *)((u8 *)((&spC0pair[0] + var_v1_4)) + 2)) = (s16) (temp_lo_4 & 0xFFFF);
            }
            var_a3_2 += 2;
            var_v1_4 += 4;
        } while (var_a3_2 != &spD8);
        (*(s32 *)((u8 *)(var_t0_3) + 0)) = (s32) ((((0x3C0 << D_8004AA28) - 1) & 0x1FFF) | 0x0E870000);
        temp_t0_32 = var_t0_3 + 8;
        (*(s32 *)((u8 *)(var_t0_3) + 4)) = (s32) (((((0x3C0 << D_8004AA28) - 1) & 0x1FFF) << 0x10) | ((temp_t1_2 << D_8004AA28) & 0x1FFF));
        (*(s32 *)((u8 *)(var_t0_3) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_32) + 4)) = 0;
        temp_t0_33 = temp_t0_32 + 8;
        (*(s32 *)((u8 *)(temp_t0_32) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_33) + 4)) = 0;
        temp_t0_34 = temp_t0_33 + 8;
        (*(s32 *)((u8 *)(temp_t0_33) + 8)) = (s32) (((0x140 << D_8004AA28) - 1) << 0x10);
        (*(s32 *)((u8 *)(temp_t0_34) + 4)) = 0;
        temp_t0_35 = temp_t0_34 + 8;
        (*(s32 *)((u8 *)(temp_t0_34) + 8)) = (s32) ((spD2 & 0xFFFF) | (spD0 << 0x10));
        temp_t0_36 = temp_t0_35 + 8;
        (*(s32 *)((u8 *)(temp_t0_35) + 4)) = (s32) ((spD4pair[1] & 0xFFFF) | (spD4pair[0] << 0x10));
        (*(s32 *)((u8 *)(temp_t0_35) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_36) + 4)) = 0;
        temp_t0_37 = temp_t0_36 + 8;
        (*(s32 *)((u8 *)(temp_t0_36) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_37) + 4)) = 0;
        temp_t0_38 = temp_t0_37 + 8;
        (*(s32 *)((u8 *)(temp_t0_37) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_38) + 4)) = 0;
        temp_t0_39 = temp_t0_38 + 8;
        (*(s32 *)((u8 *)(temp_t0_38) + 8)) = (s32) ((spC8pair[1] & 0xFFFF) | (spC8pair[0] << 0x10));
        temp_t0_40 = temp_t0_39 + 8;
        (*(s32 *)((u8 *)(temp_t0_39) + 4)) = (s32) ((spCCpair[1] & 0xFFFF) | (spCCpair[0] << 0x10));
        (*(s32 *)((u8 *)(temp_t0_39) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_40) + 4)) = 0;
        temp_t0_41 = temp_t0_40 + 8;
        (*(s32 *)((u8 *)(temp_t0_40) + 8)) = (s32) ((spC0pair[1] & 0xFFFF) | (spC0pair[0] << 0x10));
        temp_t0_42 = temp_t0_41 + 8;
        (*(s32 *)((u8 *)(temp_t0_41) + 4)) = (s32) ((coords[1] & 0xFFFF) | (coords[0] << 0x10));
        temp_t0_43 = temp_t0_42 + 8;
        (*(s32 *)((u8 *)(temp_t0_41) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_42) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_t0_43) + 4)) = 0x640000;
        (*(s32 *)((u8 *)(temp_t0_42) + 8)) = 0xFF600150;
        temp_t0_44 = temp_t0_43 + 8;
        (*(s32 *)((u8 *)(temp_t0_43) + 8)) = (s32) ((1 >> D_8004AA28) << 0x10);
        (*(s32 *)((u8 *)(temp_t0_44) + 4)) = 0;
        temp_t0_45 = temp_t0_44 + 8;
        (*(s32 *)((u8 *)(temp_t0_44) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_45) + 4)) = 0;
        temp_t0_46 = temp_t0_45 + 8;
        (*(s32 *)((u8 *)(temp_t0_45) + 8)) = (s32) (D_8004AA28 << 0x1F);
        (*(s32 *)((u8 *)(temp_t0_46) + 4)) = 0;
        temp_t0_47 = temp_t0_46 + 8;
        (*(s32 *)((u8 *)(temp_t0_46) + 8)) = (s32) ((0 << 0x10) | ((1 >> D_8004AA28) & 0xFFFF));
        temp_t0_48 = temp_t0_47 + 8;
        (*(s32 *)((u8 *)(temp_t0_47) + 4)) = (s32) ((0x47 >> D_8004AA28) << 0x10);
        (*(s32 *)((u8 *)(temp_t0_47) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_48) + 4)) = 0;
        temp_t0_49 = temp_t0_48 + 8;
        (*(s32 *)((u8 *)(temp_t0_48) + 8)) = (s32) (sp1C | ((D_8004AA28 << 0xF) & 0xFFFF));
        (*(s32 *)((u8 *)(temp_t0_49) + 4)) = 0;
        temp_t0_50 = temp_t0_49 + 8;
        temp_t0_51 = temp_t0_50 + 8;
        (*(s32 *)((u8 *)(temp_t0_49) + 8)) = 0;
        (*(s32 *)((u8 *)(temp_t0_50) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_t0_50) + 8)) = 0xE7000000;
        (*(s32 *)((u8 *)(temp_t0_51) + 4)) = 0;
        var_t0_4 = temp_t0_51 + 8;
    } else {
        if ((D_801D876C != 0) && (D_801D7DF8 != 0) && (D_8004AA28 == 0)) {
            spD0 = ((s32) (spB8 * (spB8 - D_8004ACC5)) / 255) + D_8004ACC5;
            spD2 = ((s32) (spB8 * (spBA - D_8004ACC6)) / 255) + D_8004ACC6;
            spD4pair[0] = ((s32) (spB8 * (spBC - D_8004ACC7)) / 255) + D_8004ACC7;
        } else {
            spD0 = (s16) D_8004ACC5;
            spD2 = (s16) D_8004ACC6;
            spD4pair[0] = (s16) D_8004ACC7;
        }
        temp_t0_52 = var_t0_3 + 8;
        (*(s32 *)((u8 *)(var_t0_3) + 0)) = 0x2F302C80;
        (*(s32 *)((u8 *)(var_t0_3) + 4)) = 0;
        (*(s32 *)((u8 *)(var_t0_3) + 8)) = 0xF7000000;
        temp_t0_53 = temp_t0_52 + 8;
        temp_a0 = ((spD4pair[0] >> 2) & 0x3E) | ((spD0 << 8) & 0xF800) | ((spD2 * 8) & 0x7C0);
        (*(s32 *)((u8 *)(temp_t0_52) + 4)) = (s32) (temp_a0 | (temp_a0 << 0x10));
        if ((D_8004AA28 == 0) && (D_8004A403 != 0) && (D_801D87FE != 0) && (D_8004A40D == 4)) {
            (*(s32 *)((u8 *)(temp_t0_52) + 8)) = 0xF643C3BC;
            (*(s32 *)((u8 *)(temp_t0_53) + 4)) = (s32) (((var_s0 & 0x3FF) * 4) | 0xC0000);
            var_t0_4 = temp_t0_53 + 8;
        } else {
            (*(s32 *)((u8 *)(temp_t0_52) + 8)) = (s32) (((((0x140 << D_8004AA28) - 1) & 0x3FF) << 0xE) | 0xF6000000 | (((0xEF << D_8004AA28) & 0x3FF) * 4));
            var_t0_4 = temp_t0_53 + 8;
            (*(s32 *)((u8 *)(temp_t0_53) + 4)) = (s32) (((var_s0 << D_8004AA28) & 0x3FF) * 4);
        }
    }
    (*(s32 *)((u8 *)(var_t0_4) + 0)) = 0xE9000000;
    (*(s32 *)((u8 *)(var_t0_4) + 4)) = 0;
    *arg1 = ((s32) ((var_t0_4 + 8) - *arg0) >> 3) * 8;
}
