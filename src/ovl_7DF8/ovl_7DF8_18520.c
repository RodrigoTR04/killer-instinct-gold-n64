#include "common.h"

extern u8 D_8004EA9B[], D_8004EA9D[], D_802D3959, D_802D395A;

void func_801C4040(u8 arg0) {
    if (arg0 != 0) {
        D_802D3959 = D_8004EA9B[arg0];
        D_802D395A = D_8004EA9D[arg0];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18520/func_801C407C.s")

void func_801C4238(void) {}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18520/func_801C4240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18520/func_801C4780.s")
