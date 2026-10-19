#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CBBE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CBCCC.s")

extern s32 osCreateMesgQueue();
extern s32 osCreateThread();
extern s32 osSetEventMesg();
extern s32 osStartThread();
extern u8 D_8011E650;
extern u8 D_802D3E18;
extern u8 D_802D3FC8;
extern u8 D_802D3FE0;
extern void func_801CBCCC();

void func_801CBED0(void) {
    osCreateThread(&D_802D3E18, 0x49, &func_801CBCCC, 0, &D_8011E650, 2);
    osCreateMesgQueue(&D_802D3FC8, &D_802D3FE0, 2);
    osSetEventMesg(0xE, &D_802D3FC8, 8);
    osStartThread(&D_802D3E18);
}

extern s32 osSendMesg();
extern s32 osSetThreadPri();
extern u8 D_802D3E18;
extern u8 D_802D3FC8;

void func_801CBF50(void) {
    osSendMesg(&D_802D3FC8, 1, 1);
    osSetThreadPri(&D_802D3E18, 0x7F);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CBF8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC1A4.s")

s32 __osContDataCrc();

extern s32 osEepromLongWrite();

s32 osEepromProbe();

extern u8 D_800684E0;
extern u8 D_802D3E16;

void func_801CC264(u8 *arg0) {
    D_802D3E16 = osEepromProbe(&D_800684E0);
    arg0[0x1FF] = __osContDataCrc(arg0);
    if (D_802D3E16 != 0) {
        osEepromLongWrite(&D_800684E0, 0, arg0, 0x200);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC2C8.s")

extern s32 func_80034630();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

void func_801CC350(s32 arg0, s32 arg1) {
    func_80034630((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC3BC.s")

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

void func_801CC524(s32 arg0, s32 arg1) {
    func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 0, 0, 0x300, &D_802D3A30);
}

extern s32 func_80035690();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

void func_801CC58C(s32 arg0, s32 arg1) {
    func_80035690((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, 0x300, arg0);
}

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

void func_801CC600(s32 arg0, s32 arg1) {
    func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 1, 0, 0x300, &D_802D3A30);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CC908.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCAB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCBCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCD74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCDE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CCEAC.s")

extern s32 osSendMesg();
extern s32 D_802D3E00;
extern u8 D_802D3E0E;
extern u8 D_802D3FC8;

u8 func_801CD038(s32 arg0, s32 arg1) {
    D_802D3E00 = arg0;
    osSendMesg(&D_802D3FC8, (arg1 << 8) + 4, 1);
    return D_802D3E0E;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CD078.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CD100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CD174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_200C0/func_801CD1F0.s")

s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32);s32 func_801CCD74(s32 *);
s32 func_801CD3BC(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 sp3C;

    if (func_801CCD74(&sp3C) != 0) {
        return func_801BE540(arg0, arg1, sp3C, arg2, arg3, -1800.0f, 0xFF, 0, 0, 0xFF, 1.0f);
    }
    return 0;
}
