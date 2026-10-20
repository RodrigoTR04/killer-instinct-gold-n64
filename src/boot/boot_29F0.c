#include "common.h"

extern void func_80001F2C(s32);
void func_800022C0(void);
void func_80002420(void);
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
extern u8 *D_80006678, *D_8000667C;
extern void osSpTaskYield(void), osViSwapBuffer(s32);
extern u32 osSpTaskYielded(u8 *);
extern s32 osSendMesg(s32, void *, s32);
extern s32 D_8000D190;
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

void func_80001F2C(s32 arg0) {
    s32 sp74;
    u8 *sp70;
    s16 sp50[16];
    s32 *var_s1;
    s32 var_s0;

    D_8000D194 = 0;
    D_8000D195 = 0;
    D_8000D196 = 0;
    D_8000D198 = 1;
    sp70 = (u8 *)&sp74;
    D_8000D197 = 0;
    sp50[0] = 1;
    while(1) {
        osRecvMesg(&D_8000CF80, &sp70, 1);
        switch (*sp70) {
        case 0:
            if (D_8000D194 == 0) {
                if (osRecvMesg(&D_8000CF68, &D_8000667C, 0) == 0) {
                    if (D_8000D197 != 0) {
                        osSpTaskYield();
                        D_8000D195 = 3;
                    } else {
                        osSpTaskLoad(D_8000667C + 0x18);
                        osSpTaskStartGo(D_8000667C + 0x18);
                        D_8000D194 = 1;
                        if (D_8000D198 == 1) {
                            func_80002420();
                        }
                    }
                } else if ((D_8000D195 == 0) || (D_8000D196 == 2)) {
                    func_80002420();
                } else {
                    func_800022C0();
                }
            }
            var_s0 = 0, var_s1 = D_8000D180;
            if ((s32) D_8000D18C > 0) {
                do {
                    osSendMesg(*var_s1, sp50, 0);
                    var_s0 += 1;
                    var_s1 += 1;
                } while (var_s0 < (s32) D_8000D18C);
            }
            break;
        case 2:
            if (D_8000D195 == 3) {
                if (osSpTaskYielded(D_80006678 + 0x18) == 1) {
                    osSpTaskLoad(D_8000667C + 0x18);
                    osSpTaskStartGo(D_8000667C + 0x18);
                    D_8000D194 = 1;
                    D_8000D195 = 4;
                } else {
                    D_8000D195 = 1;
                    osSpTaskLoad(D_8000667C + 0x18);
                    osSpTaskStartGo(D_8000667C + 0x18);
                    D_8000D194 = 1;
                    D_8000D197 = 0;
                }
            } else if (D_8000D194 != 0) {
                osSendMesg(*(s32 *)((u8 *)(D_8000667C) + (0x58)), *(s16 **)((u8 *)(D_8000667C) + (0x5C)), 1);
                D_8000D194 = 0;
                if (D_8000D196 == 0) {
                    func_800022C0();
                }
            } else {
                D_8000D197 = 0;
                if (D_8000D198 == 1) {
                    osViSwapBuffer(D_8000D190 = *(s32 *)(D_80006678 + 0x10));
                    D_8000D195 = 0;
                    osSendMesg(*(s32 *)((u8 *)(D_80006678) + (0x58)), *(s16 **)((u8 *)(D_80006678) + (0x5C)), 1);
                }
            }
            break;
        case 1:
            if (D_8000D196 == 1) {
                D_8000D196 = 0;
                if (D_8000D194 == 0) {
                    func_800022C0();
                }
                continue;
            }
            D_8000D198 = 1;
            if (D_8000D197 != 0) {
                continue;
            }
            osViSwapBuffer(D_8000D190 = *(s32 *)(D_80006678 + 0x10));
            D_8000D195 = 0;
            osSendMesg(*(s32 *)((u8 *)(D_80006678) + (0x58)), *(s16 **)((u8 *)(D_80006678) + (0x5C)), 1);
            break;
        }
        continue;
    }
}

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
