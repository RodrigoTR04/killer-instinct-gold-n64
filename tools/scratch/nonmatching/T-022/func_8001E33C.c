/* T-022 DRAFT: 604 instruction words differ; compiled 2420 bytes, original 2360 bytes */



s32 func_8001346C(u8 **, s32, s32);       /* extern */
s32 func_80016760(s32, u8, u8);             /* extern */
s32 func_8001EC74(u8 **, s32, s32, u32, u32, s32, s32, s32); /* extern */
s32 func_80024B0C(u8 **, s32, u8, s32);       /* extern */
s32 func_8002F6F4(s32, s32, u8 *, u8 *); /* extern */
extern u8 D_80044DD4;
extern f32 D_80048A34;
extern u8 D_8004A264;
extern u8 D_8004A40C;
extern u8 D_8004A450;
extern u8 D_8004CEE8;
extern s16 D_8004D26E;
extern u8 D_8004D270;
extern s32 D_8004EA78;
extern u8 D_8004EAB9;
extern u8 D_8004F390;
extern s32 D_80066C40;
extern u8 D_801D3430;
extern u8 D_801D8771;
extern u8 D_801D8798;
extern u8 D_801D87AC;
extern u8 D_801D87E0;

void func_8001E33C(u8 **arg0, u8 arg1) {
    s16 sp96;
    s16 sp94;
    s16 sp92;
    s16 sp90;
    s16 sp8E;
    s16 sp8C;
    s16 sp8A;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    u8 *sp3C;
    u8 *sp38;
    u8 *sp34;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s16 temp_t0;
    s16 temp_v0_10;
    s16 temp_v0_11;
    s16 temp_v0_9;
    s16 var_ra;
    s16 var_t4;
    s16 var_t5;
    s32 temp_t1_2;
    s32 var_a1;
    s32 var_t0;
    u16 var_t1;
    u16 var_t2;
    u32 temp_a3_2;
    u32 temp_t1;
    u8 *temp_t2;
    u8 temp_a3;
    u8 temp_t6;
    u8 temp_t9;
    u8 temp_v0_8;
    u8 var_a2;
    u8 var_v1;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *temp_a1_3;
    u8 *temp_v0;
    u8 *temp_v0_12;
    u8 *temp_v0_13;
    u8 *temp_v0_14;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v0_6;
    u8 *temp_v0_7;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *temp_v1_3;
    u8 *var_t3;
    u8 *var_t3_2;

    var_a2 = arg1 & 0xFF;
    var_t3 = (var_a2 << 8) + &D_801D3430;
    temp_a3 = var_a2;
    if ((*(u8 *)((u8 *)(var_t3) + -0x17C)) != 0) {
        arg1 = var_a2;
        sp38 = var_t3;
        func_80016760(1, var_a2, temp_a3);
        var_t3_2 = var_t3;
        if ((*(u8 *)((u8 *)(var_t3_2) + -0x17A)) != 0) {
            temp_a1 = (arg1 * 0x30) + &D_8004A450;
            (*(f32 *)((u8 *)(&D_8004A7A0) + 8)) = (f32) (*(f32 *)((u8 *)(temp_a1) + 0x10));
            (*(f32 *)((u8 *)(&D_8004A740) + 8)) = (f32) (*(f32 *)((u8 *)(temp_a1) + 0xC));
            (*(f32 *)((u8 *)(&D_8004A800) + 8)) = (f32) (*(f32 *)((u8 *)(temp_a1) + 0x14));
            if ((*(f32 *)((u8 *)(&D_8004A7A0) + 8)) != 0.0f) {
                if ((D_801D87AC == 0) && (D_8004A40C == 0)) {
                    if ((*(s16 *)((u8 *)(var_t3_2) + 0x7C)) > 0) {
                        (*(f32 *)((u8 *)(&D_8004A920) + 8)) = (f32) ((*(f32 *)((u8 *)(&D_8004A920) + 8)) - 6.0f);
                    } else {
                        (*(f32 *)((u8 *)(&D_8004A920) + 8)) = (f32) ((*(f32 *)((u8 *)(&D_8004A920) + 8)) + 6.0f);
                    }
                }
            } else if (D_8004EAB9 == 0) {
                D_8004EAB9 = 1;
                sp38 = var_t3_2;
                func_8002F6F4(D_80066C40, 8, &D_8004A264, &D_8004EAB9);
            }
            if ((*(f32 *)((u8 *)(&D_8004A920) + 8)) < 0.0f) {
                (*(f32 *)((u8 *)(&D_8004A920) + 8)) = (f32) ((*(f32 *)((u8 *)(&D_8004A920) + 8)) + 360.0f);
            } else if (D_80048A34 < (*(f32 *)((u8 *)(&D_8004A920) + 8))) {
                (*(f32 *)((u8 *)(&D_8004A920) + 8)) = (f32) ((*(f32 *)((u8 *)(&D_8004A920) + 8)) - 360.0f);
            }
        } else {
            temp_a1_2 = (arg1 * 0x30) + &D_8004A450;
            temp_f2 = (*(f32 *)((u8 *)(temp_a1_2) + 0x10));
            temp_f0 = (*(f32 *)((u8 *)(temp_a1_2) + 0xC));
            temp_f12 = (*(f32 *)((u8 *)(temp_a1_2) + 0x14));
            D_8004EAB9 = 0;
            (*(f32 *)((u8 *)(&D_8004A7A0) + 8)) = (f32) (temp_f2 + 100.0f);
            (*(f32 *)((u8 *)(&D_8004A7A0) + 0)) = temp_f2;
            (*(f32 *)((u8 *)(&D_8004A7A0) + 4)) = temp_f2;
            (*(f32 *)((u8 *)(&D_8004A740) + 0)) = temp_f0;
            (*(f32 *)((u8 *)(&D_8004A740) + 4)) = temp_f0;
            (*(f32 *)((u8 *)(&D_8004A740) + 8)) = temp_f0;
            (*(f32 *)((u8 *)(&D_8004A800) + 0)) = temp_f12;
            (*(f32 *)((u8 *)(&D_8004A800) + 4)) = temp_f12;
            (*(f32 *)((u8 *)(&D_8004A800) + 8)) = temp_f12;
            if ((*(u8 *)((u8 *)(&D_801D8798) + 0xC)) != 0) {
                (*(u8 *)((u8 *)(&D_801D8798) + 0xC)) = 0U;
                (*(f32 *)((u8 *)(&D_8004A8C0) + 4)) = 0.0f;
                (*(f32 *)((u8 *)(&D_8004A8C0) + 8)) = 0.0f;
                (*(f32 *)((u8 *)(&D_8004A920) + 8)) = 0.0f;
            }
        }
        var_t0 = 0;
        do {
            if (var_t0 == 0) {
                var_a1 = 0x11;
            } else {
                var_a1 = var_t0 + 0x14;
            }
            if ((var_t0 == 2) || ((*(u8 *)((u8 *)(var_t3_2) + -0x17A)) == 0)) {
                temp_v0 = *arg0;
                *arg0 = temp_v0 + 8;
                (*(s32 *)((u8 *)(temp_v0) + 4)) = 0;
                (*(s32 *)((u8 *)(temp_v0) + 0)) = 0xE7000000;
                temp_v0_2 = *arg0;
                *arg0 = temp_v0_2 + 8;
                (*(s32 *)((u8 *)(temp_v0_2) + 4)) = 0x80000;
                (*(s32 *)((u8 *)(temp_v0_2) + 0)) = 0xBA001301;
                sp38 = var_t3_2;
                sp78 = var_t0;
                func_8001346C(arg0, var_a1, 0);
                temp_v0_3 = *arg0;
                *arg0 = temp_v0_3 + 8;
                (*(s32 *)((u8 *)(temp_v0_3) + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)(temp_v0_3) + 4)) = 0;
                temp_v0_4 = *arg0;
                *arg0 = temp_v0_4 + 8;
                (*(s32 *)((u8 *)(temp_v0_4) + 4)) = 0;
                (*(s32 *)((u8 *)(temp_v0_4) + 0)) = 0xBA001301;
            }
            var_t0 += 1;
        } while (var_t0 != 3);
        return;
    }
    if ((temp_a3 == 1) && (D_8004AC88 == 0xC)) {
        arg1 = var_a2;
        sp3C = (u8 *) temp_a3;
        sp38 = var_t3;
        func_80016760(3, var_a2, temp_a3);
        var_a2 = arg1;
    }
    temp_a1_3 = (var_a2 * 0x30) + &D_8004A450;
    if ((*(u16 *)((u8 *)(temp_a1_3) + 0x22)) == 0xBE) {
        temp_v0_5 = *arg0;
        *arg0 = temp_v0_5 + 8;
        (*(s32 *)((u8 *)(temp_v0_5) + 4)) = 0;
        (*(s32 *)((u8 *)(temp_v0_5) + 0)) = 0xE7000000;
        temp_v0_6 = *arg0;
        *arg0 = temp_v0_6 + 8;
        (*(s32 *)((u8 *)(temp_v0_6) + 4)) = 0xFF;
        (*(s32 *)((u8 *)(temp_v0_6) + 0)) = 0xFA000100;
        func_80024B0C(arg0, temp_a3 ^ 1, var_a2, (s32) temp_a3);
        return;
    }
    var_t1 = (*(u16 *)((u8 *)(var_t3) + 0x58));
    var_t2 = (*(u16 *)((u8 *)(var_t3) + 0x5A));
    if (var_t1 == 0) {
        var_t1 = 0x1000;
    }
    if (var_t2 == 0) {
        var_t2 = 0x1000;
    }
    temp_v0_7 = *arg0;
    *arg0 = temp_v0_7 + 8;
    (*(s32 *)((u8 *)(temp_v0_7) + 4)) = 0;
    (*(s32 *)((u8 *)(temp_v0_7) + 0)) = 0xE7000000;
    if ((s32) (*(u8 *)((u8 *)(temp_a1_3) + 0x21)) >= 0x80) {
        sp7C = 1;
    } else {
        sp7C = 0;
    }
    D_8004EA78 = (s32) temp_a3;
    temp_t0 = *(&D_8004CEE8 + (temp_a3 * 0x1C));
    var_ra = temp_t0;
    if ((*(u8 *)((u8 *)(var_t3) + 0x95)) & 0x10) {
        var_ra = 3;
        if ((*(u16 *)((u8 *)(temp_a1_3) + 0x22)) == 0) {
            var_v1 = D_8004D270;
            if ((s32) D_8004D270 > 0) {
                temp_t9 = D_8004D270 - 1;
                D_8004D270 = temp_t9;
                var_v1 = temp_t9 & 0xFF;
            }
        } else {
            var_v1 = D_8004D270;
            if ((s32) D_8004D270 < 0x10) {
                temp_t6 = D_8004D270 + 1;
                D_8004D270 = temp_t6;
                var_v1 = temp_t6 & 0xFF;
            }
        }
        D_8004D26E = (s16) var_v1;
    } else if (D_8004EA9E[var_a2] == 9) {
        D_8004D26E = 0xB0;
    } else {
        D_8004D26E = 0xFF;
    }
    if ((D_8004A401 == 4) && ((*(&D_80044DD4 + D_8004AC88) & 0x10) == 0x10) && (D_800698C4 < 0x80) && (temp_a3 == D_801D8771)) {
        var_ra = 3;
        D_8004D26E = D_800698C4 * 2;
    }
    if (((temp_a3 + 1) == (*(u8 *)((u8 *)(&D_801D87E0) + 0))) && ((*(u8 *)((u8 *)(&D_801D87E0) + 1)) != 0)) {
        var_ra = 3;
        D_8004D26E = (D_8004D26E - ((*(u8 *)((u8 *)(&D_801D87E0) + 1)) * 4)) + 1;
    }
    temp_v0_8 = (*(u8 *)((u8 *)(var_t3) + -0x170));
    if (temp_v0_8 != 0) {
        var_ra = 3;
        if ((s32) temp_v0_8 < 0x40) {
            D_8004D26E = 0x100 - (temp_v0_8 * 4);
        } else {
            D_8004D26E = 0;
        }
    }
    if (D_8004D26E < 0) {
        D_8004D26E = 0;
    }
    if (temp_t0 != 5) {
        temp_v0_9 = (*(s16 *)((u8 *)(temp_a1_3) + 0x28));
        sp3C = &D_8004EA9E[var_a2];
        if (temp_v0_9 >= 0) {
            sp96 = temp_v0_9;
            sp90 = 0;
        } else {
            sp96 = 0;
            sp90 = -temp_v0_9;
        }
        temp_v0_10 = (*(s16 *)((u8 *)(temp_a1_3) + 0x2A));
        var_t5 = 0;
        var_t4 = 0;
        if (temp_v0_10 >= 0) {
            sp94 = temp_v0_10;
            sp8E = 0;
        } else {
            sp94 = 0;
            sp8E = -temp_v0_10;
        }
        temp_v0_11 = (*(s16 *)((u8 *)(temp_a1_3) + 0x2C));
        sp84 = (s32) var_t1;
        sp80 = (s32) var_t2;
        if (temp_v0_11 >= 0) {
            var_t4 = temp_v0_11;
        } else {
            var_t5 = temp_v0_11 * -1;
        }
        temp_t2 = var_a2 + &D_8004F390;
        if ((s32) *temp_t2 > 0) {
            temp_v1 = *arg0;
            *arg0 = temp_v1 + 8;
            (*(s32 *)((u8 *)(temp_v1) + 4)) = 0x80;
            (*(s32 *)((u8 *)(temp_v1) + 0)) = 0xFA000100;
            temp_v0_12 = *arg0;
            *arg0 = temp_v0_12 + 8;
            (*(s32 *)((u8 *)(temp_v0_12) + 4)) = 0;
            (*(s32 *)((u8 *)(temp_v0_12) + 0)) = 0xFB000000;
            temp_t1 = (*(u32 *)((u8 *)(var_t3) + 0x70));
            sp8A = var_ra;
            sp8C = var_t5;
            sp92 = var_t4;
            sp38 = var_t3;
            sp34 = temp_t2;
            func_8001EC74(arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, (u32) (temp_t1 * sp84) >> 0xC, (u32) (temp_t1 * sp80) >> 0xC, (s32) var_ra, sp7C, 0);
            *temp_t2 = 0;
        }
        if (*sp3C == 9) {
            var_ra = 1;
            sp80 *= 3;
        }
        temp_v1_2 = *arg0;
        *arg0 = temp_v1_2 + 8;
        (*(s32 *)((u8 *)(temp_v1_2) + 0)) = 0xFA000100;
        (*(s32 *)((u8 *)(temp_v1_2) + 4)) = (s32) ((sp96 << 0x18) | ((sp94 & 0xFF) << 0x10) | ((var_t4 & 0xFF) << 8) | 0xFF);
        temp_v0_13 = *arg0;
        *arg0 = temp_v0_13 + 8;
        (*(s32 *)((u8 *)(temp_v0_13) + 0)) = 0xFB000000;
        (*(s32 *)((u8 *)(temp_v0_13) + 4)) = (s32) ((sp90 << 0x18) | ((sp8E & 0xFF) << 0x10) | ((var_t5 & 0xFF) << 8));
        temp_t1_2 = (*(s32 *)((u8 *)(var_t3) + 0x70));
        func_8001EC74(arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, (u32) (temp_t1_2 * sp84) >> 0xC, (u32) (temp_t1_2 * sp80) >> 0xC, (s32) var_ra, (s32) (*((u8 *)&sp7C + 3)), 0);
        return;
    }
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 8;
    (*(s32 *)((u8 *)(temp_v1_3) + 4)) = -1;
    (*(s32 *)((u8 *)(temp_v1_3) + 0)) = 0xFA000100;
    temp_v0_14 = *arg0;
    *arg0 = temp_v0_14 + 8;
    (*(s32 *)((u8 *)(temp_v0_14) + 4)) = 0;
    (*(s32 *)((u8 *)(temp_v0_14) + 0)) = 0xFB000000;
    temp_a3_2 = (*(u32 *)((u8 *)(var_t3) + 0x70));
    func_8001EC74(arg0, (s32) (*(s32 *)((u8 *)(var_t3) + 0x68)) / 16, (s32) (*(s32 *)((u8 *)(var_t3) + 0x6C)) / 16, temp_a3_2, temp_a3_2, 5, sp7C, 0);
}
