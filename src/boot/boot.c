#include "boot.h"

extern void osInitialize(void);
extern void osSetThreadPri(void *, s32);
extern void osInvalICache(u32, u32);
extern u8 D_800076D0[], D_80007C80[];
extern s32 D_8000030C;

/* Entry initializes libultra, then starts the idle/bootstrap thread. */
void boot_start(void) {
    osInitialize();
    osCreateThread(&D_800076D0, 1, boot_idle_thread, 0, &D_80007C80, 0xA);
    osStartThread(&D_800076D0);
}

void boot_idle_thread(s32 thread_arg) {
    boot_init_pi();
    osCreateThread(&D_80007C80, 3, boot_load_main, thread_arg, &D_8000BE30, 0xA);
    osStartThread(&D_80007C80);
    osSetThreadPri(&D_800076D0, 0);
    while (1) {}
}

/* Stage compressed main above its destination, inflate, and enter it. */
void boot_load_main(s32 unused) {
    if (D_8000030C == 0) {
        bzero((void *)0x8000F960, 0x3F06A0);
    } else {
        bzero((void *)0x802D4000, 0x12C000);
    }
    osInvalICache(0x8000F960, 0x3F06A0);
    osInvalDCache(0x8000F960, 0x3F06A0);
    boot_dma(boot_overlay_table[0].rom_start, 0x802D4000, boot_overlay_table[0].rom_end - boot_overlay_table[0].rom_start);
    boot_inflate((u8 *)0x802D4000, (u8 *)0x8000F960, (huft *)0x803A2000);
    ((void (*)(void))0x8000F960)();
}

void boot_decode_backrefs(u8 *src, u8 *dst, s32 length) {
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
