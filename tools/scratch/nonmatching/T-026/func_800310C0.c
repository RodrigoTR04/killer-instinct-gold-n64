/* DRAFT. Remaining diff: 685 differing instruction words; emitted 2744 / original 2424 bytes (positional comparison). */
/* Private decoder registers are exposed as context fields. The original
 * contains shared internal entry labels and register-return helpers; the C ABI
 * and pointer/register allocation are unresolved. */
typedef struct { s32 a1, a2, a3, at, t0, t1, lo, gp; } T026DecoderLive;
extern s32 func_80032600();                                /* extern */
extern u16 func_80032670();                /* extern */

extern s32 D_8004EA78;
extern u8 *D_8004F2C8;

void func_800310C0(u8 *arg0, T026DecoderLive *live) {
    u8 *var_s1;
    s16 temp_a0;
    s16 temp_s0;
    s16 temp_s3;
    s16 var_v0_2;
    s16 var_v0_4;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_at;
    s32 temp_at_2;
    s32 temp_fp_3;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_s2_4;
    s32 temp_s2_6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 var_a0;
    s32 var_a1_11;
    s32 var_a1_12;
    s32 var_a1_3;
    s32 var_a1_5;
    s32 var_a1_6;
    s32 var_a1_8;
    s32 var_a1_9;
    s32 var_s2;
    s32 var_s4;
    s32 var_s5;
    s64 *var_a1_10;
    s64 *var_at;
    s8 *var_a1_2;
    u16 temp_s5;
    u16 temp_s5_2;
    u16 var_v0;
    u16 var_v0_3;
    u16 var_v0_5;
    u32 temp_fp;
    u32 temp_fp_2;
    u32 temp_s3_2;
    u32 temp_s3_3;
    u32 temp_s4;
    u32 temp_s6;
    u32 var_t1;
    u8 *temp_a1;
    u8 *temp_fp_4;
    u8 *temp_fp_5;
    u8 *temp_fp_6;
    u8 *temp_fp_7;
    u8 *temp_s2_3;
    u8 *temp_s2_5;
    u8 *temp_t0;
    u8 *var_a1;
    u8 *var_a1_4;
    u8 *var_a1_7;
    u8 *var_gp;
    u8 *var_s2_10;
    u8 *var_s2_2;
    u8 *var_s2_3;
    u8 *var_s2_4;
    u8 *var_s2_5;
    u8 *var_s2_6;
    u8 *var_s2_7;
    u8 *var_s2_8;
    u8 *var_s2_9;

    /* Flowgraph is not reducible, falling back to gotos-only mode. */
    var_gp = live->gp;
    var_a0 = D_8004EA78;
    var_s1 = (u8 *)D_8004CED0;
    if ((u32)(var_a0) == (u32)(0)) {
        goto block_2;
    }
loop_1:
    var_a0 -= 1;
    var_s1 += 0x1C;
    if ((u32)(var_a0) != (u32)(0)) {
        goto loop_1;
    }
block_2:
    (*(s16 *)((u32)(var_s1) + (8))) = (s16) ((*(u8 *)((u32)(arg0) + (0))) + ((*(u8 *)((u32)(arg0) + (1))) << 8));
    (*(s16 *)((u32)(var_s1) + (10))) = (s16) ((*(u8 *)((u32)(arg0) + (2))) + ((*(u8 *)((u32)(arg0) + (3))) << 8));
    (*(s16 *)((u32)(var_s1) + (14))) = (s16) ((*(u8 *)((u32)(arg0) + (6))) + ((*(u8 *)((u32)(arg0) + (7))) << 8));
    temp_a0 = (*(u8 *)((u32)(arg0) + (4))) + ((*(u8 *)((u32)(arg0) + (5))) << 8);
    temp_s3 = (temp_a0 + 2 + 3) & 0xFFFC;
    (*(s16 *)((u32)(var_s1) + (12))) = temp_a0;
    (*(s16 *)((u32)(var_s1) + (16))) = temp_s3;
    temp_s3_2 = temp_s3 * 2;
    temp_fp = temp_s3_2 >> 1;
    temp_s6 = (temp_s3 - temp_a0) * 2;
    var_s2 = (*(s32 *)((u32)(var_s1) + (0)));
    var_v0 = func_80032670(arg0, (*(u8 * *)((u32)(var_s1) + (4))), ((temp_fp + 7) & 0xFFF8) - temp_fp);
    temp_s4 = live->lo;
    var_at = (temp_s4 >> 1) + live->a1;
    var_s4 = var_s2 + temp_s4;
    if ((u32)(0) == (u32)(0)) {
        goto loop_17;
    }
    var_t1 = 0U >> 0x10;
    var_s5 = 0 & 0xFFFF;
    temp_fp_2 = temp_s3_2 >> 1;
    if ((u32)(var_t1) == (u32)(0)) {
        goto block_9;
    }
loop_4:
    var_gp = D_8004F2C8;
    if ((u32)(var_gp) == (u32)(0)) {
        goto block_6;
    }
    (*(u16 *)((u32)(var_gp) + (0))) = 0xFFU;
    (*(u16 *)((u32)(var_gp) + (2))) = 0;
    var_gp += 4;
    D_8004F2C8 = var_gp;
block_6:
    var_s2 += temp_s3_2;
loop_7:
    temp_a1 = live->a1 + 8;
    (*(u64 *)((u32)(temp_a1) + (-8))) = 0;
    if ((u32)temp_a1 != (u32)(live->a1 + temp_fp_2)) {
        goto loop_7;
    }
    var_t1 -= 1;
    if ((u32)(var_t1) != (u32)(0)) {
        goto loop_4;
    }
block_9:
    if ((u32)(var_s5) == (u32)(0)) {
        goto loop_17;
    }
    var_gp = D_8004F2C8;
    if ((u32)(var_gp) == (u32)(0)) {
        goto loop_12;
    }
    var_gp += (*(s16 *)((u32)(var_s1) + (14))) * 4;
loop_12:
    if ((u32)(var_gp) == (u32)(0)) {
        goto block_14;
    }
    (*(u16 *)((u32)(var_gp) + (0))) = 0xFF;
    (*(u16 *)((u32)(var_gp) + (2))) = 0;
    var_gp += 4;
block_14:
    var_s4 -= temp_s3_2;
    temp_v1 = var_at - temp_fp_2;
loop_15:
    var_at -= 8;
    *var_at = 0;
    if ((u32)(var_at) != (u32)(temp_v1)) {
        goto loop_15;
    }
    var_s5 -= 1;
    if ((u32)(var_s5) != (u32)(0)) {
        goto loop_12;
    }
loop_17:
    if ((u32)(var_v0) != (u32)(0xF3)) {
        goto block_19;
    }
    var_v0 = func_80032670() + 0xFE;
    goto block_25;
block_19:
    if ((u32)(live->a3) != (u32)(var_v0)) {
        goto block_25;
    }
    temp_fp_3 = var_s2 + temp_s3_2;
loop_21:
    var_s2 += 8;
    (*(u16 *)(live->a1)) = 0;
    if (var_s2 < temp_fp_3) {
        goto loop_21;
    }
    var_gp = D_8004F2C8;
    if ((u32)(var_gp) == (u32)(0)) {
        goto block_24;
    }
    (*(u16 *)((u32)(var_gp) + (0))) = (u16) live->a3;
    (*(u16 *)((u32)(var_gp) + (2))) = 0;
    var_gp += 4;
    D_8004F2C8 = var_gp;
block_24:
    *(u64 *)((live->a1 + 4) & ~7) = 0;
    var_v0 = func_80032670();
    goto loop_17;
block_25:
    temp_s0 = (*(s16 *)((u32)(var_s1) + (12)));
    temp_s3_3 = temp_s6 >> 1;
    if ((u32)(live->t0) != (u32)(0)) {
        goto block_62;
    }
block_26:
    var_a1 = live->a1 + 1;
    (*(u8 *)((u32)(var_a1) + (-1))) = 0;
    (*(u16 *)(var_s2)) = 0;
    *(u64 *)(-8 & (s32) (var_a1 + temp_s0)) = 0;
    var_s2_2 = var_s2 + 2;
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_28;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (0))) = var_v0;
    var_gp = var_v0 + 2;
