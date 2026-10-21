/* T-121 diagnostic only: corrected bounds and call ABI; 636/600 bytes, 155 words.
 * Not promoted over the existing smaller draft. See REPORT.md. */
s32 func_80031050(u8 *, s32, s32);            /* extern */
s32 func_80031DD0(u8 *, s32, s32);    /* extern */
extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2) {
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp30;
    s32 sp24;
    s32 sp20;
    s32 sp18;
    s32 temp_t6_2;
    s32 temp_a2;
    s32 temp_ra;
    s32 temp_t4;
    s32 temp_t5;
    s32 temp_t6;
    s32 temp_t8;
    s32 temp_t9;
    s32 var_a1;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_t3;
    s32 var_v0;
    s32 var_v1;

    u8 *temp_v0;

    var_v1 = ((*(u8 *)((u8 *)(arg0) + 1)) << 8) + (*(u8 *)((u8 *)(arg0) + 0));
    var_t0 = ((*(u8 *)((u8 *)(arg0) + 3)) << 8) + (*(u8 *)((u8 *)(arg0) + 2));
    temp_t4 = ((*(u8 *)((u8 *)(arg0) + 5)) << 8) + (*(u8 *)((u8 *)(arg0) + 4));
    temp_t5 = ((*(u8 *)((u8 *)(arg0) + 7)) << 8) + (*(u8 *)((u8 *)(arg0) + 6));
    if (arg1 != 0) {
        sp50 = ((*(u8 *)((u8 *)(arg1) + 5)) << 8) + (*(u8 *)((u8 *)(arg1) + 4));
        sp48 = ((*(u8 *)((u8 *)(arg1) + 3)) << 8) + (*(u8 *)((u8 *)(arg1) + 2));
        sp54 = ((*(u8 *)((u8 *)(arg1) + 7)) << 8) + (*(u8 *)((u8 *)(arg1) + 6));
        sp4C = ((*(u8 *)((u8 *)(arg1) + 1)) << 8) + (*(u8 *)((u8 *)(arg1) + 0));
    }
    var_v0 = sp4C;
    var_a1 = sp48;
    if (var_v1 >= 0x8000) {
        var_v1 += 0xFFFF0000;
    }
    if (var_v0 >= 0x8000) {
        var_v0 = (var_v0 - 0x10000);
    }
    var_v0--;
    if (var_t0 >= 0x8000) {
        var_t0 = (var_t0 - 0x10000);
    }
    var_t2 = var_v1;
    if (var_a1 >= 0x8000) {
        var_a1 = (var_a1 - 0x10000);
    }
    var_t3 = var_t0;
    if (arg1 != 0) {
        if (var_v0 >= var_v1) {
            var_t2 = var_v0;
        }
        if (var_a1 >= var_t0) {
            var_t3 = var_a1;
        }
    }
    temp_t6 = var_t2 - var_v0;
    sp20 = temp_t6;
    temp_t9 = sp50 + temp_t6;
    temp_t8 = var_t2 - var_v1;
    temp_ra = var_t3 - var_t0;
    temp_a2 = var_t3 - var_a1;
    temp_t4 += temp_t8;
    temp_t5 += temp_ra;
    sp24 = temp_t8;
    sp50 = temp_t9;
    sp54 += temp_a2;
    var_t1 = temp_t4;
    var_v1 = temp_t5;
    if (arg1 != 0) {
        if (temp_t9 >= temp_t4) {
            var_t1 = temp_t9;
        }
        if (sp54 >= temp_t5) {
            var_v1 = sp54;
        }
    }
    temp_t6_2 = (var_t1 + 9) & 0xFFF8;
    sp18 = temp_a2;
    if ((temp_t6_2 * ((var_v1 + 1) & 0xFFFE)) < 0x8891) {
        temp_v0 = (u8 *)D_8004CED0 + D_8004EA78 * 0x1C;
        (*(s16 *)((u8 *)(temp_v0) + 8)) = (s16) var_t2;
        (*(s16 *)((u8 *)(temp_v0) + 0xA)) = (s16) var_t3;
        (*(s16 *)((u8 *)(temp_v0) + 0xC)) = (s16) temp_t4;
        (*(s16 *)((u8 *)(temp_v0) + 0xE)) = (s16) var_v1;
        (*(s16 *)((u8 *)(temp_v0) + 0x10)) = temp_t6_2;
        (*(s16 *)((u8 *)(temp_v0) + 0x14)) = (s16) var_t1;
        (*(s16 *)((u8 *)(temp_v0) + 0x16)) = (s16) var_v1;
        sp30 = var_v1;
        (*(s16 *)((u8 *)(temp_v0) + 0x1A)) = (s16) arg2;
        func_80031050(arg0, sp24, ((var_v1 - temp_t5) << 0x10) | temp_ra);
        D_8004F2C8 = D_8004F2CC;
        if (arg1 != 0) {
            func_80031DD0(arg1, sp20, ((var_v1 - sp54) << 0x10) | sp18);
        }
    }
}
