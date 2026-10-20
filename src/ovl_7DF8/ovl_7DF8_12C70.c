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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF0E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF788.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF914.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BF988.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_12C70/func_801BFA40.s")