block_28:
    temp_fp_4 = var_s2_2 + (var_v0 * 2);
    var_v0 = (u16) (var_v0 + var_a1);
loop_29:
    var_a1 += 8;
    (*(u8 *)((u32)(var_a1) + (-9))) = 0;
    (*(u16 *)((u32)(var_s2_2) + (-2))) = 0;
    (*(u16 *)((u32)(var_s2_2) + (6))) = 0;
    var_s2_2 += 0x10;
    if ((s32) var_a1 < (s32) var_v0) {
        goto loop_29;
    }
    var_s2_3 = temp_fp_4;
loop_31:
    if ((u32)(var_s2_3) == (u32)(live->t0)) {
        goto block_58;
    }
    (*(u16 *)((u32)(var_s2_3) + (-4))) = 0;
    temp_s5 = func_80032670();
    var_gp += func_80032670();
    var_v0_2 = *(u16 *)(func_80032600() * 2);
    (*(u16 *)((u32)(var_s2_3) + (0))) = var_v0_2;
    (*(u16 *)(live->a1)) = live->a3;
    var_s2_3 += 2;
    (*(u16 *)((u32)(var_s2_3) + (-4))) = var_v0_2;
    (*(u8 *)(live->a1 - 1)) = (s8) ((temp_s5 & 7) << 5);
    var_a1_2 = live->a1 + 1;
    if ((u32)(live->t1) == (u32)(var_s2_3)) {
        goto block_34;
    }
