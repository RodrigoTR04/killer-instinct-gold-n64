#include "common.h"

extern s8 D_801CD454;
extern s32 D_802956F8;
extern s32 D_802956FC;
extern s32 D_80295700;
extern s32 D_802D39C8;
extern s8 D_802D39CC;
extern s8 D_802D39CD;
extern f32 D_802D39D0;
extern s8 D_802D39D5;

void func_801C72B0(void) {
    D_802D39CC = -1;
    D_802D39C8 = 0;
    D_801CD454 = 0;
    D_802956F8 = D_802956FC = D_80295700 = 0;
    D_802D39D0 = 0.0f;
    D_802D39CD = 1;
    D_802D39D5 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1B790/func_801C7310.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_1B790/func_801C780C.s")
