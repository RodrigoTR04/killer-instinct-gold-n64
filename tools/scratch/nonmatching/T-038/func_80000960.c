/* DRAFT. Remaining diff: Huffman builder stack layout, register allocation and control flow; see REPORT.md. */
s32 bzero(s32 (*)[], s32);
extern u8 *D_8000BF90;
extern s32 D_8000BF9C;

s32 func_80000960(s32 *arg0, u32 arg1, u32 arg2, s32 arg3, s32 arg4, s32 *arg5, u32 *arg6) {
    s32 sp5B0[17];
    u32 spC4[0x120];
    u32 sp7C[18];
    s32 sp5F0;
    s32 sp5B4;
    u32 sp5A8;
    s32 sp588;                                      /* compiler-managed */
    s8 sp585;
    u8 sp584;
    s32 sp544;
    s32 sp84;
    s32 sp80;
    s32 sp74;
    s32 *sp5C;
    u32 *sp44;
    u32 sp40;
    s32 *var_a2;
    s32 *temp_v0_2;
    s32 *temp_v0_3;
    s32 *temp_v0_4;
    s32 *temp_v0_5;
    s32 *temp_v0_6;
    s32 *var_a2_3;
    s32 *var_fp;
    s32 *var_fp_2;
    s32 *var_fp_3;
    s32 *var_s5;
    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 *var_v1;
    s32 temp_a0;
    u8 *temp_a0_4;
    s32 temp_a3;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_a3_4;
    s32 temp_ra;
    s32 temp_s6;
    s32 temp_t0;
    s32 temp_t6;
    s32 temp_t6_2;
    s32 temp_t7;
    s32 temp_t7_2;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2_2;
    s32 var_a3_2;
    s32 var_s6;
    s32 var_t2;
    s32 var_t4;
    s32 var_t5;
    s32 var_v0;
    s32 var_v1_2;
    s32 var_v1_3;
    s8 temp_v1_3;
    u32 *temp_v0_7;
    u32 *var_fp_4;
    u32 *var_t3;
    u32 temp_a0_2;
    u32 temp_a0_3;
    u32 temp_t6_3;
    u32 temp_t7_4;
    u32 temp_v0_10;
    u32 temp_v0_8;
    u32 temp_v0_9;
    u32 temp_v1_2;
    u32 var_a3;
    u32 var_a3_3;
    u32 var_a3_4;
    u32 var_a3_5;
    u32 var_ra;
    u32 var_ra_2;
    u32 var_ra_3;
    u32 var_ra_4;
    u32 var_s0;
    u32 var_s4;
    u32 var_t0;
    u32 var_t0_2;
    u8 *temp_a2;
    u8 *temp_t7_3;
    u8 *temp_t9;
    u8 *var_t1;

    bzero((s32 (*)[]) &sp5B0[0], 0x44);
    var_fp = arg0;
    var_a3 = 1;
    temp_v0 = -(arg1 & 3);
    var_ra = arg1;
    if (temp_v0 != 0) {
        do {
            temp_t7 = *var_fp;
            var_ra -= 1;
            var_fp += 4;
            temp_v0_2 = &(&sp5B0[0])[temp_t7];
            *temp_v0_2 += 1;
        } while ((temp_v0 + arg1) != var_ra);
        if (var_ra != 0) {
            goto loop_4;
        }
    } else {
        do {
loop_4:
            temp_t7_2 = *var_fp;
            var_ra -= 4;
            var_fp += 0x10;
            temp_v0_3 = &(&sp5B0[0])[temp_t7_2];
            *temp_v0_3 += 1;
            temp_v0_4 = &(&sp5B0[0])[*(s32 *)((u8 *)(var_fp) + (-0xC))];
            *temp_v0_4 += 1;
            temp_v0_5 = &(&sp5B0[0])[*(s32 *)((u8 *)(var_fp) + (-8))];
            *temp_v0_5 += 1;
            temp_v0_6 = &(&sp5B0[0])[*(s32 *)((u8 *)(var_fp) + (-4))];
            *temp_v0_6 += 1;
        } while (var_ra != 0);
    }
    var_v1 = &sp5B4;
    if (arg1 == sp5B0[0]) {
        *arg5 = 0;
        *arg6 = 0;
        return 0;
    }
    var_s0 = *arg6;
loop_8:
    if (*var_v1 == 0) {
        var_a3 += 1;
        var_v1 += 4;
        if (var_a3 != 0x11) {
            goto loop_8;
        }
    }
    var_s4 = var_a3;
    if (var_s0 < var_a3) {
        var_s0 = var_a3;
    }
    var_ra_2 = 0x10;
    var_v0_2 = &sp5F0;
loop_13:
    if (*var_v0_2 == 0) {
        var_ra_2 -= 1;
        var_v0_2 -= 4;
        if (var_ra_2 != 0) {
            goto loop_13;
        }
    }
    sp5A8 = var_ra_2;
    if (var_ra_2 < var_s0) {
        var_s0 = var_ra_2;
    }
    *arg6 = var_s0;
    var_a0 = 1 << var_a3;
    if (var_a3 < var_ra_2) {
        do {
            temp_t6 = *var_v1;
            var_v1 += 4;
            var_a0 = (var_a0 - temp_t6) * 2;
        } while ((u32) var_v1 < (u32) &(&sp5B0[0])[var_ra_2]);
    }
    temp_v1 = *var_v0_2;
    temp_ra = var_ra_2 - 1;
    var_a3_2 = 0;
    temp_a0 = var_a0 - temp_v1;
    *var_v0_2 = temp_v1 + temp_a0;
    sp80 = 0;
    var_fp_2 = &sp5B4;
    var_a2 = &sp84;
    var_v0_3 = var_v0_2 - 4;
    if (temp_ra != 0) {
        temp_t0 = -(temp_ra & 3);
        if (temp_t0 != 0) {
            do {
                var_v0_3 -= 4;
                var_a2 += 4;
                var_a3_2 += *var_fp_2;
                *(s32 *)((u8 *)(var_a2) + (-4)) = var_a3_2;
                var_fp_2 += 4;
            } while (&(&sp5B0[0])[temp_t0 + temp_ra] != var_v0_3);
            if (var_v0_3 != &sp5B0[0]) {
                goto block_25;
            }
        } else {
block_25:
            do {
                var_v0_3 -= 0x10;
                var_a2 += 0x10;
                temp_a3 = var_a3_2 + *(s32 *)((u8 *)(var_fp_2) + (0));
                *(s32 *)((u8 *)(var_a2) + (-0x10)) = temp_a3;
                temp_t6_2 = *(s32 *)((u8 *)(var_fp_2) + (4));
                var_fp_2 += 0x10;
                temp_a3_2 = temp_a3 + temp_t6_2;
                *(s32 *)((u8 *)(var_a2) + (-0xC)) = temp_a3_2;
                temp_a3_3 = temp_a3_2 + *(s32 *)((u8 *)(var_fp_2) + (-8));
                *(s32 *)((u8 *)(var_a2) + (-8)) = temp_a3_3;
                var_a3_2 = temp_a3_3 + *(s32 *)((u8 *)(var_fp_2) + (-4));
                *(s32 *)((u8 *)(var_a2) + (-4)) = var_a3_2;
            } while (var_v0_3 != &sp5B0[0]);
        }
    }
    var_fp_3 = arg0;
    var_ra_3 = 0;
    do {
        temp_a3_4 = *var_fp_3;
        var_fp_3 += 4;
        if (temp_a3_4 != 0) {
            temp_v0_7 = &(&sp7C[0])[temp_a3_4];
            temp_v1_2 = *temp_v0_7;
            (&spC4[0])[temp_v1_2] = var_ra_3;
            *temp_v0_7 = temp_v1_2 + 1;
        }
        var_ra_3 += 1;
    } while (var_ra_3 < arg1);
    sp74 = temp_a0;
    var_ra_4 = 0;
    sp7C[0] = 0;
    var_fp_4 = &spC4[0];
    var_t4 = -1;
    var_t2 = -(s32) var_s0;
    sp544 = 0;
    var_a2_2 = 0;
    var_t0 = 0;
    if ((s32) sp5A8 >= (s32) var_s4) {
        sp5C = &(&sp5B0[0])[var_s4];
        var_s5 = arg5;
        do {
            var_t5 = var_t4 * 4;
            temp_s6 = *sp5C;
            var_s6 = temp_s6 - 1;
            if (temp_s6 != 0) {
                var_t3 = &(&sp7C[0])[var_t4];
                sp40 = 1 << (var_s4 + 0x1F);
                sp44 = &(&spC4[0])[arg1];
                do {
                    var_v1_2 = var_t2 + var_s0;
                    if (var_v1_2 < (s32) var_s4) {
                        var_t1 = var_t5 + &sp544;
                        do {
                            var_t4 += 1;
                            var_t5 += 4;
                            var_t0_2 = sp5A8 - var_v1_2;
                            var_t1 += 4;
                            var_t3 += 4;
                            var_t2 = var_v1_2;
                            if (var_s0 < var_t0_2) {
                                var_t0_2 = var_s0;
                            }
                            temp_v0_8 = var_s4 - var_t2;
                            temp_a0_2 = 1 << temp_v0_8;
                            var_a3_3 = temp_v0_8;
                            if ((u32) (var_s6 + 1) < temp_a0_2) {
                                var_a3_3 = temp_v0_8 + 1;
                                var_v1_3 = (temp_a0_2 - var_s6) - 1;
                                var_a2_3 = &(&sp5B0[0])[var_s4];
                                if (var_a3_3 < var_t0_2) {
loop_41:
                                    temp_a0_3 = *(u32 *)((u8 *)(var_a2_3) + (4));
                                    temp_v0_9 = var_v1_3 * 2;
                                    var_a2_3 += 4;
                                    if (temp_a0_3 < temp_v0_9) {
                                        var_a3_3 += 1;
                                        var_v1_3 = temp_v0_9 - temp_a0_3;
                                        if (var_a3_3 < var_t0_2) {
                                            goto loop_41;
                                        }
                                    }
                                }
                            }
                            var_t0 = 1 << var_a3_3;
                            temp_a2 = (D_8000BF9C * 8) + D_8000BF90;
                            D_8000BF9C = D_8000BF9C + var_t0 + 1;
                            temp_a0_4 = temp_a2 + 8;
                            *var_s5 = temp_a0_4;
                            *(s32 *)((u8 *)(temp_a2) + (4)) = 0;
                            var_s5 = temp_a2 + 4;
                            var_a2_2 = temp_a0_4;
                            *(s32 *)((u8 *)(var_t1) + (0)) = temp_a0_4;
                            if (var_t4 != 0) {
                                *var_t3 = var_ra_4;
                                sp585 = (s8) var_s0;
                                sp584 = var_a3_3 + 0x10;
                                sp588 = temp_a0_4;
                                temp_t7_3 = *(s32 *)((u8 *)(var_t1) + (-4)) + ((var_ra_4 >> (var_t2 - var_s0)) * 8);
                                *(s32 *)((u8 *)(temp_t7_3) + (0)) = (s32) *(s32 *)((u8 *)(&sp584) + (0));
                                *(s32 *)((u8 *)(temp_t7_3) + (4)) = (s32) *(s32 *)((u8 *)(&sp584) + (4));
                            }
                            var_v1_2 = var_t2 + var_s0;
                        } while (var_v1_2 < (s32) var_s4);
                    }
                    temp_v1_3 = var_s4 - var_t2;
                    sp585 = temp_v1_3;
                    if ((u32) var_fp_4 >= (u32) sp44) {
                        sp584 = 0x63;
                    } else {
                        temp_v0_10 = *var_fp_4;
                        if (temp_v0_10 < arg2) {
                            if (temp_v0_10 < 0x100U) {
                                sp584 = 0x10;
                            } else {
                                sp584 = 0xF;
                            }
                            temp_t7_4 = *var_fp_4;
                            var_fp_4 += 4;
                            sp588 = (s16) temp_t7_4;
                        } else {
                            var_fp_4 += 4;
                            sp584 = *((u8 *)arg4 + (temp_v0_10 - arg2));
                            sp588 = *((u16 *)arg3 + (*(s32 *)((u8 *)(var_fp_4) + (-4)) * 2) + -(arg2 * 2));
                        }
                    }
                    var_a3_4 = var_ra_4 >> var_t2;
                    if (var_a3_4 < var_t0) {
                        do {
                            temp_t9 = var_a2_2 + (var_a3_4 * 8);
                            *(s32 *)((u8 *)(temp_t9) + (0)) = (s32) *(s32 *)((u8 *)(&sp584) + (0));
                            var_a3_4 += 1 << temp_v1_3;
                            *(s32 *)((u8 *)(temp_t9) + (4)) = (s32) *(s32 *)((u8 *)(&sp584) + (4));
                        } while (var_a3_4 < var_t0);
                    }
                    var_a3_5 = sp40;
                    if (var_ra_4 & var_a3_5) {
                        do {
                            temp_t6_3 = var_a3_5 >> 1;
                            var_ra_4 ^= var_a3_5;
                            var_a3_5 = temp_t6_3;
                        } while (var_ra_4 & temp_t6_3);
                    }
                    var_ra_4 ^= var_a3_5;
                    if ((var_ra_4 & ((1 << var_t2) - 1)) != *var_t3) {
                        do {
                            var_t2 -= var_s0;
                            var_t4 -= 1;
                            var_t5 -= 4;
                            var_t3 -= 4;
                        } while ((var_ra_4 & ((1 << var_t2) - 1)) != *(s32 *)((u8 *)(var_t3) + (-4)));
                    }
                    var_s6 -= 1;
                } while (var_s6 != 0);
            }
            var_s4 += 1;
            sp5C += 4;
        } while ((s32) sp5A8 >= (s32) var_s4);
        arg5 = var_s5;
    }
    temp_t8 = sp74 != 0;
    var_v0 = temp_t8;
    if (temp_t8 != 0) {
        var_v0 = sp5A8 != 1;
    }
    return var_v0;
}
