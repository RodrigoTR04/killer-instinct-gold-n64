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

void boot_dma_chunked(s32 rom, s32 dest, u32 length) {
    u8 io[0x14];
    s16 *completion;
    s16 *event = 0;
    u32 done = 0;
    u32 chunk;
    osInvalDCache(dest, length);
    while (osRecvMesg(&D_8000BF50, &event, 0) == 0) {}
    while (done < length) {
        osRecvMesg(&D_8000BF50, &event, 1);
        if (*event != 1) {
            continue;
        }
        chunk = length - done < 0x14000 ? length - done : 0x14000;
        osPiStartDma(io, 0, 0, rom, dest, chunk, &D_8000BF18);
        osRecvMesg(&D_8000BF18, &completion, 1);
        done += chunk;
        rom += chunk;
        dest += chunk;
    }
}
