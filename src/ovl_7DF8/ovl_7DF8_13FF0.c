#include "common.h"

extern void func_801CC784(void);
extern void func_801CC878(void);
extern void func_801BEFFC(void);

void func_801BFB10(void) {
    func_801CC784();
    func_801CC878();
    func_801BEFFC();
}

typedef struct { s32 x, y; } T023PairB40;
extern void func_801ADAD4(s32);
extern T023PairB40 D_80128300, D_802D37D8, D_802D37E0, D_802D37F0;
extern s32 D_80295700, D_802956FC, D_802956F8;
extern s32 D_802D37D0, D_802D37F8, D_802D3820, D_802D3824;
extern u8 D_802D37EA[];
void func_801BFB40(u8 arg0) {
    D_802D37D0 = -1;
    D_802D37F0.x = D_80128300.x;
    D_802D37F0.y = D_80128300.y;
    D_802D37EA[0] = D_802D37EA[1] = 0;
    D_802D37D8.x = D_802D37D8.y = 40;
    D_802D37E0.x = D_802D37E0.y = 32;
    D_802D37F8 = 0;
    D_802D3820 = 2560;
    D_802D3824 = 2560;
    if (arg0) func_801ADAD4(42);
    D_802956F8 = D_802956FC = D_80295700 = 0;
}

extern void func_801ADC64(s32);
extern void func_801AF5D4(s32);
extern void func_801AF5EC(s32);
extern s32 D_802D37D0;
extern s32 D_802D37F8;

void func_801BFC08(s32 arg0) {
    if (arg0 == 0) D_802D37F8 += 0x280;
    else D_802D37F8 = arg0 + 0xA0;
    if (D_802D37F8 != 0xA0) {
        if (++D_802D37D0 >= 14) {
            func_801ADC64(0);
            func_801AF5EC(0xFFFF);
            func_801AF5D4(16);
        }
    }
}

extern s32 D_802D37D0, D_802D37F8;

void func_801BFC8C(void) {
    if (D_802D37D0-- <= 0) D_802D37D0 = 13;
    D_802D37F8 = 160;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801BFCBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C0610.s")

extern void func_801BF190(s32, s32, s32);
extern void func_801BFC08(s32);
extern void func_801C0610(s32, u32);
extern s8 D_801CD454;
extern s32 D_802CA068, D_802D37D0;
extern s32 D_802D37F8;

void func_801C0784(s32 arg0, u32 arg1) {
    if ((u32)D_802D37F8 < arg1) func_801BFC08(arg1);
    if (arg1 + 0x280 < (u32)D_802D37F8) D_802D37F8 = arg1 + 0x280;
    func_801C0610(arg0, arg1);
    func_801BF190(arg0, D_802CA068, D_802D37D0);
    D_801CD454 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C0800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C08F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C11F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1434.s")

extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u8 D_80128310[][11], D_80128328[][11];
void func_801C1704(u8 player) {
    s32 i;


    D_80128308[player] = 0;
    D_8012830A[player] = 0;
    for (i = 0; i < 11; i++) {
        D_80128310[player][i] = 0;
        D_80128328[player][i] = 0;
    }
    D_80127C30[player] = 100;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C17D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1C34.s")

void func_801C2110(f32 t, f32 *coef, f32 *position, f32 *velocity) {
    f32 two = 2.0f;
    f32 three = 3.0f;
    f32 t2;
    f32 t3;

    t2 = t * t;
    t3 = t2 * t;
    position[0] = coef[0] * t3 + coef[1] * t2 + coef[2] * t + coef[3];
    position[1] = coef[4] * t3 + coef[5] * t2 + coef[6] * t + coef[7];
    position[2] = coef[8] * t3 + coef[9] * t2 + coef[10] * t + coef[11];
    velocity[0] = three * coef[0] * t2 + two * coef[1] * t + coef[2];
    velocity[1] = three * coef[4] * t2 + two * coef[5] * t + coef[6];
    velocity[2] = three * coef[8] * t2 + two * coef[9] * t + coef[10];
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C224C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C23C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2ADC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2D34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C317C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C3524.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C3580.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C35AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C35D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C3758.s")
