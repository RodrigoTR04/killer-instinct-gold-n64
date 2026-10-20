#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BE790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BE910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BEA74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BED0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BEEA4.s")

extern void func_801BE910(s32 *, s32, s32, s32);
extern s32 func_801BEEA4(s32, s32, s32);
extern s32 func_801BF0E8(s32 *, s32, s32);
extern s32 D_80127E50;
extern s32 D_80127EA0;
extern s32 D_80127EF0;
extern s32 D_80127F40;
extern s32 D_802D36D0[];
extern s32 D_802D3748[];

void func_801BEFFC(void) {
    s32 temp_s3;
    s32 var_s0;

    temp_s3 = func_801BF0E8(&D_80127F40, 0xA, func_801BF0E8(&D_80127EF0, 0xA, func_801BF0E8(&D_80127EA0, 0xA, 0)));
    func_801BE910(&D_80127E50, 0xA, 0, 0);
    var_s0 = 0;
    if (temp_s3 > 0) {
        do {
            func_801BEEA4(0, D_802D3748[var_s0], D_802D36D0[var_s0]);
            var_s0 += 1;
        } while (var_s0 != temp_s3);
    }
    if (var_s0 < 0xA) {
        do {
            func_801BEEA4(0, 1, 0);
            var_s0 += 1;
        } while (var_s0 < 0xA);
    }
}

s32 func_801BF0E8(s32 *arg0, s32 count, s32 used) {
    s32 i, j, value;
    s32 *score;
    i = 0;
    if (count > 0) {
        do {
            value = *arg0;
            j = 0;
            while (j < used && value != D_802D36D0[j]) {
                j++;
            }
            if (j == used) {
                D_802D36D0[j] = value;
                D_802D3748[j] = 10 - i;
                used++;
            } else {
                score = &D_802D3748[j];
                *score = (*score - i) + 10;
            }
            i++;
            arg0 += 2;
        } while (i != count);
    }
    return used;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF720.s")

extern s32 func_801BF720(s32);
u8 *func_801BF788(u8 *arg0, u8 *arg1, s32 count) {
    s32 i;
    s32 first;
    u16 packed;
    i = 0;
    if (count > 0) {
        do {
            packed = (arg0[0] << 8) + arg0[1];
            first = func_801BF720((packed >> 10) & 31) << 24;
            first |= (func_801BF720((packed >> 5) & 31) << 16);
            first |= func_801BF720(packed & 31) << 8;
            *(s32 *)arg1 = first;
            i++;
            arg1 += 8;
            arg0 += 3;
            *(s16 *)(arg1 - 4) = arg0[-1];
        } while (i != count);
    }
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF914.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF988.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BFA40.s")
