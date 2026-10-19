/* DRAFT. Remaining diff: 413 linked instruction words; compiled 1748 bytes, original 1656 bytes. */

extern u8 D_8004EA9C[];
s32 func_8001D47C(u8);                          /* extern */
s32 func_8001DE5C(u8 *, u8 *, u8, u8 *);  /* extern */
s32 func_80024144(u8, u8);                      /* extern */
s32 func_800241BC(u8, u8);                      /* extern */
s32 func_800244F0(u8, u8);                      /* extern */
s32 func_80024714(u8, u8);                      /* extern */
s32 func_8002A1A0(u8);                          /* extern */
s32 func_800310C0(u8 *, s32 *, s32, u8 *);  /* extern */
s32 func_80031A38(u8 *, s32 *, s32, u8 *);  /* extern */
extern u8 D_8004D278;
extern s32 D_8004EA78;
extern s32 D_8004EA90;
extern s32 D_8004EA94;
extern s16 D_8004EA98;
extern u8 D_8004EA9A;
extern u8 D_8004F394;
extern u8 D_8004F395;
extern u8 D_8004F396;
extern u8 D_8004F398;
extern u8 D_801D34BE;

void func_8001D7E4(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4) {
    s32 sp50;
    u8 *sp1C;
    T022Sprite *temp_t0;
    s16 var_t2;
    s32 temp_t5;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0_6;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3_2;
    s32 var_t7;
    s32 var_v0;
    u8 temp_t6;
    u8 temp_v0;
    u8 temp_v0_2;
    u8 *temp_a0;
    u8 *temp_t0_2;
    u8 *temp_t6_2;
    u8 *temp_v0_3;
    u8 *temp_v0_4;
    u8 *temp_v0_5;
    u8 *temp_v1;
    u8 *var_a3;
    u8 *var_v0_2;

    temp_t6 = arg3 & 0xFF;
    if ((arg1 == 0xC7) && (D_8004F398 == 0)) {
        arg3 = temp_t6;
        func_800244F0(temp_t6, temp_t6);
    } else if ((((arg1 == 0xB0) && (D_8004EA9C[temp_t6] != 1)) || ((arg1 == 0xAE) && ((temp_v0 = D_8004EA9C[temp_t6], (temp_v0 == 3)) || (temp_v0 == 5))) || ((arg1 == 0xAB) && (D_8004EA9C[temp_t6] == 4)) || (((arg1 == 0x99) || (arg1 == 0xAB)) && (D_8004EA9C[temp_t6] == 2))) && (D_8004F395 == 0)) {
        arg3 = temp_t6;
        func_800241BC(temp_t6, temp_t6);
    } else if (((arg1 == 0xB9) || (arg1 == 0xBA) || (arg1 == 0xBB) || (arg1 == 0xB1)) && (D_8004F394 == 0)) {
        arg3 = temp_t6;
        func_80024144(temp_t6, temp_t6);
    } else {
        temp_v0_2 = D_8004EA9C[temp_t6];
        if (((temp_v0_2 == 1) && ((arg1 == 0x84) || (arg1 == 0x85))) || ((temp_v0_2 == 2) && ((arg1 == 0x84) || (arg1 == 0x86) || (arg1 == 0xAD) || (arg1 == 0xBC))) || ((temp_v0_2 == 4) && ((arg1 == 0x85) || (arg1 == 0x86))) || ((arg3 = temp_t6, (temp_v0_2 == 5)) && ((arg1 == 0x83) || (arg3 = temp_t6, (arg1 == 0x86))))) {
            arg3 = temp_t6;
            if (*(&D_8004F396 + temp_t6) == 0) {
                arg3 = temp_t6;
                func_80024714(temp_t6, temp_t6);
            }
        }
    }
    func_8002A1A0(arg3);
    D_8004EA78 = arg0;
    func_8001D47C(arg3);
    var_v0 = arg1 & 0xFFFF;
    D_8004EA90 = arg2 - 1;
    D_8004EA98 = (s16) arg1;
    if (var_v0 < 0) {
        D_8004EA98 = 0;
        var_v0 = 0 & 0xFFFF;
    } else if (var_v0 >= 0x100) {
        D_8004EA98 = 0xFF;
        var_v0 = 0xFF & 0xFFFF;
    }
    temp_t9 = arg3 * 8;
    temp_v1 = &D_8004D278 + (var_v0 * 0x18) + temp_t9;
    temp_a0 = (*(u8 **)((u8 *)(temp_v1) + 0));
    if (temp_a0 != 0) {
        var_t2 = 0;
        var_a3 = temp_a0;
        if (D_8004EA9A == 1) {
            return;
        }
        goto block_46;
    }
    temp_v0_3 = (*(u8 **)((u8 *)(temp_v1) + 4));
    var_t2 = 5;
    var_a3 = temp_v0_3;
    if (temp_v0_3 != 0) {
block_46:
        var_a0 = D_8004EA90;
        temp_t5 = ((*(u8 *)((u8 *)(var_a3) + 3)) << 8) + (*(u8 *)((u8 *)(var_a3) + 2));
        D_8004EA94 = temp_t5;
        if (var_a0 >= temp_t5) {
            var_a0 = temp_t5 - 1;
            D_8004EA90 = var_a0;
        }
        if (var_a0 < 0) {
            D_8004EA90 = 0;
            var_a0 = 0;
        }
        temp_t0 = &D_8004CED0[D_8004EA78];
        temp_t0->flags = var_t2;
        temp_v0_4 = (var_a0 * 4) + var_a3;
        var_a2 = ((*(u8 *)((u8 *)(temp_v0_4) + 0xB)) << 0x18) + (*(u8 *)((u8 *)(temp_v0_4) + 8)) + ((*(u8 *)((u8 *)(temp_v0_4) + 9)) << 8) + ((*(u8 *)((u8 *)(temp_v0_4) + 0xA)) << 0x10);
        temp_v1_2 = ((*(u8 *)((u8 *)(var_a3) + 7)) << 0x18) + (*(u8 *)((u8 *)(var_a3) + 4)) + ((*(u8 *)((u8 *)(var_a3) + 5)) << 8) + ((*(u8 *)((u8 *)(var_a3) + 6)) << 0x10);
        if (var_a2 >= temp_v1_2) {
            do {
                temp_t7 = var_a0 - 1;
                D_8004EA90 = temp_t7;
                temp_v0_5 = (temp_t7 * 4) + var_a3;
                var_a0 = temp_t7;
                var_a2 = ((*(u8 *)((u8 *)(temp_v0_5) + 0xB)) << 0x18) + (*(u8 *)((u8 *)(temp_v0_5) + 8)) + ((*(u8 *)((u8 *)(temp_v0_5) + 9)) << 8) + ((*(u8 *)((u8 *)(temp_v0_5) + 0xA)) << 0x10);
            } while (var_a2 >= temp_v1_2);
        }
        switch (D_8004EA9A) {
        case 0:
            sp50 = 0x8890;
            break;
        case 2:
            sp50 = 0x1E40;
            break;
        case 3:
            sp50 = 0x780;
            break;
        case 4:
            sp50 = 0x780;
            break;
        case 5:
            var_t7 = 0x6180;
block_64:
            sp50 = var_t7;
            break;
        case 6:
        case 7:
        case 8:
            sp50 = 0x1800;
            break;
        case 10:
            sp50 = 0x7E90;
            break;
        case 9:
            sp50 = 0x3408;
            break;
        case 11:
            sp50 = 0x100;
            break;
        case 12:
            var_t7 = 0x1200;
            goto block_64;
        }
        temp_t6_2 = var_a3 + var_a2;
        sp1C = temp_t6_2;
        if (sp50 < (((((*(u8 *)((u8 *)(temp_t6_2) + 7)) << 8) + (*(u8 *)((u8 *)(temp_t6_2) + 6)) + 1) & 0xFFFE) * (((*(u8 *)((u8 *)(temp_t6_2) + 4)) + ((*(u8 *)((u8 *)(temp_t6_2) + 5)) << 8) + 9) & 0xFFF8))) {
            temp_t0->height2 = 0x10;
            temp_t0->width = 0x10;
            temp_t0->width2 = 0x10;
            temp_t0->height = temp_t0->height2;
            return;
        }
        if ((var_t2 != 0) && (arg4 != 0)) {
            arg4 = 0U;
        }
        if (arg4 != 0) {
            temp_t0_2 = (*(u8 **)((u8 *)((&D_8004D278 + (arg4 * 0x18) + temp_t9)) + 4));
            if (temp_t0_2 == 0) {
                func_8001DE5C(sp1C, 0, 0U, var_a3);
                return;
            }
            var_a1 = var_a0;
            temp_v0_6 = ((*(u8 *)((u8 *)(temp_t0_2) + 3)) << 8) + (*(u8 *)((u8 *)(temp_t0_2) + 2));
            if (var_a0 >= temp_v0_6) {
                var_a1 = temp_v0_6 - 1;
            }
            var_v0_2 = (var_a1 * 4) + temp_t0_2;
            temp_v1_3 = ((*(u8 *)((u8 *)(temp_t0_2) + 7)) << 0x18) + (*(u8 *)((u8 *)(temp_t0_2) + 4)) + ((*(u8 *)((u8 *)(temp_t0_2) + 5)) << 8) + ((*(u8 *)((u8 *)(temp_t0_2) + 6)) << 0x10);
            var_a3_2 = ((*(u8 *)((u8 *)(var_v0_2) + 0xB)) << 0x18) + (*(u8 *)((u8 *)(var_v0_2) + 8)) + ((*(u8 *)((u8 *)(var_v0_2) + 9)) << 8) + ((*(u8 *)((u8 *)(var_v0_2) + 0xA)) << 0x10);
            if (var_a3_2 >= temp_v1_3) {
                do {
                    var_a3_2 = ((*(u8 *)((u8 *)(var_v0_2) + 7)) << 0x18) + (*(u8 *)((u8 *)(var_v0_2) + 4)) + ((*(u8 *)((u8 *)(var_v0_2) + 5)) << 8) + ((*(u8 *)((u8 *)(var_v0_2) + 6)) << 0x10);
                    var_v0_2 -= 4;
                } while (var_a3_2 >= temp_v1_3);
            }
            if (var_t2 == 0) {
                if (D_8004EA9E[arg3] == 9) {
                    func_8001DE5C(sp1C, temp_t0_2 + var_a3_2, 0x13U, (u8 *) var_a3_2);
                    return;
                }
                func_8001DE5C(sp1C, temp_t0_2 + var_a3_2, *(&D_801D34BE + (arg3 << 8)), (u8 *) var_a3_2);
            }
        } else {
            if (var_t2 == 0) {
                func_800310C0(sp1C, &D_8004EA90, var_a2, var_a3);
                return;
            }
            func_80031A38(sp1C, &D_8004EA90, var_a2, var_a3);
        }
    }
}
