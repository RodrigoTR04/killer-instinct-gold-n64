#include "common.h"

extern void osInitialize(void);
extern void osCreateThread(void *, s32, void (*)(s32), s32, void *, s32);
extern void osStartThread(void *);
extern void osSetThreadPri(void *, s32);
extern void bzero(u32, u32);
extern void osInvalDCache(u32, u32);
extern void osInvalICache(u32, u32);
extern void boot_dma(s32, s32, s32);
extern s32 boot_inflate(u32, u32, u32);
extern void func_800006B0(void);
void func_800004AC(s32);
void func_80000520(s32);
extern u8 D_800076D0[], D_80007C80[], D_8000BE30[];
extern s32 D_8000030C;
extern s32 D_800071F0[];

void func_80000450(void) {
    osInitialize();
    osCreateThread(&D_800076D0, 1, func_800004AC, 0, &D_80007C80, 0xA);
    osStartThread(&D_800076D0);
}

void func_800004AC(s32 arg0) {
    func_800006B0();
    osCreateThread(&D_80007C80, 3, func_80000520, arg0, &D_8000BE30, 0xA);
    osStartThread(&D_80007C80);
    osSetThreadPri(&D_800076D0, 0);
    while (1) {}
}

void func_80000520(s32 arg0) {
    if (D_8000030C == 0) {
        bzero(0x8000F960, 0x3F06A0);
    } else {
        bzero(0x802D4000, 0x12C000);
    }
    osInvalICache(0x8000F960, 0x3F06A0);
    osInvalDCache(0x8000F960, 0x3F06A0);
    boot_dma(D_800071F0[0], 0x802D4000, D_800071F0[1] - D_800071F0[0]);
    boot_inflate(0x802D4000, 0x8000F960, 0x803A2000);
    ((void (*)(void))0x8000F960)();
}

void func_800005EC(u8 *src, u8 *dst, s32 length) {
    s32 out = 0;
    s32 in = 0;
    s32 n, offset, count;
    s32 control;
    while (in < length) {
        control = src[in];

        if (control) {
            n = (control & 7) + 1;
            offset = (src[in + 1] << 5) + (control >> 3) + 1;
            in++;
            for (count = 0; count < n; count++) {
                dst[out] = dst[out - offset];
                out++;
            }
        } else {
            dst[out] = src[in + 1];
            in++;
            out++;
        }
        in++;
    }
}
