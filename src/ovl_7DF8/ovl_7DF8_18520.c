#include "common.h"

extern u8 D_8004EA9B[], D_8004EA9D[], D_802D3959, D_802D395A;

void func_801C4040(u8 arg0) {
    if (arg0 != 0) {
        D_802D3959 = D_8004EA9B[arg0];
        D_802D395A = D_8004EA9D[arg0];
    }
}

extern void func_8001C534(void), func_8002B9B4(void);
extern void func_8002F6F4();
extern void func_801ADAD4(s32);
extern void func_801C47E0();
extern void func_801C48E4();
extern u8 D_8004A278[], D_800F4070[];
extern s32 D_80066C40, D_800698C4;
extern f32 D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0;
extern s8 D_801CD454;
extern u8 D_802C8724;
const u8 D_802937E0[] = "SUPREME";
const u8 D_802937E8[] = "  ULTRA";
const u8 D_802937F0[] = "AWESOME";
extern s32 D_802956F8, D_802956FC, D_80295700;
extern void *D_802D3950;
extern u8 D_802D3954, D_802D3958;
extern u16 D_802D3956;
extern u8 D_802D3959, D_802D395A;

void func_801C407C(u8 arg0, u8 arg1) {
    func_801C47E0((D_802D3959 + 0x80) & 0xFF, D_802D395A, &D_800F4070, D_802D3959);
    func_801C48E4(0, D_802D3959, 1);
    D_802956F8 = D_802956FC = D_80295700 = 0;
    D_801CD454 = 0;
    if (D_802D3959 == 8) {
        D_802C8724 = 1;
    } else {
        D_802C8724 = 0;
    }
    D_800698C4 = 0;
    D_800695D8 = 0.0f;
    D_800695DC = 0.0f;
    D_800695E0 = 0.0f;
    D_800695CC = 0.0f;
    D_800695D0 = 0.0f;
    D_800695D4 = 0.0f;
    func_8002B9B4();
    func_8002F6F4(D_80066C40, 0x15D, &D_8004A278);
    func_801ADAD4(0x2A);
    switch (arg0) {
    case 1:
    case 3:
        D_802D3950 = &D_802937E0;
        D_802D3956 = 0x17C;
        break;
    case 2:
        D_802D3950 = &D_802937E8;
        D_802D3956 = 0;
        break;
    default:
    case 4:
    case 5:
        D_802D3950 = &D_802937F0;
        D_802D3956 = 0x17B;
        break;
    }
    if (arg1 != 0) {
        D_802D3954 = 1;
    } else {
        D_802D3954 = 0;
    }
    D_802D3958 = 1;
    func_8001C534();
}

void func_801C4238(void) {}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18520/func_801C4240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_18520/func_801C4780.s")
