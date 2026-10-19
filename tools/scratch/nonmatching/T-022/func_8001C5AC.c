/* T-022 DRAFT: 431 instruction words differ; compiled 1908 bytes, original 1568 bytes */

extern void func_8001CD0C(void *arg0, f32 arg1, f32 arg2, f32 arg3);

s32 func_8001BB64(s32 **);                      /* extern */
s32 guRotateRPY(u8 *, f32, f32, f32);         /* extern */
s32 guScale(u8 *, f32, f32, f32);             /* extern */
s32 guTranslate(u8 *, s32, s32, s32);         /* extern */
extern u8 D_80044A24;
extern f32 D_8004A980;
extern u8 D_8004A984;
extern u8 D_8004A998;
extern u8 D_8004A9A4;
extern u8 D_8004AEB8;

void func_8001C5AC(s32 **arg0, s32 arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8, f32 arg9, f32 arg10, s32 arg11) {
    f32 temp_f0;
    s32 *temp_v1;
    s32 *temp_v1_10;
    s32 *temp_v1_11;
    s32 *temp_v1_12;
    s32 *temp_v1_13;
    s32 *temp_v1_14;
    s32 *temp_v1_15;
    s32 *temp_v1_16;
    s32 *temp_v1_17;
    s32 *temp_v1_18;
    s32 *temp_v1_19;
    s32 *temp_v1_20;
    s32 *temp_v1_2;
    s32 *temp_v1_3;
    s32 *temp_v1_4;
    s32 *temp_v1_5;
    s32 *temp_v1_6;
    s32 *temp_v1_7;
    s32 *temp_v1_8;
    s32 *temp_v1_9;
    s32 temp_t1;
    s32 temp_v0;
    s32 var_a1;
    s32 var_a3;
    s32 var_t9;
    u8 **var_a0;
    u8 *temp_t2;
    u8 *var_a0_2;

    if (((arg2 != 0) || (*(&D_8004A9A4 + ((arg3 * 0x10) + -(arg4 * 4))) != 0)) && (D_8004AEB0 != 0x14)) {
        if (arg1 == 0) {
            temp_v1 = *arg0;
            *arg0 = temp_v1 + 8;
            (*(u8 **)((u8 *)(temp_v1) + 4)) = (u8 *)0x2000;
            (*(s32 *)((u8 *)(temp_v1) + 0)) = 0xB7000000;
            temp_v1_2 = *arg0;
            var_t9 = 0xB6000000;
            *arg0 = temp_v1_2 + 8;
            (*(u8 **)((u8 *)(temp_v1_2) + 4)) = (u8 *)0x1000;
        } else {
            temp_v1_3 = *arg0;
            *arg0 = temp_v1_3 + 8;
            (*(u8 **)((u8 *)(temp_v1_3) + 4)) = (u8 *)0x2000;
            (*(s32 *)((u8 *)(temp_v1_3) + 0)) = 0xB6000000;
            temp_v1_4 = *arg0;
            var_t9 = 0xB7000000;
            *arg0 = temp_v1_4 + 8;
            (*(u8 **)((u8 *)(temp_v1_4) + 4)) = (u8 *)0x1000;
        }
        (*(s32 *)((u8 *)(*arg0) + 0)) = var_t9;
        temp_v1_5 = *arg0;
        *arg0 = temp_v1_5 + 8;
        (*(u8 **)((u8 *)(temp_v1_5) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_v1_5) + 0)) = 0xE7000000;
        func_8001BB64(arg0);
        guTranslate((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + &D_8004AEB8, arg5, arg6, arg7);
        if (arg1 == 1) {
            func_8001CD0C((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0x500 + &D_8004AEB8, arg8, arg9, arg10);
        } else {
            guRotateRPY((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0x500 + &D_8004AEB8, arg8, arg9, arg10);
        }
        if (D_8004A984 != 0) {
            guRotateRPY((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0x500 + &D_8004AEB8, arg8, arg9, arg10);
        }
        temp_v1_6 = *arg0;
        *arg0 = temp_v1_6 + 8;
        (*(s32 *)((u8 *)(temp_v1_6) + 0)) = 0x01040040;
        (*(u8 **)((u8 *)(temp_v1_6) + 4)) = (u8 *) (&D_8004AEB8 + (D_80044A24 * 0xF00) + (D_8004AEB0 << 6));
        temp_v1_7 = *arg0;
        *arg0 = temp_v1_7 + 8;
        (*(s32 *)((u8 *)(temp_v1_7) + 0)) = 0x01000040;
        (*(u8 **)((u8 *)(temp_v1_7) + 4)) = (u8 *) (&D_8004AEB8 + (D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0x500);
        if (D_8004A984 != 0) {
            guRotateRPY(&D_8004AEB8 + (D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0xA00, 0.0f, D_8004A980, 0.0f);
            temp_v1_8 = *arg0;
            *arg0 = temp_v1_8 + 8;
            (*(s32 *)((u8 *)(temp_v1_8) + 0)) = 0x01000040;
            (*(u8 **)((u8 *)(temp_v1_8) + 4)) = (u8 *) ((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0xA00 + &D_8004AEB8);
        } else if ((arg11 != 0) && (arg11 != 0x1000)) {
            temp_f0 = (f32) arg11 / 4096.0f;
            guScale(&D_8004AEB8 + (D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0xA00, temp_f0, temp_f0, temp_f0);
            temp_v1_9 = *arg0;
            *arg0 = temp_v1_9 + 8;
            (*(s32 *)((u8 *)(temp_v1_9) + 0)) = 0x01000040;
            (*(u8 **)((u8 *)(temp_v1_9) + 4)) = (u8 *) ((D_80044A24 * 0xF00) + (D_8004AEB0 << 6) + 0xA00 + &D_8004AEB8);
        }
        if (arg2 != 0) {
            temp_v1_10 = *arg0;
            *arg0 = temp_v1_10 + 8;
            (*(u8 **)((u8 *)(temp_v1_10) + 4)) = arg2;
            (*(s32 *)((u8 *)(temp_v1_10) + 0)) = 0x06000000;
        } else {
            temp_t1 = 3 - arg4;
            var_a1 = 3;
            if (temp_t1 < 4) {
                temp_v0 = -(((3 - temp_t1) + 1) & 3);
                temp_t2 = (arg3 * 0x10) + &D_8004A998;
                if (temp_v0 != 0) {
                    var_a0 = temp_t2 + (3 * 4);
                    do {
                        var_a1 -= 1;
                        if (*var_a0 != 0) {
                            temp_v1_11 = *arg0;
                            *arg0 = temp_v1_11 + 8;
                            (*(s32 *)((u8 *)(temp_v1_11) + 0)) = 0x06000000;
                            (*(u8 **)((u8 *)(temp_v1_11) + 4)) = (u8 *) *var_a0;
                        }
                        var_a0 -= 4;
                    } while ((temp_v0 + 3) != var_a1);
                    if ((var_a1 + 1) != temp_t1) {
                        goto block_25;
                    }
                } else {
block_25:
                    var_a3 = var_a1 * 4;
                    var_a0_2 = temp_t2 + var_a3;
                    do {
                        var_a3 -= 0x10;
                        if ((*(u8 **)((u8 *)(var_a0_2) + 0)) != 0) {
                            temp_v1_12 = *arg0;
                            *arg0 = temp_v1_12 + 8;
                            (*(s32 *)((u8 *)(temp_v1_12) + 0)) = 0x06000000;
                            (*(u8 **)((u8 *)(temp_v1_12) + 4)) = (u8 *) (*(u8 **)((u8 *)(var_a0_2) + 0));
                        }
                        if ((*(u8 **)((u8 *)(var_a0_2) + -4)) != 0) {
                            temp_v1_13 = *arg0;
                            *arg0 = temp_v1_13 + 8;
                            (*(s32 *)((u8 *)(temp_v1_13) + 0)) = 0x06000000;
                            (*(u8 **)((u8 *)(temp_v1_13) + 4)) = (u8 *) (*(u8 **)((u8 *)(var_a0_2) + -4));
                        }
                        if ((*(u8 **)((u8 *)(var_a0_2) + -8)) != 0) {
                            temp_v1_14 = *arg0;
                            *arg0 = temp_v1_14 + 8;
                            (*(s32 *)((u8 *)(temp_v1_14) + 0)) = 0x06000000;
                            (*(u8 **)((u8 *)(temp_v1_14) + 4)) = (u8 *) (*(u8 **)((u8 *)(var_a0_2) + -8));
                        }
                        if ((*(u8 **)((u8 *)(var_a0_2) + -0xC)) != 0) {
                            temp_v1_15 = *arg0;
                            *arg0 = temp_v1_15 + 8;
                            (*(s32 *)((u8 *)(temp_v1_15) + 0)) = 0x06000000;
                            (*(u8 **)((u8 *)(temp_v1_15) + 4)) = (u8 *) (*(u8 **)((u8 *)(var_a0_2) + -0xC));
                        }
                        var_a0_2 -= 0x10;
                    } while (var_a3 != ((temp_t1 - 1) * 4));
                }
            }
        }
        temp_v1_16 = *arg0;
        *arg0 = temp_v1_16 + 8;
        (*(u8 **)((u8 *)(temp_v1_16) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_v1_16) + 0)) = 0xBD000000;
        if (arg1 != 0) {
            temp_v1_17 = *arg0;
            *arg0 = temp_v1_17 + 8;
            (*(u8 **)((u8 *)(temp_v1_17) + 4)) = (u8 *)0x2000;
            (*(s32 *)((u8 *)(temp_v1_17) + 0)) = 0xB7000000;
            temp_v1_18 = *arg0;
            *arg0 = temp_v1_18 + 8;
            (*(u8 **)((u8 *)(temp_v1_18) + 4)) = (u8 *)0x1000;
            (*(s32 *)((u8 *)(temp_v1_18) + 0)) = 0xB6000000;
        }
        temp_v1_19 = *arg0;
        *arg0 = temp_v1_19 + 8;
        (*(u8 **)((u8 *)(temp_v1_19) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_v1_19) + 0)) = 0xE7000000;
        temp_v1_20 = *arg0;
        *arg0 = temp_v1_20 + 8;
        (*(u8 **)((u8 *)(temp_v1_20) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_v1_20) + 0)) = 0xB9000002;
        D_8004AEB0 += 1;
    }
}
