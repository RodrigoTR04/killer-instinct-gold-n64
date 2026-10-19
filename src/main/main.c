#include "common.h"

extern u8 D_8004A230[], D_80127C30[], D_80128350[], D_8006F1C0[];
extern void *D_8004A294;
extern u8 D_8004A298[], D_8004A2D0[], D_8004EA9C[], D_8004EA9E[];
extern s32 D_8004A414, D_80127D80;
extern void bzero(void *, s32);
extern void func_8000FA50(void), func_80001DF0(void), func_800006FC(void);
extern void func_8002A4F0(void), func_80027DA0(void), func_8002B500(void), func_8000FA80(void);
extern void osViBlack(s32);
extern void func_80001EF4(void *, void *);
extern void func_8002FAC0(s32, s32);
extern void func_8002A900(s32);

void func_8000F960(void) {
    bzero(D_8004A230, D_80127C30 - D_8004A230);
    bzero(D_80128350, 0x4A380);
    D_8004A294 = D_8006F1C0;
    func_8000FA50();
    func_80001DF0();
    osViBlack(1);
    func_80001EF4(D_8004A2D0, D_8004A298);
    func_800006FC();
    func_8002A4F0();
    func_8002FAC0(0, 0x4E20);
    func_80027DA0();
    D_8004EA9C[0] = 0;
    D_8004EA9C[1] = 0;
    D_8004A414 = 0;
    D_8004EA9E[0] = 0;
    D_8004EA9E[1] = 0;
    D_80127D80 = 0;
    func_8002B500();
    for (;;) {
        func_8000FA80();
        func_8002A900(0x11);
    }
}

extern u8 D_8004A298[], D_8004A2B0[];
extern void osCreateMesgQueue(void *, void *, s32);

void func_8000FA50(void) {
    osCreateMesgQueue(D_8004A298, D_8004A2B0, 8);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8000FA80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001178C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80011FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800121C8.s")

void func_800122F8(s16 *arg0) {
    s32 i;
    for (i = 0; i < 0x12BFF; i++) {
        arg0[i] = 0;
    }
}

extern void boot_inflate(void *, void *, void *);

void func_80012338(void *arg0, void *arg1, s32 arg2) {
    boot_inflate(arg0, arg1, (void *)0x803A2000);
}

extern void func_80012390(void);
extern void func_80020E98(s32, s32, s32);

void func_80012360(void) {
    func_80012390();
    func_80020E98(1, 13, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_80012390.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001256C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_800126D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main/func_8001272C.s")
