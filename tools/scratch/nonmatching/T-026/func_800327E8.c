/* DRAFT. Remaining diff: 286 differing instruction words; emitted 1168 / original 1096 bytes (positional comparison). */
/* Arithmetic interval decode; tree links use byte offsets, counts are 32-bit. */
extern u8 D_80066590;
extern s32 D_80066594;
extern u8 *D_8006659C;
extern s32 D_800669A8;
extern s32 D_800669AC;
extern s32 D_800669B0;

u8 func_800327E8(u32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 *temp_s1_2;
    s32 *temp_s1_3;
    s32 *var_a1;
    s32 *var_t2;
    s32 temp_t7;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32 var_s1;
    s32 var_s3;
    s32 var_t1;
    s32 var_t6;
    s32 var_t7;
    s32 var_t7_2;
    s32 var_t8;
    s32 var_t9_2;
    s32 var_v1_2;
    u32 *var_a0;
    u32 temp_lo;
    u32 temp_lo_2;
    u32 temp_t3;
    u32 temp_t4;
    u32 temp_v0;
    u32 var_t9;
    u32 var_v0;
    u32 var_v1;
    u8 *temp_t7_2;
    u8 *temp_t9;
    u8 *var_s7;
    u8 temp_at;
    u8 temp_s1;
    u8 var_s5;
    u8 *var_v0_2;

    var_a0 = arg0;
    var_a1 = arg1;
    var_t6 = D_800669A8;
    temp_t3 = *var_a0;
    temp_t4 = (D_800669B0 - D_800669AC) + 1;
    temp_lo = (u32) ((((var_t6 - D_800669AC) + 1) * temp_t3) - 1) / temp_t4;
    var_s3 = D_80066594;
    var_s5 = D_80066590;
    var_s7 = D_8006659C + 1;
    var_t8 = 1;
    var_v0_2 = (u8 *)var_a0 + 0x400;
    temp_v1 = (*(s32 *)(var_v0_2 + -512));
    if ((s32) temp_lo < (temp_v1 + 1)) {

    } else {
        var_v0_2 -= 0x200;
        var_t8 = temp_v1 + 1;
    }
    temp_v1_2 = (*(s32 *)(var_v0_2 + -256));
    if ((s32) temp_lo < (temp_v1_2 + var_t8)) {

    } else {
        var_v0_2 -= 0x100;
        var_t8 += temp_v1_2;
    }
    temp_v1_3 = (*(s32 *)(var_v0_2 + -128));
    if ((s32) temp_lo < (temp_v1_3 + var_t8)) {

    } else {
        var_v0_2 -= 0x80;
        var_t8 += temp_v1_3;
    }
    temp_v1_4 = (*(s32 *)(var_v0_2 + -64));
    if ((s32) temp_lo < (temp_v1_4 + var_t8)) {

    } else {
        var_v0_2 -= 0x40;
        var_t8 += temp_v1_4;
    }
    temp_v1_5 = (*(s32 *)(var_v0_2 + -32));
    if ((s32) temp_lo < (temp_v1_5 + var_t8)) {

    } else {
        var_v0_2 -= 0x20;
        var_t8 += temp_v1_5;
    }
    temp_v1_6 = (*(s32 *)(var_v0_2 + -16));
    if ((s32) temp_lo < (temp_v1_6 + var_t8)) {

    } else {
        var_v0_2 -= 0x10;
        var_t8 += temp_v1_6;
    }
    temp_v1_7 = (*(s32 *)(var_v0_2 + -8));
    if ((s32) temp_lo < (temp_v1_7 + var_t8)) {

    } else {
        var_v0_2 -= 8;
        var_t8 += temp_v1_7;
    }
    temp_v1_8 = (*(s32 *)(var_v0_2 + -4));
    if ((s32) temp_lo < (temp_v1_8 + var_t8)) {

    } else {
        var_v0_2 -= 4;
        var_t8 += temp_v1_8;
    }
    temp_v0 = var_v0_2 - (u8 *)var_a0;
    var_t2 = temp_v0 + var_a1;
    var_v0 = temp_v0 >> 2;
    if (var_v0 != 0x101) {
        temp_lo_2 = ((*(s32 *)(var_t2 + 0)) + var_t8) * temp_t4;
        if (*var_a0 != 0x3FFF) {

        } else {
            var_t7 = 0;
loop_37:
            var_a1 += 4;
            var_a0 += 4;
            var_t7 += 1;
            *var_a1 = 1;
            var_t9 = 1;
loop_38:
            if (!(var_t9 & var_t7)) {
                var_t9 *= 2;
                goto loop_38;
            }
            *var_a0 = var_t9;
            if (var_t7 != 0x101) {
                goto loop_37;
            }
            *(var_a1 - 0x404) = 0;
            var_a0 -= 0x404;
            *var_a0 = 0x101;
        }
        var_v1 = var_v0;
        temp_t7 = (*(s32 *)(var_t2 + 0));
        if (temp_t7 != (*(s32 *)(var_t2 + -4))) {

        } else {
            do {
                var_t2 -= 4;
                var_v1 -= 1;
            } while ((*(s32 *)(var_t2 + -4)) == temp_t7);
        }
        temp_t7_2 = var_v1 + arg2;
        temp_t9 = var_v0 + arg2;
        temp_s1 = *temp_t7_2;
        temp_at = *temp_t9;
        *temp_t7_2 = temp_at;
        *temp_t9 = temp_s1;
        *(s32 *)(arg3 + (temp_s1 * 4)) = var_v0;
        var_v0 = (u32) temp_at;
        *(s32 *)(arg3 + (temp_at * 4)) = var_v1;
        *var_t2 += 1;
        temp_v1_9 = var_v1 - 1;
        *var_a0 += 1;
        if (temp_v1_9 > 0) {
            var_v1_2 = temp_v1_9 * 4;
            var_t9_2 = 0x3FFFC;
            temp_s1_2 = var_v1_2 + var_a0;
            *temp_s1_2 += 1;
            var_t7_2 = 0x3FFFC & var_v1_2;
            do {
                if (var_v1_2 != var_t7_2) {
                    var_v1_2 = var_t7_2;
                    temp_s1_3 = var_v1_2 + var_a0;
                    *temp_s1_3 += 1;
                }
                var_t9_2 *= 2;
                var_t7_2 = var_t9_2 & var_v1_2;
            } while (var_t7_2 != 0);
        }
        var_s1 = (temp_lo_2 / temp_t3) - 1 + D_800669AC;
        var_t1 = D_800669AC + (s32) (((f64) temp_t4 * (f64) var_t8) / (f64) temp_t3);
loop_55:
        if (!(var_s1 & 0x8000)) {
block_61:
            var_t1 *= 2;
            var_s1 = (var_s1 * 2) + 1;
            var_s3 -= 1;
            var_t6 = (var_t6 * 2) + (var_s5 & 1);
            var_s5 = (u8) (var_s5 >> 1);
            if (var_s3 != 0) {

            } else {
                var_s5 = *var_s7;
                var_s3 = 8;
                D_8006659C = var_s7;
                var_s7 += 1;
            }
            goto loop_55;
        }
        if (var_t1 & 0x8000) {
            var_t1 -= 0x8000;
            var_s1 -= 0x8000;
            var_t6 -= 0x8000;
            goto block_61;
        }
        if ((var_t1 & 0x4000) && !(var_s1 & 0x4000)) {
            var_t1 -= 0x4000;
            var_s1 -= 0x4000;
            var_t6 -= 0x4000;
            goto block_61;
        }
        D_800669AC = var_t1;
        D_800669B0 = var_s1;
        D_800669A8 = var_t6;
        D_80066594 = var_s3;
        D_80066590 = var_s5;
    }
    return (u8) var_v0;
}