loop_33:
    *var_a1_2 = live->a3;
    var_v0_2 = *(u16 *)(func_80032600() * 2);
    var_s2_3 += 2;
    var_a1_2 = live->a1 + 1;
    (*(u16 *)((u32)(var_s2_3) + (-2))) = var_v0_2;
    if ((u32)(live->t1) != (u32)(var_s2_3)) {
        goto loop_33;
    }
block_34:
    (*(u16 *)((u32)(var_s2_3) + (0))) = var_v0_2;
    *var_a1_2 = (temp_s5 >> 4) << 6;
    (*(u16 *)((u32)(var_s2_3) + (2))) = 0;
    var_v0_3 = func_80032670();
    if ((u32)(var_v0_3) != (u32)(0xFE)) {
        goto block_36;
    }
    var_v0_3 = func_80032670() + 0xFE;
    goto block_51;
block_36:
    if ((u32)(var_v0_3) != (u32)(live->a3)) {
        goto block_51;
    }
    if ((u32)(var_s2_3) == (u32)(live->t0)) {
        goto block_41;
    }
    var_s2_3 += 2;
    var_a1_3 = live->a1 + 1;
    if ((u32)(var_s2_3) == (u32)(live->t0)) {
        goto block_41;
    }
loop_39:
    var_a1_3 += 1;
    (*(u8 *)((u32)(var_a1_3) + (-1))) = 0;
    if (var_a1_3 < live->at) {
        goto loop_39;
    }
    var_s2_3 = live->t0;
block_41:
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_43;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (2))) = (s16) var_gp;
    D_8004F2C8 += 4;
block_43:
    var_a1_4 = (live->a1 + temp_s3_3) - 1 + live->a2;
    temp_at = var_a1_4 + temp_s0 + 2;
    temp_v1_2 = (temp_at + 7) & ~7;
