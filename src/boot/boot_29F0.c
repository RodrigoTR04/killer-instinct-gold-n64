#include "common.h"

extern void func_80001F2C(s32);
void func_800022C0(void);
extern void osCreateMesgQueue(void *, void *, s32);
extern void osCreateThread(void *, s32, void (*)(s32), s32, void *, s32);
extern void osCreateViManager(s32);
extern void osSetEventMesg(s32, void *, s32);
extern void osStartThread(void *);
extern void osViSetEvent(void *, s32, u8);
extern void osSpTaskLoad(u8 *), osSpTaskStartGo(u8 *);
extern s32 osViGetCurrentFramebuffer(void), osViGetNextFramebuffer(void);
extern s32 osRecvMesg(void *, void *, s32);
/* This boot copy passes the byte count as an o32 64-bit argument (a2/a3). */
extern s32 osDpSetNextBuffer(s32, u64);
extern u8 *D_80006678;
extern s32 D_8000666C, D_80006670, D_80006674;
extern s32 D_8000C3A0, D_8000CF50, D_8000CF68, D_8000CF80;
extern s32 D_8000CF98, D_8000CFA8, D_8000CFB8, D_8000CFD0;
extern u8 D_8000CFCC, D_8000D18C;
extern u8 D_8000D194, D_8000D195, D_8000D196;
extern u8 D_8000D197, D_8000D198, D_8000D199;
extern s32 D_8000D180[];

void func_80001DF0(void) {
    D_8000CFCC = 1;
    osCreateViManager(0xFE);
    osCreateMesgQueue(&D_8000CF50, &D_8000CF98, 3);
    osCreateMesgQueue(&D_8000CF68, &D_8000CFA8, 3);
    osCreateMesgQueue(&D_8000CF80, &D_8000CFB8, 5);
    osSetEventMesg(9, &D_8000CF80, D_80006670);
    osSetEventMesg(4, &D_8000CF80, D_80006674);
    osViSetEvent(&D_8000CF80, D_8000666C, D_8000CFCC);
    D_8000D18C = 0;
    osCreateThread(&D_8000CFD0, 0x14, func_80001F2C, 0, &D_8000C3A0, 0xD);
    osStartThread(&D_8000CFD0);
}

void func_80001EF4(s32 arg0, s32 arg1) {
    if ((s32) D_8000D18C < 3) {
        D_8000D180[D_8000D18C++] = arg1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_29F0/func_80001F2C.s")

void func_800022C0(void) {
    if (D_8000D195 == 4) {
        osSpTaskLoad(D_80006678 + 0x18);
        osSpTaskStartGo(D_80006678 + 0x18);
        D_8000D195 = 1;
        D_8000D199 += 1;
        return;
    }
    if (D_8000D195 == 2) {
        osSpTaskLoad(D_80006678 + 0x18);
        osSpTaskStartGo(D_80006678 + 0x18);
        D_8000D197 = 1;
        D_8000D198 = 0;
        D_8000D199 = 0;
        D_8000D195 = 1;
        return;
    }
    if ((D_8000D195 == 5) && (D_80006678 != 0)) {
        if ((osViGetCurrentFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10))) && (osViGetNextFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10)))) {
            osSpTaskLoad(D_80006678 + 0x18);
            osSpTaskStartGo(D_80006678 + 0x18);
            D_8000D197 = 1;
            D_8000D198 = 0;
            D_8000D199 = 0;
            D_8000D195 = 1;
            return;
        }
        D_8000D195 = 2;
    }
}

void func_80002420(void) {
    if ((D_8000D195 == 0) || (D_8000D195 == 5)) {
        if (D_8000D196 == 2) {
            if ((osViGetCurrentFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10))) && (osViGetNextFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10))) && (osDpSetNextBuffer(*(s32 *)((u8 *)(D_80006678) + (0)), (u32)*(s32 *)((u8 *)(D_80006678) + (4))) != -1)) {
                D_8000D196 = 1;
            }
        } else if ((D_8000D195 == 0) && (osRecvMesg(&D_8000CF50, &D_80006678, 0) == 0)) {
            D_8000D195 = 5;
            if (*(s32 *)((u8 *)(D_80006678) + (0)) != 0) {
                if ((osViGetCurrentFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10))) && (osViGetNextFramebuffer() != *(s32 *)((u8 *)(D_80006678) + (0x10)))) {
                    if (osDpSetNextBuffer(*(s32 *)((u8 *)(D_80006678) + (0)), (u32)*(s32 *)((u8 *)(D_80006678) + (4))) != -1) {
                        D_8000D196 = 1;
                    }
                } else {
                    D_8000D196 = 2;
                }
            } else if (D_8000D194 == 0) {
                func_800022C0();
            }
        }
    }
}
