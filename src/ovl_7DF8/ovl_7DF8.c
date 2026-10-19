#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ABB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AC95C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACAD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACB1C.s")

extern s32 func_801AF67C(int);                               /* extern */
extern int func_801AF68C(s32, s32);                          /* extern */
extern int func_801BBC84(void);                                  /* extern */
extern int func_801C3E40(s32);                               /* extern */
extern u8 D_801CD454;

void func_801ACE04(s32 arg0, s32 arg1) {
    if (D_801CD454 != 0) {
        func_801BBC84();
    }
    func_801AF68C(arg0, arg1);
    if (func_801AF67C(4) != 0) {
        func_801C3E40(arg0);
    }
}

typedef void (*Callback)();
extern int func_801ACB1C(Callback, Callback, Callback);                     /* extern */
extern s32 func_801AF67C(int);                               /* extern */
extern void func_801ACE04();
extern void func_801AD568();
extern void func_801B47A4();
extern void func_801BD3FC();

void func_801ACE5C(void) {
    if (func_801AF67C(0x20) != 0) {
        func_801ACB1C(func_801AD568, func_801ACE04, func_801B47A4);
        return;
    }
    func_801ACB1C(func_801AD568, func_801ACE04, func_801BD3FC);
}

extern void (*D_8004AA30)(int, int, int, int, float, float, float);
extern int D_800695CC, D_800695D0;
extern float D_800695D4, D_800695D8, D_800695DC;
void func_801ACEC0(int a0, int a1, int a2) {
    D_8004AA30(a0, a1, D_800695CC, D_800695D0,
        D_800695D4, D_800695D8, D_800695DC);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACF1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACF50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ACF84.s")

extern int func_801ACB1C(Callback, Callback, Callback);                     /* extern */
extern void func_801ACEC0();
extern void func_801ACF84();
extern void func_801AD568();
extern void func_801C71FC();
extern u8 D_802D39BA;

void func_801ACFC8(void) {
    if (D_802D39BA & 1) {
        func_801ACB1C(func_801ACEC0, func_801ACF84, func_801C71FC);
        return;
    }
    func_801ACB1C(func_801AD568, func_801ACF84, func_801C71FC);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD030.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD098.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD114.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD388.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD3BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD568.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD794.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801AD7D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADA04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADAD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADB14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADBB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADC64.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADCFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8/func_801ADDD8.s")

extern unsigned char D_8004EA9C[], D_8004EA9E[];
extern void func_801ADC64(int);
void func_801ADE48(unsigned char a, unsigned char b, unsigned char c, unsigned char d) {
    D_8004EA9C[0] = a;
    D_8004EA9C[1] = b;
    D_8004EA9E[0] = c;
    D_8004EA9E[1] = d;
    func_801ADC64(10);
}

