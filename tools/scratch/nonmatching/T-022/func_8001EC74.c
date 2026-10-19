/* DRAFT. Remaining diff: 2174 linked instruction words; compiled 8476 bytes, original 8740 bytes. */

s32 func_8002365C(u16, s32);                        /* extern */
s32 func_80023790(s32, s32);                        /* extern */
s32 osVirtualToPhysical();     /* extern */
extern u8 D_8004CED4;
extern u8 D_8004CEDE;
extern s16 D_8004D26E;
extern s32 D_8004EA78;
extern u8 D_8004F2D0;
extern u8 D_8004F390;

void func_8001EC74(u8 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, u8 arg6, u8 arg7) {
    s32 sp250[8], sp270[8], sp290[8], sp2B0[8];
    s32 sp240;
    s32 sp23C;
    s32 sp234;
    s32 sp22C;
    s32 sp224;
    s32 sp218;
    s32 sp214;
    s32 sp210;
    s32 sp20C;
    s32 sp208;
    s32 sp204;
    s32 sp200;
    s32 sp1E4;
    u32 spAC;
    s32 spA0;
    s32 sp9C;
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp6C;
    T022Sprite *temp_t1;
    s16 temp_t2;
    s16 temp_v0;
    s16 temp_v0_5;
    s16 temp_v0_6;
    s32 *temp_s0_19;
    s32 *temp_v0_15;
    s32 *temp_v1;
    s32 *var_a0_2;
    s32 *var_a1;

    s32 *var_a2_2;
    s32 *var_t3;

    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 temp_a0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_lo;
    s32 temp_lo_10;
    s32 temp_lo_11;
    s32 temp_lo_12;
    s32 temp_lo_13;
    s32 temp_lo_14;
    s32 temp_lo_15;
    s32 temp_lo_16;
    s32 temp_lo_2;
    s32 temp_lo_3;
    s32 temp_lo_4;
    s32 temp_lo_5;
    s32 temp_lo_6;
    s32 temp_lo_7;
    s32 temp_lo_8;
    s32 temp_lo_9;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s2;
    s32 temp_s3;
    s32 temp_s3_2;
    s32 temp_s3_3;
    s32 temp_s3_4;
    s32 temp_s7;
    s32 temp_s7_2;
    s32 temp_s7_3;
    s32 temp_t0;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t6_3;
    s32 temp_t6_4;
    s32 temp_t6_5;
    s32 temp_t6_6;
    s32 temp_t6_7;
    s32 temp_t6_8;
    s32 temp_t7;
    s32 temp_t7_10;
    s32 temp_t7_11;
    s32 temp_t7_12;
    s32 temp_t7_13;
    s32 temp_t7_14;
    s32 temp_t7_15;
    s32 temp_t7_16;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t7_4;
    s32 temp_t7_5;
    s32 temp_t7_6;
    s32 temp_t7_7;
    s32 temp_t7_8;
    s32 temp_t7_9;
    s32 temp_t8;
    s32 temp_t8_10;
    s32 temp_t8_11;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t8_4;
    s32 temp_t8_5;
    s32 temp_t8_6;
    s32 temp_t8_7;
    s32 temp_t8_8;
    s32 temp_t8_9;
    s32 temp_t9;
    s32 temp_t9_2;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 temp_t9_5;
    s32 temp_t9_6;
    s32 temp_t9_7;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_7;
    s32 temp_v0_9;
    s32 temp_v1_2;
    s32 var_a0;

    s32 var_a3_2;
    s32 var_a3_3;
    s32 var_a3_4;
    s32 var_s1;

    s32 var_s2;

    s32 var_s3;
    s32 var_s4;
    s32 var_t0;

    s32 var_t3_3;
    s32 var_v0_4;
    s32 var_v1;

    u32 temp_v0_10;
    u32 temp_v0_8;
    u32 var_a2;
    u8 temp_a3;
    u8 temp_a3_2;
    u8 temp_a3_3;
    u8 temp_a3_4;
    u8 temp_a3_5;
    u8 temp_a3_6;
    u8 temp_a3_8;
    u8 var_a3;
    u8 *temp_a0_2;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_a3_7;
    u8 *temp_s0;
    u8 *temp_s0_10;
    u8 *temp_s0_11;
    u8 *temp_s0_12;
    u8 *temp_s0_13;
    u8 *temp_s0_14;
    u8 *temp_s0_15;
    u8 *temp_s0_16;
    u8 *temp_s0_17;
    u8 *temp_s0_18;
    u8 *temp_s0_20;
    u8 *temp_s0_21;
    u8 *temp_s0_22;
    u8 *temp_s0_23;
    u8 *temp_s0_24;
    u8 *temp_s0_25;
    u8 *temp_s0_26;
    u8 *temp_s0_27;
    u8 *temp_s0_28;
    u8 *temp_s0_29;
    u8 *temp_s0_2;
    u8 *temp_s0_30;
    u8 *temp_s0_31;
    u8 *temp_s0_32;
    u8 *temp_s0_33;
    u8 *temp_s0_34;
    u8 *temp_s0_35;
    u8 *temp_s0_36;
    u8 *temp_s0_37;
    u8 *temp_s0_38;
    u8 *temp_s0_3;
    u8 *temp_s0_4;
    u8 *temp_s0_5;
    u8 *temp_s0_6;
    u8 *temp_s0_7;
    u8 *temp_s0_8;
    u8 *temp_s0_9;
    u8 *temp_t1_2;
    u8 *temp_v0_11;
    u8 *temp_v0_12;
    u8 *temp_v0_13;
    u8 *temp_v0_14;
    u8 *var_s0;

    u8 *var_v0;

    var_s1 = arg1;
    if ((arg3 != 0) && (arg4 != 0)) {
        temp_s0 = *arg0;
        spAC = (u32) arg5;
        switch (arg5) {                             /* switch 1 */
        case 1:                                     /* switch 1 */
            temp_s0_2 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xFCF517EA;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0xFF2FFFFF;
            temp_s0_3 = temp_s0_2 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(temp_s0_2) + 4)) = 0x504240;
            (*(s32 *)((u8 *)(temp_s0_2) + 8)) = 0xFA000100;
            (*(s32 *)((u8 *)(temp_s0_3) + 4)) = (s32) ((D_8004D26E & 0xFF) | 0x7F7F7F00);
            var_s0 = temp_s0_3 + 8;
            arg4 = arg4 / 3;
            break;
        case 2:                                     /* switch 1 */
            temp_s0_4 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0x100000;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xBA001402;
            temp_s0_5 = temp_s0_4 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xFCFFA7FF;
            (*(s32 *)((u8 *)(temp_s0_4) + 4)) = 0xFFFCFE38;
            var_s0 = temp_s0_5 + 8;
            (*(s32 *)((u8 *)(temp_s0_4) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(temp_s0_5) + 4)) = 0x0C184240;
            (*(s32 *)((u8 *)(temp_s0_5) + 8)) = 0xFA000100;
            (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((D_8004D26E & 0xFF) | 0x7F7F7F00);
block_15:
            var_s0 = var_s0 + 8;
            break;
        case 7:                                     /* switch 1 */
            var_s0 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xFC30FE61;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0x55FEF379;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(var_s0) + 4)) = 0x504240;
            goto block_15;
        case 5:                                     /* switch 1 */
            temp_s0_6 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0x100000;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xBA001402;
            var_s0 = temp_s0_6 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xFC3133FF;
            (*(s32 *)((u8 *)(temp_s0_6) + 4)) = 0x5FFEDA38;
            (*(s32 *)((u8 *)(temp_s0_6) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(var_s0) + 4)) = 0x0C184240;
            goto block_15;
        case 8:                                     /* switch 1 */
            var_s0 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xFCFFFFFF;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0xFFFCF279;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(var_s0) + 4)) = 0x0F0A4000;
            goto block_15;
        case 3:                                     /* switch 1 */
            temp_s0_7 = temp_s0 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0x100000;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xBA001402;
            temp_s0_8 = temp_s0_7 + 8;
            (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xFCFFA7FF;
            (*(s32 *)((u8 *)(temp_s0_7) + 4)) = 0xFFFCFE38;
            temp_s0_9 = temp_s0_8 + 8;
            (*(s32 *)((u8 *)(temp_s0_7) + 8)) = 0xB900031D;
            (*(s32 *)((u8 *)(temp_s0_8) + 4)) = 0x0C184240;
            temp_s0_10 = temp_s0_9 + 8;
            (*(s32 *)((u8 *)(temp_s0_9) + 4)) = 0x20;
            (*(s32 *)((u8 *)(temp_s0_8) + 8)) = 0xBA000402;
            var_s0 = temp_s0_10 + 8;
            (*(s32 *)((u8 *)(temp_s0_9) + 8)) = 0xF8000000;
            (*(s32 *)((u8 *)(temp_s0_10) + 4)) = 0xFF;
            (*(s32 *)((u8 *)(temp_s0_10) + 8)) = 0xFA000100;
            (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((D_8004D26E & 0xFF) | 0x7F7F7F00);
            goto block_15;
        default:                                    /* switch 1 */
            (*(s32 *)((u8 *)(temp_s0) + 4)) = 0x100000;
            (*(s32 *)((u8 *)(temp_s0) + 0)) = 0xBA001402;
            temp_s0_11 = temp_s0 + 8;
            if ((D_8004EA78 < 2) && ((s32) *(&D_8004F390 + D_8004EA78) > 0)) {
                (*(s32 *)((u8 *)(temp_s0_11) + 4)) = 0xFFFCFE38;
                var_s0 = temp_s0_11 + 8;
                (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xFCFFA7FF;
            } else {
                (*(s32 *)((u8 *)(temp_s0) + 8)) = 0xFCFFFE6A;
                (*(s32 *)((u8 *)(temp_s0_11) + 4)) = 0xF5FCF438;
                var_s0 = temp_s0_11 + 8;
            }
            (*(s32 *)((u8 *)(var_s0) + 0)) = 0xB900031D;
            (*(s32 *)((u8 *)(var_s0) + 4)) = 0x0C184240;
            goto block_15;
        }
        temp_t1 = &D_8004CED0[D_8004EA78];
        temp_t2 = temp_t1->width2;
        if ((spAC == 5) || (spAC == 7)) {

        }
        if ((spAC == 1) || (spAC == 5) || (spAC == 7)) {
            sp218 = (0x1000 / (s32) ((temp_t2 + 7) & 0xFFF8)) & 0xFFFE;
        } else if (spAC == 8) {
            var_s1 -= 1;
            sp218 = (0x1000 / (s32) (((temp_t2 + 3) & 0xFFFC) + (temp_t2 * 2))) & 0xFFFE;
        } else {
            var_s1 -= 1;
            sp218 = (0x1000 / (s32) (((temp_t2 + 7) & 0xFFF8) + (temp_t2 * 2))) & 0xFFFE;
        }
        temp_t9 = sp218 - 2;
        sp218 = temp_t9;
        if (temp_t9 > 0) {
            temp_v0 = temp_t1->height;
            temp_lo = temp_v0 * arg4;
            sp234 = (s32) ((temp_v0 + temp_t9) - 1) / temp_t9;
            temp_s3 = arg2 - temp_lo;
            if (D_8004EA78 < 2) {
                temp_a3 = *(&D_8004F390 + D_8004EA78);
                if ((s32) temp_a3 > 0) {
                    var_v0 = (D_8004EA78 * 0x60) + &D_8004F2D0;
                    var_a1 = &sp290[0];
                    do {
                        var_a1 += 1;
                        temp_t6 = (*(s32 *)((u8 *)(var_v0) + 4)) - temp_lo;
                        var_v0 += 0xC;
                        (*(s32 *)((u8 *)(var_a1) + -4)) = temp_t6;
                    } while ((u32) var_a1 < (u32) &(&sp290[0])[temp_a3]);
                }
            }
            if (arg6 == 1) {
                sp210 = -0x1000;
                if ((spAC == 5) || (spAC == 1) || (spAC == 7)) {
                    sp224 = (s32) temp_t2;
                    sp240 = ((temp_t1->halfWidth * arg3) + var_s1) - (temp_t2 * arg3);
                    sp20C = (temp_t2 - 1) << 5;
                } else {
                    temp_lo_2 = temp_t1->halfWidth * arg3;
                    sp224 = (s32) temp_t2;
                    sp20C = (temp_t2 - 1) << 5;
                    temp_lo_3 = temp_t2 * arg3;
                    sp240 = (temp_lo_2 + var_s1) - temp_lo_3;
                    if (D_8004EA78 < 2) {
                        temp_a3_2 = *(&D_8004F390 + D_8004EA78);
                        if ((s32) temp_a3_2 > 0) {
                            var_v0_2 = (D_8004EA78 * 0x60) + &D_8004F2D0;
                            var_t3 = &sp2B0[0];
                            do {
                                var_t3 += 1;
                                temp_t9_2 = (temp_lo_2 + *var_v0_2) - temp_lo_3;
                                var_v0_2 += 3;
                                (*(s32 *)((u8 *)(var_t3) + -4)) = temp_t9_2;
                            } while ((u32) var_t3 < (u32) &(&sp2B0[0])[temp_a3_2]);
                        }
                    }
                }
            } else {
                temp_lo_4 = temp_t1->halfWidth * arg3;
                sp224 = (s32) temp_t2;
                sp20C = 0;
                sp210 = 0x1000;
                sp240 = var_s1 - temp_lo_4;
                if (D_8004EA78 < 2) {
                    temp_a3_3 = *(&D_8004F390 + D_8004EA78);
                    if ((s32) temp_a3_3 > 0) {
                        var_v0_3 = (D_8004EA78 * 0x60) + &D_8004F2D0;
                        var_t3 = &sp2B0[0];
                        do {
                            var_t3 += 1;
                            temp_t7 = *var_v0_3 - temp_lo_4;
                            var_v0_3 += 3;
                            (*(s32 *)((u8 *)(var_t3) + -4)) = temp_t7;
                        } while ((u32) var_t3 < (u32) &(&sp2B0[0])[temp_a3_3]);
                    }
                }
            }
            sp94 = (s32) arg7;
            if (arg7 == 1) {
                sp204 = (sp218 + 1) << 5;
                temp_lo_5 = temp_t1->halfHeight * arg4;
                sp208 = -0x1000;
                sp23C = (temp_lo + temp_s3) - temp_lo_5;
                if (D_8004EA78 < 2) {
                    temp_a3_4 = *(&D_8004F390 + D_8004EA78);
                    if ((s32) temp_a3_4 > 0) {
                        var_a1 = &sp290[0];
                        do {
                            temp_t7_2 = *var_a1;
                            var_a1 += 1;
                            (*(s32 *)((u8 *)(var_a1) + -4)) = (s32) ((temp_lo + temp_t7_2) - temp_lo_5);
                        } while ((u32) var_a1 < (u32) &(&sp290[0])[temp_a3_4]);
                    }
                }
            } else {
                temp_lo_6 = temp_t1->halfHeight * arg4;
                sp204 = 0;
                sp208 = 0x1000;
                sp23C = temp_lo_6 + temp_s3;
                if (D_8004EA78 < 2) {
                    temp_a3_5 = *(&D_8004F390 + D_8004EA78);
                    if ((s32) temp_a3_5 > 0) {
                        var_a1 = &sp290[0];
                        temp_v1 = &var_a1[temp_a3_5];
                        do {
                            temp_t8 = *var_a1;
                            var_a1 += 1;
                            (*(s32 *)((u8 *)(var_a1) + -4)) = (s32) (temp_lo_6 + temp_t8);
                        } while ((u32) var_a1 < (u32) temp_v1);
                    }
                }
            }
            temp_t4 = sp240 / 4096;
            if (temp_t4 < 0x501) {
                temp_t7_3 = sp23C / 4096;
                if ((temp_t7_3 < 0x3C1) && (((s32) ((sp224 * arg3 * 3) + sp240) / 4096) >= 0)) {
                    temp_lo_7 = sp234 * sp218;
                    temp_s0_12 = var_s0 + 8;
                    temp_s0_13 = temp_s0_12 + 8;
                    if ((temp_t7_3 + temp_lo_7) >= 0) {
                        (*(s32 *)((u8 *)(var_s0) + 4)) = 0x80200;
                        (*(s32 *)((u8 *)(var_s0) + 0)) = 0xF5100000;
                        (*(s32 *)((u8 *)(var_s0) + 8)) = (s32) (((((s32) ((sp224 * 2) + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
                        (*(s32 *)((u8 *)(temp_s0_12) + 4)) = 0x02080200;
                        switch (spAC) {             /* switch 2 */
                        case 1:                     /* switch 2 */
                        case 5:                     /* switch 2 */
                            (*(s32 *)((u8 *)(temp_s0_12) + 8)) = 0xF5900000;
                            (*(s32 *)((u8 *)(temp_s0_13) + 4)) = 0x01080200;
                            temp_s0_14 = temp_s0_13 + 8;
                            (*(s32 *)((u8 *)(temp_s0_14) + 4)) = 0x03080200;
                            (*(s32 *)((u8 *)(temp_s0_13) + 8)) = (s32) (((((s32) (((sp224 + 7) & 0xFFF8) + 7) >> 3) & 0x1FF) << 9) | 0xF5880000);
                            var_s0 = temp_s0_14 + 8;
                            break;
                        case 7:                     /* switch 2 */
                            (*(s32 *)((u8 *)(temp_s0_12) + 8)) = 0xF5700000;
                            (*(s32 *)((u8 *)(temp_s0_13) + 4)) = 0x01080200;
                            temp_s0_15 = temp_s0_13 + 8;
                            (*(s32 *)((u8 *)(temp_s0_15) + 4)) = 0x03080200;
                            (*(s32 *)((u8 *)(temp_s0_13) + 8)) = (s32) (((((s32) (sp224 + 7) >> 3) & 0x1FF) << 9) | 0xF5680000);
                            var_s0 = temp_s0_15 + 8;
                            break;
                        case 8:                     /* switch 2 */
                            temp_s0_16 = temp_s0_13 + 8;
                            (*(s32 *)((u8 *)(temp_s0_13) + 4)) = 1;
                            (*(s32 *)((u8 *)(temp_s0_12) + 8)) = 0xB9000002;
                            (*(s32 *)((u8 *)(temp_s0_16) + 4)) = 0x7F;
                            (*(s32 *)((u8 *)(temp_s0_13) + 8)) = 0xF9000000;
                            temp_s0_17 = temp_s0_16 + 8;
                            var_s0 = temp_s0_17 + 8;
                            (*(s32 *)((u8 *)(temp_s0_16) + 8)) = (s32) ((((s32) ((sp218 + 2) * sp224) / 4) & 0x1FF) | 0xF5900000);
                            (*(s32 *)((u8 *)(temp_s0_17) + 4)) = 0x01080200;
                            break;
                        default:                    /* switch 2 */
                            temp_s0_18 = temp_s0_13 + 8;
                            (*(s32 *)((u8 *)(temp_s0_13) + 4)) = 0x01080200;
                            var_s0 = temp_s0_18 + 8;
                            temp_v0_2 = ((s32) ((sp218 + 2) * sp224) / 4) & 0x1FF;
                            (*(s32 *)((u8 *)(temp_s0_12) + 8)) = (s32) (temp_v0_2 | 0xF5900000);
                            (*(s32 *)((u8 *)(temp_s0_13) + 8)) = (s32) (((((s32) (((sp224 + 7) & 0xFFF8) + 7) >> 3) & 0x1FF) << 9) | 0xF5880000 | temp_v0_2);
                            (*(s32 *)((u8 *)(temp_s0_18) + 4)) = 0x03080200;
                            break;
                        }
                        sp214 = 0;
                        if (sp234 > 0) {
                            sp84 = sp218 * 4;
                            spA0 = sp218 + 1;
                            temp_t0 = D_8004EA78;
                            sp88 = temp_lo_7;
                            sp6C = sp218 * arg4;
                            sp9C = temp_t4;
                            do {
                                temp_t7_4 = sp23C / 4096;
                                var_s2 = sp84;
                                sp22C = 0;
                                sp200 = sp204;
                                if (sp94 == 1) {
                                    var_v0_4 = (sp234 - sp214) - 1;
                                } else {
                                    var_v0_4 = sp214;
                                }
                                temp_t7_5 = var_v0_4 + 1;
                                sp80 = temp_t7_5;
                                if (sp234 == temp_t7_5) {
                                    if (temp_t0 < 2) {
                                        temp_lo_8 = sp218 * (sp234 - 1);
                                        sp90 = temp_t7_4;
                                        var_s3 = var_v0_4 * sp218;
                                        temp_a1 = var_s3 & 0xFFFF;
                                        sp98 = temp_a1;
                                        var_s4 = func_8002365C((*(&D_8004CEDE + (temp_t0 * 0x1C)) - temp_lo_8) & 0xFFFF, temp_a1) & 0xFFFF;
                                        temp_v0_4 = func_80023790(((*(s16 *)((u8 *)&D_8004CEDE + D_8004EA78 * 0x1C)) - temp_lo_8) & 0xFFFF, temp_a1);
                                        var_a0 = 0;
                                        if (sp224 >= temp_v0_4) {
                                            var_a0 = (sp224 - temp_v0_4) & 0xFFFF;
                                        }
                                    } else {
                                        var_s4 = 0;
                                        var_a0 = 0;
                                        var_s3 = var_v0_4 * sp218;
                                    }
                                    if (sp94 == 1) {
                                        temp_v0_5 = *(&D_8004CEDE + (temp_t0 * 0x1C));
                                        temp_v1_2 = sp88 - temp_v0_5;
                                        sp22C = (temp_v1_2 * arg4) + 0xFFF;
                                        sp200 = sp204 - ((temp_v1_2 + 0x1000) << 5);
                                        var_s2 = ((temp_v0_5 - var_s3) - 1) * 4;
                                    } else {
                                        temp_v0_6 = *(&D_8004CEDE + (temp_t0 * 0x1C));
                                        var_s2 = ((temp_v0_6 - var_s3) - 1) * 4;
                                        sp22C = (sp88 - temp_v0_6) * arg4;
                                    }
                                } else if (temp_t0 < 2) {
                                    sp90 = temp_t7_4;
                                    var_s3 = var_v0_4 * sp218;
                                    temp_a1_2 = var_s3 & 0xFFFF;
                                    sp98 = temp_a1_2;
                                    var_s4 = func_8002365C((*(s16 *)((u8 *)&sp218 + 2)), temp_a1_2) & 0xFFFF;
                                    temp_v0_7 = func_80023790((*(s16 *)((u8 *)&sp218 + 2)) & 0xFFFF, temp_a1_2);
                                    if (sp224 >= temp_v0_7) {
                                        var_a0 = (sp224 - temp_v0_7) & 0xFFFF;
                                    } else {
                                        var_a0 = 0;
                                    }
                                } else {
                                    var_s4 = 0;
                                    var_a0 = 0;
                                    var_s3 = var_v0_4 * sp218;
                                }
                                if (var_a0 == 0) {
                                    var_a2 = (sp224 - 1) * 4;
                                } else {
                                    var_a2 = (sp224 - var_a0) * 4;
                                }
                                temp_t8_2 = (var_a2 & 0xFFF) << 0xC;
                                temp_s0_19 = var_s0 + 8;
                                temp_a0 = var_s2 & 0xFFF;
                                var_a3 = 0xF2000000;
                                var_a1 = temp_s0_19;
                                (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) (temp_t8_2 | 0x02000000 | temp_a0);
                                (*(s32 *)((u8 *)(var_s0) + 0)) = 0xF2000000;
                                (*(s32 *)((u8 *)(var_a1) + 4)) = (s32) (temp_t8_2 | 0x03000000 | temp_a0);
                                (*(s32 *)((u8 *)(var_s0) + 8)) = 0xF2000000;
                                temp_s0_20 = temp_s0_19 + 8;
                                if (var_s4 != 0) {
                                    var_s4 = (var_s4 - 1) & 0xFFFF;
                                }
                                if ((arg4 == 0x1000) && (arg3 == 0x1000)) {
                                    var_t3_3 = 0;
                                    if (D_8004EA78 < 2) {
                                        var_a3 = *(&D_8004F390 + D_8004EA78);
                                        if ((s32) var_a3 > 0) {
                                            var_a2 = (u32) &sp250[0];
                                            temp_v0_8 = (var_a3 * 4) + var_a2;
                                            do {
                                                var_a2 += 4;
                                                (*(s32 *)((u8 *)(var_a2) + -4)) = 0;
                                            } while (var_a2 < temp_v0_8);
                                        }
                                    }
                                } else {
                                    var_t3_3 = (s32) (32.0f - ((((f32) sp23C / 4096.0f) - (f32) temp_t7_4) * 32.0f));
                                    if (D_8004EA78 < 2) {
                                        var_a3 = *(&D_8004F390 + D_8004EA78);
                                        var_a0_2 = &sp270[0];
                                        if ((s32) var_a3 > 0) {
                                            var_a1 = &sp290[0];
                                            var_a2 = (u32) &sp250[0];
                                            do {
                                                temp_v0_9 = *var_a1;
                                                var_a0_2 += 1;
                                                var_a1 += 1;
                                                var_a2 += 4;
                                                (*(s32 *)((u8 *)(var_a0_2) + -4)) = 0;
                                                (*(s32 *)((u8 *)(var_a2) + -4)) = (s32) (32.0f - ((((f32) temp_v0_9 / 4096.0f) - (f32) (temp_v0_9 / 4096)) * 32.0f));
                                            } while ((u32) var_a0_2 < (u32) &(&sp270[0])[var_a3]);
                                        }
                                    }
                                }
                                if (sp94 == 1) {
                                    var_t3_3 = -var_t3_3;
                                    if (D_8004EA78 < 2) {
                                        var_a3 = *(&D_8004F390 + D_8004EA78);
                                        if ((s32) var_a3 > 0) {
                                            var_a2 = (u32) &sp250[0];
                                            temp_v0_10 = (var_a3 * 4) + var_a2;
                                            do {
                                                temp_t8_3 = *(s32 *)var_a2;
                                                var_a2 += 4;
                                                (*(s32 *)((u8 *)(var_a2) + -4)) = (s32) -temp_t8_3;
                                            } while (var_a2 < temp_v0_10);
                                        }
                                    }
                                }
                                switch (spAC) {     /* switch 3 */
                                case 1:             /* switch 3 */
                                case 5:             /* switch 3 */
                                case 7:             /* switch 3 */
                                    (*(s32 *)((u8 *)(temp_s0_19) + 8)) = 0xFD900000;
                                    temp_t8_4 = (sp224 + 7) & 0xFFF8;
                                    sp1E4 = var_t3_3;
                                    sp90 = temp_t7_4;
                                    temp_s0_21 = temp_s0_20 + 8;
                                    temp_s1 = ((s32) ((temp_t8_4 * spA0) + 1) >> 1) - 1;
                                    (*(s32 *)((u8 *)(temp_s0_20) + 4)) = osVirtualToPhysical((*(u8 **)((u8 *)&D_8004CED4 + D_8004EA78 * 0x1C)) + (var_s3 * temp_t8_4), var_a1, (s32 *) var_a2, var_a3);
                                    (*(s32 *)((u8 *)(temp_s0_20) + 8)) = 0xF3000000;
                                    temp_s0_22 = temp_s0_21 + 8;
                                    if (temp_s1 < 0x7FF) {
                                        var_v1 = temp_s1;
                                    } else {
                                        var_v1 = 0x7FF;
                                    }
                                    (*(s32 *)((u8 *)(temp_s0_21) + 4)) = (s32) (((var_v1 & 0xFFF) << 0xC) | 0x01000000);
                                    (*(s32 *)((u8 *)(temp_s0_21) + 8)) = 0xE6000000;
                                    (*(s32 *)((u8 *)(temp_s0_22) + 4)) = 0;
                                    var_s0 = temp_s0_22 + 8;
                                    if ((temp_t7_4 < (0xF0 << D_8004AA28)) && (sp9C < (0x140 << D_8004AA28)) && (sp9C >= -0x12B) && (temp_t7_4 >= -0x12B)) {
                                        temp_lo_9 = (s32) (sp210 << 0xA) / arg3;
                                        temp_lo_10 = (s32) (sp208 << 0xA) / arg4;
                                        temp_s7 = temp_lo_10 & 0xFFFF;
                                        temp_s3_2 = temp_s7 & 0xFFFF;
                                        if (sp210 >= 0) {
                                            temp_s0_23 = var_s0 + 8;
                                            temp_a1_3 = temp_t7_4 * 4;
                                            var_t0 = 0;
                                            var_v1 = 0;
                                            temp_t7_6 = (s32) ((((sp224 - var_a0) * arg3) + sp240) * 4) / 4096;
                                            if (temp_t7_6 > 0) {
                                                var_t0 = temp_t7_6;
                                            }
                                            temp_t7_7 = ((s32) ((sp6C + sp23C) - sp22C) / 4096) * 4;
                                            if (temp_t7_7 > 0) {
                                                var_v1 = temp_t7_7;
                                            }
                                            (*(s32 *)((u8 *)(temp_s0_22) + 8)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                            var_t0 = 0;
                                            temp_t8_5 = (s32) (((var_s4 * arg3) + sp240) * 4) / 4096;
                                            if (temp_t8_5 > 0) {
                                                var_t0 = temp_t8_5;
                                            }
                                            var_v1 = 0;
                                            if (temp_a1_3 > 0) {
                                                var_v1 = temp_a1_3;
                                            }
                                            (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x03000000 | ((var_t0 & 0xFFF) << 0xC));
                                            (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                            temp_t9_3 = (s32) (temp_t8_5 * temp_lo_9) >> 7;
                                            temp_s0_24 = temp_s0_23 + 8;
                                            if (temp_t9_3 < 0) {
                                                var_t0 = temp_t9_3;
                                            } else {
                                                var_t0 = 0;
                                            }
                                            var_v1 = 0;
                                            temp_t8_6 = (s32) (temp_a1_3 * temp_s7) >> 7;
                                            if (temp_t8_6 < 0) {
                                                var_v1 = temp_t8_6;
                                            }
                                            (*(s32 *)((u8 *)(temp_s0_23) + 4)) = (s32) ((((sp200 + var_t3_3) - var_v1) & 0xFFFF) | (((sp20C + (var_s4 << 5)) - var_t0) << 0x10));
                                            (*(s32 *)((u8 *)(temp_s0_23) + 8)) = 0xB2000000;
                                            (*(s32 *)((u8 *)(temp_s0_24) + 4)) = (s32) ((temp_lo_9 << 0x10) | temp_s3_2);
                                            var_s0 = temp_s0_24 + 8;
                                        } else {
                                            temp_s0_25 = var_s0 + 8;
                                            temp_a2 = temp_s0_25;
                                            temp_s0_26 = temp_s0_25 + 8;
                                            temp_a1_4 = temp_t7_4 * 4;
                                            var_t0 = 0;
                                            var_v1 = 0;
                                            temp_t7_8 = (s32) ((((sp224 - var_s4) * arg3) + sp240) * 4) / 4096;
                                            if (temp_t7_8 > 0) {
                                                var_t0 = temp_t7_8;
                                            }
                                            temp_t9_4 = ((s32) ((sp6C + sp23C) - sp22C) / 4096) * 4;
                                            if (temp_t9_4 > 0) {
                                                var_v1 = temp_t9_4;
                                            }
                                            (*(s32 *)((u8 *)(temp_s0_22) + 8)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                            var_t0 = 0;
                                            temp_t6_2 = (s32) (((var_a0 * arg3) + sp240) * 4) / 4096;
                                            if (temp_t6_2 > 0) {
                                                var_t0 = temp_t6_2;
                                            }
                                            if (temp_a1_4 > 0) {
                                                var_v1 = temp_a1_4;
                                            } else {
                                                var_v1 = 0;
                                            }
                                            (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x03000000 | ((var_t0 & 0xFFF) << 0xC));
                                            (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                            if (temp_lo_9 >= 0) {
                                                var_v1 = temp_lo_9;
                                            } else {
                                                var_v1 = -temp_lo_9;
                                            }
                                            var_a3_2 = 0;
                                            var_t0 = -temp_lo_10;
                                            if (((s32) (var_v1 * temp_t6_2) / 128) < 0) {
                                                var_v1 = -temp_lo_9;
                                                if (temp_lo_9 >= 0) {
                                                    var_v1 = temp_lo_9;
                                                }
                                                var_a3_2 = (s32) (var_v1 * temp_t6_2) / 128;
                                            }
                                            if (temp_lo_10 >= 0) {
                                                var_t0 = temp_lo_10;
                                            }
                                            temp_v0_11 = temp_s0_26;
                                            var_v1 = 0;
                                            if (((s32) (var_t0 * temp_a1_4) / 128) < 0) {
                                                var_a0 = -temp_lo_10;
                                                if (temp_lo_10 >= 0) {
                                                    var_a0 = temp_lo_10;
                                                }
                                                var_v1 = (s32) (var_a0 * temp_a1_4) / 128;
                                            }
                                            var_s0 = temp_s0_26 + 8;
                                            (*(s32 *)((u8 *)(temp_a2) + 4)) = (s32) ((((sp200 + var_t3_3) - var_v1) & 0xFFFF) | (((sp20C - (var_a0 << 5)) + var_a3_2) << 0x10));
                                            (*(s32 *)((u8 *)(temp_v0_11) + 0)) = 0xB2000000;
                                            (*(s32 *)((u8 *)(temp_v0_11) + 4)) = (s32) ((temp_lo_9 << 0x10) | temp_s3_2);
                                        }
                                    }
                                    var_v1 = sp6C + sp23C;
                                    break;
                                default:            /* switch 3 */
                                case 0:             /* switch 3 */
                                case 2:             /* switch 3 */
                                case 3:             /* switch 3 */
                                case 4:             /* switch 3 */
                                case 6:             /* switch 3 */
                                case 8:             /* switch 3 */
                                    (*(s32 *)((u8 *)(temp_s0_19) + 8)) = 0xFD100000;
                                    sp1E4 = var_t3_3;
                                    sp90 = temp_t7_4;
                                    temp_s0_27 = temp_s0_20 + 8;
                                    temp_s2 = (spA0 * sp224) - 1;
                                    (*(s32 *)((u8 *)(temp_s0_20) + 4)) = osVirtualToPhysical(D_8004CED0[D_8004EA78].unk0 + (var_s3 * sp224 * 2), var_a1, (s32 *) var_a2, var_a3);
                                    (*(s32 *)((u8 *)(temp_s0_20) + 8)) = 0xF3000000;
                                    var_s0 = temp_s0_27 + 8;
                                    if (temp_s2 < 0x7FF) {
                                        var_v1 = temp_s2;
                                    } else {
                                        var_v1 = 0x7FF;
                                    }
                                    (*(s32 *)((u8 *)(temp_s0_27) + 4)) = (s32) ((var_v1 & 0xFFF) << 0xC);
                                    if (spAC != 8) {
                                        (*(s32 *)((u8 *)(temp_s0_27) + 8)) = 0xFD900000;
                                        temp_t8_7 = (sp224 + 7) & 0xFFF8;
                                        sp1E4 = var_t3_3;
                                        sp90 = temp_t7_4;
                                        temp_s0_28 = var_s0 + 8;
                                        temp_s1_2 = ((s32) ((temp_t8_7 * spA0) + 1) >> 1) - 1;
                                        (*(s32 *)((u8 *)(var_s0) + 4)) = osVirtualToPhysical((*(u8 **)((u8 *)&D_8004CED4 + D_8004EA78 * 0x1C)) + (var_s3 * temp_t8_7));
                                        temp_a0_2 = temp_s0_28;
                                        (*(s32 *)((u8 *)(var_s0) + 8)) = 0xF3000000;
                                        var_s0 = temp_s0_28 + 8;
                                        if (temp_s1_2 < 0x7FF) {
                                            var_v1 = temp_s1_2;
                                        } else {
                                            var_v1 = 0x7FF;
                                        }
                                        (*(s32 *)((u8 *)(temp_a0_2) + 4)) = (s32) (((var_v1 & 0xFFF) << 0xC) | 0x01000000);
                                    }
                                    temp_s0_29 = var_s0 + 8;
                                    (*(s32 *)((u8 *)(var_s0) + 0)) = 0xE6000000;
                                    (*(s32 *)((u8 *)(var_s0) + 4)) = 0;
                                    (*(s32 *)((u8 *)(var_s0) + 8)) = 0xE7000000;
                                    (*(s32 *)((u8 *)(temp_s0_29) + 4)) = 0;
                                    var_s0 = temp_s0_29 + 8;
                                    if ((temp_t7_4 < (0xF0 << D_8004AA28)) && (sp9C < (0x140 << D_8004AA28)) && (sp9C >= -0x12B) && (temp_t7_4 >= -0x12B)) {
                                        if ((D_8004EA78 < 2) && (temp_a3_6 = *(&D_8004F390 + D_8004EA78), ((s32) temp_a3_6 > 0))) {
                                            var_s2 = 0;
                                            if ((s32) temp_a3_6 > 0) {
                                                var_s1 = 0;
                                                temp_lo_11 = (s32) (sp210 << 0xA) / arg3;
                                                var_a1 = &sp290[0];
                                                var_t3 = &sp2B0[0];
                                                temp_lo_12 = (s32) (sp208 << 0xA) / arg4;
                                                temp_s7_2 = temp_lo_12 & 0xFFFF;
                                                temp_s3_3 = temp_s7_2 & 0xFFFF;
                                                var_a2_2 = &sp250[0];
                                                do {
                                                    if (sp210 >= 0) {
                                                        temp_s0_30 = var_s0 + 8;
                                                        temp_a3_7 = temp_s0_30;
                                                        var_t0 = 0;
                                                        var_v1 = 0;
                                                        temp_lo_13 = var_s4 * arg3;
                                                        temp_t6_3 = (s32) ((*var_t3 + ((sp224 - var_a0) * arg3)) * 4) / 4096;
                                                        if (temp_t6_3 > 0) {
                                                            var_t0 = temp_t6_3;
                                                        }
                                                        temp_t7_9 = ((s32) ((*var_a1 + sp6C) - sp22C) / 4096) * 4;
                                                        if (temp_t7_9 > 0) {
                                                            var_v1 = temp_t7_9;
                                                        }
                                                        (*(s32 *)((u8 *)(var_s0) + 0)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                                        var_t0 = 0;
                                                        var_v1 = 0;
                                                        temp_t7_10 = (s32) ((*var_t3 + temp_lo_13) * 4) / 4096;
                                                        if (temp_t7_10 > 0) {
                                                            var_t0 = temp_t7_10;
                                                        }
                                                        temp_t6_4 = ((s32) *var_a1 / 4096) * 4;
                                                        if (temp_t6_4 > 0) {
                                                            var_v1 = temp_t6_4;
                                                        }
                                                        (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x02000000 | ((var_t0 & 0xFFF) << 0xC));
                                                        (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                                        var_t0 = 0;
                                                        temp_s0_31 = temp_s0_30 + 8;
                                                        temp_t7_11 = (s32) (((s32) ((*var_t3 + temp_lo_13) * 4) / 4096) * temp_lo_11) >> 7;
                                                        if (temp_t7_11 < 0) {
                                                            var_t0 = temp_t7_11;
                                                        }
                                                        var_v1 = 0;
                                                        temp_t7_12 = (s32) (((s32) *var_a1 / 4096) * 4 * temp_s7_2) >> 7;
                                                        if (temp_t7_12 < 0) {
                                                            var_v1 = temp_t7_12;
                                                        }
                                                        temp_v0_12 = temp_s0_31;
                                                        var_s0 = temp_s0_31 + 8;
                                                        (*(s32 *)((u8 *)(temp_a3_7) + 4)) = (s32) ((((sp200 + *var_a2_2) - var_v1) & 0xFFFF) | ((((sp20C - *(var_s1 + &sp270[0])) + (var_s4 << 5)) - var_t0) << 0x10));
                                                        (*(s32 *)((u8 *)(temp_v0_12) + 0)) = 0xB2000000;
                                                        (*(s32 *)((u8 *)(temp_v0_12) + 4)) = (s32) ((temp_lo_11 << 0x10) | temp_s3_3);
                                                    } else {
                                                        temp_s0_32 = var_s0 + 8;
                                                        temp_t1_2 = temp_s0_32;
                                                        temp_s0_33 = temp_s0_32 + 8;
                                                        temp_lo_14 = var_a0 * arg3;
                                                        temp_t8_8 = (s32) ((*var_t3 + ((sp224 - var_s4) * arg3)) * 4) / 4096;
                                                        if (temp_t8_8 > 0) {
                                                            var_t0 = temp_t8_8;
                                                        } else {
                                                            var_t0 = 0;
                                                        }
                                                        temp_t9_5 = ((s32) ((*var_a1 + sp6C) - sp22C) / 4096) * 4;
                                                        if (temp_t9_5 > 0) {
                                                            var_v1 = temp_t9_5;
                                                        } else {
                                                            var_v1 = 0;
                                                        }
                                                        (*(s32 *)((u8 *)(var_s0) + 0)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                                        temp_t9_6 = (s32) ((*var_t3 + temp_lo_14) * 4) / 4096;
                                                        if (temp_t9_6 > 0) {
                                                            var_t0 = temp_t9_6;
                                                        } else {
                                                            var_t0 = 0;
                                                        }
                                                        temp_t7_13 = ((s32) *var_a1 / 4096) * 4;
                                                        if (temp_t7_13 > 0) {
                                                            var_v1 = temp_t7_13;
                                                        } else {
                                                            var_v1 = 0;
                                                        }
                                                        (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x02000000 | ((var_t0 & 0xFFF) << 0xC));
                                                        (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                                        if (temp_lo_11 >= 0) {
                                                            var_v1 = temp_lo_11;
                                                        } else {
                                                            var_v1 = -temp_lo_11;
                                                        }
                                                        temp_t6_5 = (s32) ((*var_t3 + temp_lo_14) * 4) / 4096;
                                                        if (((s32) (var_v1 * temp_t6_5) / 128) < 0) {
                                                            var_v1 = -temp_lo_11;
                                                            if (temp_lo_11 >= 0) {
                                                                var_v1 = temp_lo_11;
                                                            }
                                                            var_a3_3 = (s32) (var_v1 * temp_t6_5) / 128;
                                                        } else {
                                                            var_a3_3 = 0;
                                                        }
                                                        if (temp_lo_12 >= 0) {
                                                            var_t0 = temp_lo_12;
                                                        } else {
                                                            var_t0 = -temp_lo_12;
                                                        }
                                                        temp_t8_9 = ((s32) *var_a1 / 4096) * 4;
                                                        if (((s32) (var_t0 * temp_t8_9) / 128) < 0) {
                                                            var_a0 = -temp_lo_12;
                                                            if (temp_lo_12 >= 0) {
                                                                var_a0 = temp_lo_12;
                                                            }
                                                            var_v1 = (s32) (var_a0 * temp_t8_9) / 128;
                                                        } else {
                                                            var_v1 = 0;
                                                        }
                                                        temp_v0_13 = temp_s0_33;
                                                        var_s0 = temp_s0_33 + 8;
                                                        (*(s32 *)((u8 *)(temp_t1_2) + 4)) = (s32) ((((sp200 + *var_a2_2) - var_v1) & 0xFFFF) | (((sp20C - (var_a0 << 5)) + var_a3_3) << 0x10));
                                                        (*(s32 *)((u8 *)(temp_v0_13) + 0)) = 0xB2000000;
                                                        (*(s32 *)((u8 *)(temp_v0_13) + 4)) = (s32) ((temp_lo_11 << 0x10) | temp_s3_3);
                                                    }
                                                    var_s2 += 1;
                                                    var_s1 += 4;
                                                    var_a1 += 1;
                                                    var_t3 += 1;
                                                    var_a2_2 += 1;
                                                } while (var_s2 < (s32) *(&D_8004F390 + D_8004EA78));
                                            }
                                        } else {
                                            temp_lo_15 = (s32) (sp210 << 0xA) / arg3;
                                            temp_lo_16 = (s32) (sp208 << 0xA) / arg4;
                                            temp_s7_3 = temp_lo_16 & 0xFFFF;
                                            temp_s3_4 = temp_s7_3 & 0xFFFF;
                                            if (sp210 >= 0) {
                                                temp_s0_34 = var_s0 + 8;
                                                temp_a1_5 = temp_t7_4 * 4;
                                                var_t0 = 0;
                                                var_v1 = 0;
                                                temp_t7_14 = (s32) ((((sp224 - var_a0) * arg3) + sp240) * 4) / 4096;
                                                if (temp_t7_14 > 0) {
                                                    var_t0 = temp_t7_14;
                                                }
                                                temp_t7_15 = ((s32) ((sp6C + sp23C) - sp22C) / 4096) * 4;
                                                if (temp_t7_15 > 0) {
                                                    var_v1 = temp_t7_15;
                                                }
                                                (*(s32 *)((u8 *)(temp_s0_29) + 8)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                                var_t0 = 0;
                                                temp_t8_10 = (s32) (((var_s4 * arg3) + sp240) * 4) / 4096;
                                                if (temp_t8_10 > 0) {
                                                    var_t0 = temp_t8_10;
                                                }
                                                var_v1 = 0;
                                                if (temp_a1_5 > 0) {
                                                    var_v1 = temp_a1_5;
                                                }
                                                (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x02000000 | ((var_t0 & 0xFFF) << 0xC));
                                                (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                                temp_t6_6 = (s32) (temp_t8_10 * temp_lo_15) >> 7;
                                                temp_s0_35 = temp_s0_34 + 8;
                                                if (temp_t6_6 < 0) {
                                                    var_t0 = temp_t6_6;
                                                } else {
                                                    var_t0 = 0;
                                                }
                                                var_v1 = 0;
                                                temp_t8_11 = (s32) (temp_a1_5 * temp_s7_3) >> 7;
                                                if (temp_t8_11 < 0) {
                                                    var_v1 = temp_t8_11;
                                                }
                                                (*(s32 *)((u8 *)(temp_s0_34) + 4)) = (s32) ((((sp200 + var_t3_3) - var_v1) & 0xFFFF) | (((sp20C + (var_s4 << 5)) - var_t0) << 0x10));
                                                (*(s32 *)((u8 *)(temp_s0_34) + 8)) = 0xB2000000;
                                                (*(s32 *)((u8 *)(temp_s0_35) + 4)) = (s32) ((temp_lo_15 << 0x10) | temp_s3_4);
                                                var_s0 = temp_s0_35 + 8;
                                            } else {
                                                temp_s0_36 = var_s0 + 8;
                                                temp_a2_2 = temp_s0_36;
                                                temp_s0_37 = temp_s0_36 + 8;
                                                temp_a1_6 = temp_t7_4 * 4;
                                                var_t0 = 0;
                                                var_v1 = 0;
                                                temp_t7_16 = (s32) ((((sp224 - var_s4) * arg3) + sp240) * 4) / 4096;
                                                if (temp_t7_16 > 0) {
                                                    var_t0 = temp_t7_16;
                                                }
                                                temp_t6_7 = ((s32) ((sp6C + sp23C) - sp22C) / 4096) * 4;
                                                if (temp_t6_7 > 0) {
                                                    var_v1 = temp_t6_7;
                                                }
                                                (*(s32 *)((u8 *)(temp_s0_29) + 8)) = (s32) ((var_v1 & 0xFFF) | 0xE4000000 | ((var_t0 & 0xFFF) << 0xC));
                                                var_t0 = 0;
                                                temp_t9_7 = (s32) (((var_a0 * arg3) + sp240) * 4) / 4096;
                                                if (temp_t9_7 > 0) {
                                                    var_t0 = temp_t9_7;
                                                }
                                                if (temp_a1_6 > 0) {
                                                    var_v1 = temp_a1_6;
                                                } else {
                                                    var_v1 = 0;
                                                }
                                                (*(s32 *)((u8 *)(var_s0) + 4)) = (s32) ((var_v1 & 0xFFF) | 0x02000000 | ((var_t0 & 0xFFF) << 0xC));
                                                (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB3000000;
                                                if (temp_lo_15 >= 0) {
                                                    var_v1 = temp_lo_15;
                                                } else {
                                                    var_v1 = -temp_lo_15;
                                                }
                                                var_a3_4 = 0;
                                                var_t0 = -temp_lo_16;
                                                if (((s32) (var_v1 * temp_t9_7) / 128) < 0) {
                                                    var_v1 = -temp_lo_15;
                                                    if (temp_lo_15 >= 0) {
                                                        var_v1 = temp_lo_15;
                                                    }
                                                    var_a3_4 = (s32) (var_v1 * temp_t9_7) / 128;
                                                }
                                                if (temp_lo_16 >= 0) {
                                                    var_t0 = temp_lo_16;
                                                }
                                                temp_v0_14 = temp_s0_37;
                                                var_v1 = 0;
                                                if (((s32) (var_t0 * temp_a1_6) / 128) < 0) {
                                                    var_a0 = -temp_lo_16;
                                                    if (temp_lo_16 >= 0) {
                                                        var_a0 = temp_lo_16;
                                                    }
                                                    var_v1 = (s32) (var_a0 * temp_a1_6) / 128;
                                                }
                                                var_s0 = temp_s0_37 + 8;
                                                (*(s32 *)((u8 *)(temp_a2_2) + 4)) = (s32) ((((sp200 + var_t3_3) - var_v1) & 0xFFFF) | (((sp20C - (var_a0 << 5)) + var_a3_4) << 0x10));
                                                (*(s32 *)((u8 *)(temp_v0_14) + 0)) = 0xB2000000;
                                                (*(s32 *)((u8 *)(temp_v0_14) + 4)) = (s32) ((temp_lo_15 << 0x10) | temp_s3_4);
                                            }
                                        }
                                    }
                                    var_v1 = sp6C + sp23C;
                                    break;
                                }
                                (*(s32 *)((u8 *)(var_s0) + 0)) = 0xE7000000;
                                (*(s32 *)((u8 *)(var_s0) + 4)) = 0;
                                var_s0 = var_s0 + 8;
                                sp23C = var_v1;
                                if (D_8004EA78 < 2) {
                                    temp_a3_8 = *(&D_8004F390 + D_8004EA78);
                                    var_a1 = &sp290[0];
                                    if ((s32) temp_a3_8 > 0) {
                                        temp_v0_15 = &var_a1[temp_a3_8];
                                        do {
                                            temp_t6_8 = *var_a1;
                                            var_a1 += 1;
                                            (*(s32 *)((u8 *)(var_a1) + -4)) = (s32) (temp_t6_8 + sp6C);
                                        } while ((u32) var_a1 < (u32) temp_v0_15);
                                    }
                                }
                                if (sp234 == sp80) {
                                    sp23C -= sp22C;
                                }
                                temp_v0_3 = sp214 + 1;
                                sp214 = temp_v0_3;
                            } while (temp_v0_3 != sp234);
                        }
                        temp_s0_38 = var_s0 + 8;
                        (*(s32 *)((u8 *)(var_s0) + 4)) = 0xC00;
                        (*(s32 *)((u8 *)(var_s0) + 0)) = 0xBA000903;
                        (*(s32 *)((u8 *)(var_s0) + 8)) = 0xB9000002;
                        (*(s32 *)((u8 *)(temp_s0_38) + 4)) = 0;
                        var_s0 = temp_s0_38 + 8;
                        if (spAC == 3) {
                            (*(s32 *)((u8 *)(var_s0) + 4)) = 0x30;
                            (*(s32 *)((u8 *)(temp_s0_38) + 8)) = 0xBA000402;
                            var_s0 += 8;
                        }
                        if ((spAC == 0) || (spAC == 5) || (spAC == 3) || (spAC == 2)) {
                            (*(s32 *)((u8 *)(var_s0) + 0)) = 0xBA001402;
                            (*(s32 *)((u8 *)(var_s0) + 4)) = 0;
                            var_s0 += 8;
                        }
                        *arg0 = var_s0;
                    }
                }
            }
        }
    }
}
