#include "common.h"

extern s32 D_800614C0, D_800614C4;
extern u8 D_800614C8, D_800614C9;
void func_80026AA0(void) {
    if (++D_800614C4 >= 4) {
        D_800614C4 = 0;
        if (++D_800614C0 >= 18) D_800614C0 = 1;
    }
    if (++D_800614C9 >= 10) {
        D_800614C9 = 0;
        if (++D_800614C8 >= 6) D_800614C8 = 1;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_17140/func_80026B38.s")
