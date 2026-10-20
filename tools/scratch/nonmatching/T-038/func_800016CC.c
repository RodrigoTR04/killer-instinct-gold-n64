/* DRAFT. Remaining diff: Dynamic-Huffman stack layout, table types and control flow; see REPORT.md. */
s32 func_80000960(s32 *, s32, s32, s32 *, s32 *, u8 **, u32 *);
s32 func_80000FA0(u8 *, u8 *, u32, u32);
extern u8 D_80006560;
extern s32 D_80006573;
extern s32 D_80006574;
extern s32 D_800065B4;
extern s32 D_800065D4;
extern s32 D_80006610;
extern s32 D_80006630;
extern u32 D_80006654;
extern u32 D_80006658;
extern u8 *D_8000BF80;
extern s32 D_8000BF88;
extern u32 D_8000BF94;
extern u32 D_8000BF98;

s32 func_800016CC(void) {
    u8 *sp550;
    u8 *sp54C;
    u32 sp40[0x140];
    u32 sp548;
    u32 sp544;
    s32 sp53C;
    s32 sp538;
    u32 sp534;
    u32 sp530;
    s32 *var_v0;
    s32 *var_v0_2;
    s32 *var_v0_3;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a2;
    s32 temp_t6_2;
    s32 temp_t6_5;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t9_3;
    s32 temp_t9_4;
    s32 var_a0_2;
    s32 var_a0_3;
    s32 var_a0_4;
    u16 temp_a0_2;
    u16 var_a2;
    u32 temp_a3;
    u32 var_a0;
    u32 var_a1_3;
    u32 var_t0;
    u32 var_t0_2;
    u32 var_t0_3;
    u32 var_t0_4;
    u32 var_t0_5;
    u32 var_t1;
    u32 var_t1_2;
    u32 var_t1_3;
    u32 var_t1_4;
    u32 var_t1_5;
    u8 *var_a1;
    u8 *var_a1_2;
    u8 temp_a0;
    u8 temp_t6;
    u8 temp_t6_3;
    u8 temp_t6_4;
    u8 temp_t7;
    u8 temp_t7_5;
    u8 temp_t7_6;
    u8 temp_t8_3;
    u8 temp_t9;
    u8 temp_t9_2;
    u8 *temp_t7_4;

    var_t0 = D_8000BF98;
    var_t1 = D_8000BF94;
    if (var_t0 < 5U) {
        do {
            temp_t7 = *(D_8000BF80 + D_8000BF88);
            D_8000BF88 += 1;
            temp_t8 = temp_t7 << var_t0;
            var_t0 += 8;
            var_t1 |= temp_t8;
        } while (var_t0 < 5U);
    }
    var_t0_2 = var_t0 - 5;
    sp53C = (var_t1 & 0x1F) + 0x101;
    var_t1_2 = var_t1 >> 5;
    if (var_t0_2 < 5U) {
        do {
            temp_t6 = *(D_8000BF80 + D_8000BF88);
            D_8000BF88 += 1;
            temp_t7_2 = temp_t6 << var_t0_2;
            var_t0_2 += 8;
            var_t1_2 |= temp_t7_2;
        } while (var_t0_2 < 5U);
    }
    var_t0_3 = var_t0_2 - 5;
    sp538 = (var_t1_2 & 0x1F) + 1;
    var_t1_3 = var_t1_2 >> 5;
    if (var_t0_3 < 4U) {
        do {
            temp_t9 = *(D_8000BF80 + D_8000BF88);
            D_8000BF88 += 1;
            temp_t6_2 = temp_t9 << var_t0_3;
            var_t0_3 += 8;
            var_t1_3 |= temp_t6_2;
        } while (var_t0_3 < 4U);
    }
    temp_a2 = (var_t1_3 & 0xF) + 4;
    var_t1_4 = var_t1_3 >> 4;
    var_t0_4 = var_t0_3 - 4;
    var_a0 = 0;
    if (temp_a2 != 0) {
        var_a1 = &D_80006560;
        do {
            var_a0 += 1;
            if (var_t0_4 < 3U) {
                do {
                    temp_t6_3 = *(D_8000BF80 + D_8000BF88);
                    D_8000BF88 += 1;
                    temp_t7_3 = temp_t6_3 << var_t0_4;
                    var_t0_4 += 8;
                    var_t1_4 |= temp_t7_3;
                } while (var_t0_4 < 3U);
            }
            temp_t6_4 = *var_a1;
            var_a1 += 1;
            (&sp40[0])[temp_t6_4] = var_t1_4 & 7;
            var_t1_4 = var_t1_4 >> 3;
            var_t0_4 -= 3;
        } while (var_a0 != temp_a2);
    }
    if (var_a0 < 0x13U) {
        var_a1_2 = &(&D_80006560)[var_a0];
        do {
            temp_t9_2 = *var_a1_2;
            var_a1_2 += 1;
            (&sp40[0])[temp_t9_2] = 0;
        } while ((u32) var_a1_2 < (u32) &D_80006573);
    }
    sp548 = 7;
    sp534 = var_t0_4;
    sp530 = var_t1_4;
    func_80000960(&sp40[0], 0x13, 0x13, 0, 0, &sp550, &sp548);
    temp_a3 = sp53C + sp538;
    var_t0_5 = sp534;
    var_t1_5 = sp530;
    var_a2 = 0;
    var_a1_3 = 0;
    if (temp_a3 != 0) {
        do {
            if (var_t0_5 < sp548) {
                do {
                    temp_t8_2 = *(D_8000BF80 + D_8000BF88) << var_t0_5;
                    var_t0_5 += 8;
                    var_t1_5 |= temp_t8_2;
                    D_8000BF88 += 1;
                } while (var_t0_5 < sp548);
            }
            temp_t7_4 = ((var_t1_5 & *(&D_80006630 + (sp548 * 2))) * 8) + sp550;
            sp54C = temp_t7_4;
            temp_a0 = *(u8 *)((u8 *)(temp_t7_4) + (1));
            var_t1_5 = var_t1_5 >> temp_a0;
            var_t0_5 -= temp_a0;
            temp_a0_2 = *(u16 *)((u8 *)(temp_t7_4) + (4));
            if (temp_a0_2 < 0x10U) {
                var_a2 = temp_a0_2;
                (&sp40[0])[var_a1_3] = (s32) temp_a0_2;
                var_a1_3 += 1;
            } else if (temp_a0_2 == 0x10) {
                if (var_t0_5 < 2U) {
                    do {
                        temp_t7_5 = *(D_8000BF80 + D_8000BF88);
                        D_8000BF88 += 1;
                        temp_t9_3 = temp_t7_5 << var_t0_5;
                        var_t0_5 += 8;
                        var_t1_5 |= temp_t9_3;
                    } while (var_t0_5 < 2U);
                }
                temp_a0_3 = (var_t1_5 & 3) + 3;
                var_t1_5 = var_t1_5 >> 2;
                var_t0_5 -= 2;
                var_a0_2 = temp_a0_3 - 1;
                if (temp_a0_3 != 0) {
                    var_v0 = &(&sp40[0])[var_a1_3];
                    do {
                        *var_v0 = (s32) var_a2;
                        var_a1_3 += 1;
                        var_v0 += 4;
                        var_a0_2 -= 1;
                    } while (var_a0_2 != 0);
                }
            } else {
                var_a2 = 0;
                if (temp_a0_2 == 0x11) {
                    if (var_t0_5 < 3U) {
                        do {
                            temp_t8_3 = *(D_8000BF80 + D_8000BF88);
                            D_8000BF88 += 1;
                            temp_t6_5 = temp_t8_3 << var_t0_5;
                            var_t0_5 += 8;
                            var_t1_5 |= temp_t6_5;
                        } while (var_t0_5 < 3U);
                    }
                    temp_a0_4 = (var_t1_5 & 7) + 3;
                    var_t1_5 = var_t1_5 >> 3;
                    var_t0_5 -= 3;
                    var_a0_3 = temp_a0_4 - 1;
                    if (temp_a0_4 != 0) {
                        var_v0_2 = &(&sp40[0])[var_a1_3];
                        do {
                            *var_v0_2 = 0;
                            var_a1_3 += 1;
                            var_v0_2 += 4;
                            var_a0_3 -= 1;
                        } while (var_a0_3 != 0);
                    }
                } else {
                    if (var_t0_5 < 7U) {
                        do {
                            temp_t7_6 = *(D_8000BF80 + D_8000BF88);
                            D_8000BF88 += 1;
                            temp_t9_4 = temp_t7_6 << var_t0_5;
                            var_t0_5 += 8;
                            var_t1_5 |= temp_t9_4;
                        } while (var_t0_5 < 7U);
                    }
                    temp_a0_5 = (var_t1_5 & 0x7F) + 0xB;
                    var_t1_5 = var_t1_5 >> 7;
                    var_t0_5 -= 7;
                    var_a0_4 = temp_a0_5 - 1;
                    if (temp_a0_5 != 0) {
                        var_v0_3 = &(&sp40[0])[var_a1_3];
                        do {
                            *var_v0_3 = 0;
                            var_a1_3 += 1;
                            var_v0_3 += 4;
                            var_a0_4 -= 1;
                        } while (var_a0_4 != 0);
                    }
                }
            }
        } while (var_a1_3 < temp_a3);
    }
    D_8000BF94 = var_t1_5;
    D_8000BF98 = var_t0_5;
    sp548 = D_80006654;
    func_80000960(&sp40[0], sp53C, 0x101, &D_80006574, &D_800065B4, &sp550, &sp548);
    sp544 = D_80006658;
    func_80000960(&(&sp40[0])[sp53C], sp538, 0, &D_800065D4, &D_80006610, &sp54C, &sp544);
    func_80000FA0(sp550, sp54C, sp548, sp544);
    return 0;
}