loop_44:
    var_a1_4 += 8;
    (*(u64 *)((u32)(var_a1_4) + (-8))) = 0;
    if ((u32)(var_a1_4) != (u32)(temp_v1_2)) {
        goto loop_44;
    }
    var_gp = D_8004F2C8;
    var_s2_4 = ((temp_s0 * 2) + ((var_s2_3 + temp_s6) - 2) + 4) - 2;
    if ((u32)(var_gp) == (u32)(0)) {
        goto block_47;
    }
    (*(u16 *)((u32)(var_gp) + (0))) = (u16) live->a3;
    var_gp = 0;
block_47:
    var_v0 = func_80032670();
    if ((u32)(var_v0) != (u32)(0xFE)) {
        goto block_49;
    }
    var_v0 = func_80032670() + 0xFE;
    goto block_94;
block_49:
    if ((u32)(var_v0) != (u32)(live->a3)) {
        goto block_94;
    }
    goto block_77;
block_51:
    temp_fp_5 = (var_v0_3 * 2) + var_s2_3;
    if ((s32) temp_fp_5 < live->t0) {
        goto block_55;
    }
    bzero((u8 *)live->a1 + 1, 8 - ((live->a1 + 1) & 7));
    bzero((u8 *)var_s2 + 1, 8 - ((var_s2 + 1) & 7));
    temp_s2 = (s32) (var_s2_3 + 8) & ~7;
    var_a1_5 = (live->a1 + 8) & ~7;
    (*(u16 *)(temp_s2)) = 0;
    var_s2_5 = temp_s2 + 8;
loop_53:
    var_a1_5 += 8;
    (*(u64 *)((u32)(var_a1_5) + (-8))) = 0;
    (*(u16 *)((u32)(var_s2_5) + (0))) = 0;
    (*(u16 *)((u32)(var_s2_5) + (8))) = 0;
    var_s2_5 += 0x10;
    if (var_a1_5 < live->at) {
        goto loop_53;
    }
    var_s2_3 = live->t0;
    var_v0 = (u16) ((u32) (temp_fp_5 - var_s2_3) >> 1);
    goto block_58;
block_55:
    var_gp += var_v0_3;
    bzero((u8 *)live->a1 + 1, 8 - ((live->a1 + 1) & 7));
    bzero((u8 *)var_s2 + 1, 8 - ((var_s2 + 1) & 7));
    temp_s2_2 = (s32) (var_s2_3 + 8) & ~7;
    var_a1_6 = (live->a1 + 8) & ~7;
    (*(u16 *)(temp_s2_2)) = 0;
    var_s2_6 = temp_s2_2 + 8;
loop_56:
    var_a1_6 += 8;
    (*(u64 *)((u32)(var_a1_6) + (-8))) = 0;
    var_v0 = var_a1_6 < (var_v0_3 + live->a1);
    (*(u16 *)((u32)(var_s2_6) + (0))) = 0;
    (*(u16 *)((u32)(var_s2_6) + (8))) = 0;
    var_s2_6 += 0x10;
    if ((u32)(var_v0) != (u32)(0)) {
        goto loop_56;
    }
    var_s2_3 = temp_fp_5;
    goto loop_31;
block_58:
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_60;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (2))) = (s16) var_gp;
    D_8004F2C8 += 4;
block_60:
    var_s2 = (s32) (var_s2_3 - 2 + temp_s6);
    if (var_s2 < var_s4) {
        goto block_62;
    }
block_61:
    return;
block_62:
    var_a1_7 = live->a1 + 1;
    (*(u8 *)((u32)(var_a1_7) + (-1))) = 0;
    (*(u16 *)(var_s2)) = 0;
    *(u64 *)(-8 & (s32) (var_a1_7 + temp_s0)) = 0;
    var_s2_7 = var_s2 + 2;
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_64;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (0))) = var_v0;
    var_gp = var_v0 + 2;
block_64:
    temp_fp_6 = var_s2_7 + (var_v0 * 2);
    var_v0 = (u16) (var_v0 + var_a1_7);
