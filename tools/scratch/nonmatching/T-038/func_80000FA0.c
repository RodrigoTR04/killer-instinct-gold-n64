/* DRAFT. Remaining diff: Huffman decoder types, bit-buffer scheduling and control flow; see REPORT.md. */
s32 memcpy(s32, s32, u32, u32);
extern s32 D_80006630;
extern u8 *D_8000BF80;
extern u8 *D_8000BF84;
extern s32 D_8000BF88;
extern s32 D_8000BF8C;
extern u32 D_8000BF94;
extern u32 D_8000BF98;

s32 func_80000FA0(s32 arg0, s32 arg1, u32 arg2, u32 arg3) {
    s32 sp48;
    s32 sp44;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    s32 temp_t4;
    s32 temp_t4_3;
    s32 temp_t4_4;
    s32 temp_t6;
    s32 temp_t6_3;
    s32 temp_t7;
    s32 temp_v0_5;
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    s8 *temp_t4_2;
    u32 temp_s2;
    u32 temp_s2_2;
    u32 var_s2_3;
    u32 var_s3;
    u32 var_s3_2;
    u32 var_s3_3;
    u32 var_s4;
    u32 var_s4_2;
    u32 var_s4_3;
    u32 var_s7;
    u8 *temp_t5_3;
    u8 *var_a0;
    u8 *var_a0_2;
    u8 temp_t2;
    u8 temp_t2_2;
    u8 temp_t3;
    u8 temp_t4_5;
    u8 temp_t5;
    u8 temp_t5_2;
    u8 temp_t6_2;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 temp_v0_3;
    u8 temp_v0_4;
    u8 var_s2;
    u8 var_s2_2;

    var_s4 = D_8000BF94;
    var_s3 = D_8000BF98;
    var_s1 = D_8000BF8C;
    sp48 = (s32) *(&D_80006630 + (arg2 * 2));
    sp44 = (s32) *(&D_80006630 + (arg3 * 2));
loop_1:
    if (var_s3 < arg2) {
        do {
            temp_t5 = *(D_8000BF80 + D_8000BF88);
            D_8000BF88 += 1;
            temp_t6 = temp_t5 << var_s3;
            var_s3 += 8;
            var_s4 |= temp_t6;
        } while (var_s3 < arg2);
    }
    var_a0 = ((var_s4 & sp48) * 8) + arg0;
    var_s2 = *var_a0;
    if (var_s2 >= 0x11U) {
        do {
            temp_v0 = *(u8 *)((u8 *)(var_a0) + (1));
            temp_s2 = var_s2 - 0x10;
            var_s3 -= temp_v0;
            var_s4 = var_s4 >> temp_v0;
            if (var_s3 < temp_s2) {
                do {
                    temp_t3 = *(D_8000BF80 + D_8000BF88);
                    D_8000BF88 += 1;
                    temp_t4 = temp_t3 << var_s3;
                    var_s3 += 8;
                    var_s4 |= temp_t4;
                } while (var_s3 < temp_s2);
            }
            var_a0 = ((*(&D_80006630 + (temp_s2 * 2)) & var_s4) * 8) + *(s32 *)((u8 *)(var_a0) + (4));
            var_s2 = *var_a0;
        } while (var_s2 >= 0x11U);
    }
    temp_v0_2 = *(u8 *)((u8 *)(var_a0) + (1));
    var_s4 = var_s4 >> temp_v0_2;
    var_s3 -= temp_v0_2;
    if (var_s2 == 0x10) {
        temp_t4_2 = D_8000BF84 + var_s1;
        var_s1 += 1;
        *temp_t4_2 = (s8) *(u16 *)((u8 *)(var_a0) + (4));
        goto loop_1;
    }
    if (var_s2 != 0xF) {
        if (var_s3 < var_s2) {
            do {
                temp_t6_2 = *(D_8000BF80 + D_8000BF88);
                D_8000BF88 += 1;
                temp_t7 = temp_t6_2 << var_s3;
                var_s3 += 8;
                var_s4 |= temp_t7;
            } while (var_s3 < var_s2);
        }
        var_s3_2 = var_s3 - var_s2;
        var_s4_2 = var_s4 >> var_s2;
        var_s7 = (*(&D_80006630 + (var_s2 * 2)) & var_s4) + *(u16 *)((u8 *)(var_a0) + (4));
        if (var_s3_2 < arg3) {
            do {
                temp_t5_2 = *(D_8000BF80 + D_8000BF88);
                D_8000BF88 += 1;
                temp_t6_3 = temp_t5_2 << var_s3_2;
                var_s3_2 += 8;
                var_s4_2 |= temp_t6_3;
            } while (var_s3_2 < arg3);
        }
        var_a0_2 = ((var_s4_2 & sp44) * 8) + arg1;
        var_s2_2 = *var_a0_2;
        if (var_s2_2 >= 0x11U) {
            do {
                temp_v0_3 = *(u8 *)((u8 *)(var_a0_2) + (1));
                temp_s2_2 = var_s2_2 - 0x10;
                var_s3_2 -= temp_v0_3;
                var_s4_2 = var_s4_2 >> temp_v0_3;
                if (var_s3_2 < temp_s2_2) {
                    do {
                        temp_t2 = *(D_8000BF80 + D_8000BF88);
                        D_8000BF88 += 1;
                        temp_t4_3 = temp_t2 << var_s3_2;
                        var_s3_2 += 8;
                        var_s4_2 |= temp_t4_3;
                    } while (var_s3_2 < temp_s2_2);
                }
                var_a0_2 = ((*(&D_80006630 + (temp_s2_2 * 2)) & var_s4_2) * 8) + *(s32 *)((u8 *)(var_a0_2) + (4));
                var_s2_2 = *var_a0_2;
            } while (var_s2_2 >= 0x11U);
        }
        temp_v0_4 = *(u8 *)((u8 *)(var_a0_2) + (1));
        var_s3_3 = var_s3_2 - temp_v0_4;
        var_s4_3 = var_s4_2 >> temp_v0_4;
        if (var_s3_3 < var_s2_2) {
            do {
                temp_t2_2 = *(D_8000BF80 + D_8000BF88);
                D_8000BF88 += 1;
                temp_t4_4 = temp_t2_2 << var_s3_3;
                var_s3_3 += 8;
                var_s4_3 |= temp_t4_4;
            } while (var_s3_3 < var_s2_2);
        }
        var_s3 = var_s3_3 - var_s2_2;
        var_s0 = (var_s1 - *(u16 *)((u8 *)(var_a0_2) + (4))) - (*(&D_80006630 + (var_s2_2 * 2)) & var_s4_3);
        var_s4 = var_s4_3 >> var_s2_2;
        do {
            var_s2_3 = var_s7;
            var_s7 = 0;
            if ((u32) (var_s1 - var_s0) >= var_s2_3) {
                memcpy(D_8000BF84 + var_s1, D_8000BF84 + var_s0, var_s2_3, arg3);
                var_s1 += var_s2_3;
                var_s0 += var_s2_3;
            } else {
                temp_v0_5 = -(var_s2_3 & 3);
                temp_v1 = temp_v0_5 + var_s2_3;
                if (temp_v0_5 != 0) {
                    do {
                        var_s2_3 -= 1;
                        temp_t4_5 = *(var_s0 + D_8000BF84);
                        temp_t5_3 = D_8000BF84 + var_s1;
                        var_s1 += 1;
                        var_s0 += 1;
                        *temp_t5_3 = temp_t4_5;
                    } while (temp_v1 != var_s2_3);
                    if (var_s2_3 != 0) {
                        goto loop_32;
                    }
                } else {
                    do {
loop_32:
                        var_s2_3 -= 4;
                        temp_s0 = var_s0 + 1;
                        *(D_8000BF84 + var_s1) = *(var_s0 + D_8000BF84);
                        temp_s1 = var_s1 + 1;
                        temp_s0_2 = temp_s0 + 1;
                        *(D_8000BF84 + temp_s1) = *(temp_s0 + D_8000BF84);
                        temp_s1_2 = temp_s1 + 1;
                        temp_s0_3 = temp_s0_2 + 1;
                        *(D_8000BF84 + temp_s1_2) = *(temp_s0_2 + D_8000BF84);
                        temp_s1_3 = temp_s1_2 + 1;
                        var_s1 = temp_s1_3 + 1;
                        var_s0 = temp_s0_3 + 1;
                        *(D_8000BF84 + temp_s1_3) = *(temp_s0_3 + D_8000BF84);
                    } while (var_s2_3 != 0);
                }
            }
        } while (0 != 0);
        goto loop_1;
    }
    D_8000BF8C = var_s1;
    D_8000BF94 = var_s4;
    D_8000BF98 = var_s3;
    return 0;
}
