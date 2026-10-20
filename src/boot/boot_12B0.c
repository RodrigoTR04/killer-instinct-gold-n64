#include "common.h"

extern void osCreatePiManager(s32, void *, void *, s32);
extern void osCreateMesgQueue(void *, void *, s32);
extern void func_80001EF4(void *, void *);
extern void osInvalDCache(s32, s32);
extern void osPiStartDma(void *, s32, s32, s32, s32, s32, void *);
extern s32 osRecvMesg(void *, void *, s32);
extern s32 D_8000BE30, D_8000BEF8, D_8000BF00, D_8000BF18;
extern s32 D_8000BF48, D_8000BF50, D_8000BF68;

void func_800006B0(void) {
    osCreatePiManager(0x96, &D_8000BF00, &D_8000BE30, 0x32);
    osCreateMesgQueue(&D_8000BF18, &D_8000BEF8, 1);
}

void func_800006FC(void) {
    osCreateMesgQueue(&D_8000BF50, &D_8000BF68, 4);
    func_80001EF4(&D_8000BF48, &D_8000BF50);
}

void boot_dma(s32 arg0, s32 arg1, s32 arg2) {
    u8 sp2C[0x14];
    s32 sp28;

    osInvalDCache(arg1, arg2);
    osPiStartDma(sp2C, 0, 0, arg0, arg1, arg2, &D_8000BF18);
    osRecvMesg(&D_8000BF18, &sp28, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_12B0/boot_dma_chunked.s")