loop_65:
    var_a1_7 += 8;
    (*(u8 *)((u32)(var_a1_7) + (-9))) = 0;
    (*(u16 *)((u32)(var_s2_7) + (-2))) = 0;
    (*(u16 *)((u32)(var_s2_7) + (6))) = 0;
    var_s2_7 += 0x10;
    if ((s32) var_a1_7 < (s32) var_v0) {
        goto loop_65;
    }
    var_s2_4 = temp_fp_6;
loop_67:
    if ((u32)(var_s2_4) == (u32)(live->t0)) {
        goto block_94;
    }
    *(u16 *)((s32) (var_s2_4 - 4) ^ 4) = 0;
    temp_s5_2 = func_80032670();
    var_gp += func_80032670();
    var_v0_4 = *(u16 *)(func_80032600() * 2);
    *(u16 *)((s32) var_s2_4 ^ 4) = var_v0_4;
    *(u16 *)(live->a1 ^ 4) = (s8) live->a3;
    *(u16 *)((s32) (var_s2_4 - 2) ^ 4) = var_v0_4;
    var_s2_4 += 2;
    *(u16 *)((live->a1 - 1) ^ 4) = (s8) ((temp_s5_2 & 7) << 5);
    var_a1_8 = live->a1 + 1;
    if ((u32)(live->t1) == (u32)(var_s2_4)) {
        goto block_70;
    }
loop_69:
    var_v0_4 = *(u16 *)(func_80032600() * 2);
    temp_v1_3 = (s32) var_s2_4 ^ 4;
    var_s2_4 += 2;
    (*(u16 *)(temp_v1_3)) = var_v0_4;
    *(u16 *)(live->a1 ^ 4) = (s8) live->a3;
    var_a1_8 = live->a1 + 1;
    if ((u32)(live->t1) != (u32)(var_s2_4)) {
        goto loop_69;
    }
block_70:
    *(u16 *)((s32) var_s2_4 ^ 4) = var_v0_4;
    *(u16 *)((s32) (var_s2_4 + 2) ^ 4) = 0;
    *(u16 *)(var_a1_8 ^ 4) = (s8) ((temp_s5_2 >> 4) << 6);
    var_v0_5 = func_80032670();
    if ((u32)(var_v0_5) != (u32)(0xFE)) {
        goto block_72;
    }
    var_v0_5 = func_80032670() + 0xFE;
    goto block_87;
block_72:
    if ((u32)(var_v0_5) != (u32)(live->a3)) {
        goto block_87;
    }
    if ((u32)(var_s2_4) == (u32)(live->t0)) {
        goto block_77;
    }
    var_s2_4 += 2;
    var_a1_9 = live->a1 + 1;
    if ((u32)(var_s2_4) == (u32)(live->t0)) {
        goto block_77;
    }
loop_75:
    temp_v1_4 = var_a1_9 ^ 4;
    var_a1_9 += 1;
    (*(u16 *)(temp_v1_4)) = 0;
    if (var_a1_9 < live->at) {
        goto loop_75;
    }
    var_s2_4 = live->t0;
block_77:
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_79;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (2))) = (s16) var_gp;
    D_8004F2C8 += 4;
block_79:
    var_a1_10 = (live->a1 + temp_s3_3) - 1 + live->a2;
    var_s2_8 = (var_s2_4 + temp_s6) - 2;
    temp_at_2 = var_a1_10 + temp_s0 + 2;
    temp_t0 = (temp_s0 * 2) + var_s2_8 + 4;
    temp_v1_5 = (temp_at_2 + 7) & ~7;
loop_80:
    *var_a1_10 = 0;
    var_a1_10 += 8;
    (*(u16 *)((u32)(var_s2_8) + (0))) = 0;
    (*(u16 *)((u32)(var_s2_8) + (8))) = 0;
    var_s2_8 += 0x10;
    if ((u32)(var_a1_10) != (u32)(temp_v1_5)) {
        goto loop_80;
    }
    var_gp = D_8004F2C8;
    var_s2_3 = temp_t0 - 2;
    if ((u32)(var_gp) == (u32)(0)) {
        goto block_83;
    }
    (*(u16 *)((u32)(var_gp) + (0))) = (u16) live->a3;
    var_gp = 0;
block_83:
    var_v0 = func_80032670();
    if ((u32)(var_v0) != (u32)(0xFE)) {
        goto block_85;
    }
    var_v0 = func_80032670() + 0xFE;
    goto block_58;
block_85:
    if ((u32)(var_v0) != (u32)(live->a3)) {
        goto block_58;
    }
    goto block_41;
block_87:
    temp_fp_7 = (var_v0_5 * 2) + var_s2_4;
    if ((s32) temp_fp_7 < live->t0) {
        goto block_91;
    }
    temp_a1_2 = live->a1 + 1;
    temp_s2_3 = var_s2_4 + 1;
    *(u16 *)(temp_a1_2 ^ 4) = (s32) 0;
    *(u16 *)((s32) temp_s2_3 ^ 4) = (s32) 0;
    *(u16 *)(((temp_a1_2 + 4) ^ 4) & ~3) = 0;
    temp_s2_4 = (s32) (temp_s2_3 + 7) & ~7;
    *(u16 *)(((s32) (temp_s2_3 + 4) ^ 4) & ~3) = 0;
    var_a1_11 = (temp_a1_2 + 7) & ~7;
    (*(u16 *)(temp_s2_4)) = 0;
    var_s2_9 = temp_s2_4 + 8;
loop_89:
    var_a1_11 += 8;
    (*(u64 *)((u32)(var_a1_11) + (-8))) = 0;
    (*(u16 *)((u32)(var_s2_9) + (0))) = 0;
    (*(u16 *)((u32)(var_s2_9) + (8))) = 0;
    var_s2_9 += 0x10;
    if (var_a1_11 < live->at) {
        goto loop_89;
    }
    var_s2_4 = live->t0;
    var_v0 = (u16) ((u32) (temp_fp_7 - var_s2_4) >> 1);
    goto block_94;
block_91:
    var_gp += var_v0_5;
    temp_a1_3 = live->a1 + 1;
    *(u16 *)(temp_a1_3 ^ 4) = (s32) 0;
    temp_s2_5 = var_s2_4 + 1;
    *(u16 *)((s32) temp_s2_5 ^ 4) = (s32) 0;
    *(u16 *)(((temp_a1_3 + 4) ^ 4) & ~3) = 0;
    *(u16 *)(((s32) (temp_s2_5 + 4) ^ 4) & ~3) = 0;
    temp_s2_6 = (s32) (temp_s2_5 + 7) & ~7;
    var_a1_12 = (temp_a1_3 + 7) & ~7;
    (*(u16 *)(temp_s2_6)) = 0;
    var_s2_10 = temp_s2_6 + 8;
loop_92:
    var_a1_12 += 8;
    (*(u64 *)((u32)(var_a1_12) + (-8))) = 0;
    var_v0 = var_a1_12 < (var_v0_5 + live->a1);
    (*(u16 *)((u32)(var_s2_10) + (0))) = 0;
    (*(u16 *)((u32)(var_s2_10) + (8))) = 0;
    var_s2_10 += 0x10;
    if ((u32)(var_v0) != (u32)(0)) {
        goto loop_92;
    }
    var_s2_4 = temp_fp_7;
    goto loop_67;
block_94:
    if ((u32)(D_8004F2C8) == (u32)(0)) {
        goto block_96;
    }
    (*(u16 *)((u32)(D_8004F2C8) + (2))) = (s16) var_gp;
    D_8004F2C8 += 4;
block_96:
    var_s2 = (s32) (var_s2_4 - 2 + temp_s6);
    if (var_s2 < var_s4) {
        goto block_26;
    }
    goto block_61;
}
