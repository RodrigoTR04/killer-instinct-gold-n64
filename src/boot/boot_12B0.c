#include "boot.h"

extern void osCreatePiManager(s32, void *, void *, s32);
extern void osPiStartDma(void *, s32, s32, s32, s32, s32, void *);
extern s32 D_8000BEF8, D_8000BF00, boot_pi_completion_queue;
extern s32 D_8000BF48, boot_dma_retrace_queue, D_8000BF68;

void boot_init_pi(void) {
    osCreatePiManager(0x96, &D_8000BF00, &D_8000BE30, 0x32);
    osCreateMesgQueue(&boot_pi_completion_queue, &D_8000BEF8, 1);
}

void boot_init_dma_events(void) {
    osCreateMesgQueue(&boot_dma_retrace_queue, &D_8000BF68, 4);
    boot_subscribe_retrace(&D_8000BF48, &boot_dma_retrace_queue);
}

/* Blocking PI transfer; the chunked variant waits for retrace between chunks. */
void boot_dma(s32 rom, s32 dest, s32 length) {
    BootDmaMessage io_message;
    s32 completion_message;

    osInvalDCache(dest, length);
    osPiStartDma(&io_message, 0, 0, rom, dest, length, &boot_pi_completion_queue);
    osRecvMesg(&boot_pi_completion_queue, &completion_message, 1);
}

void boot_dma_chunked(s32 rom, s32 dest, u32 length) {
    BootDmaMessage io;
    s16 *completion;
    s16 *event = 0;
    u32 done = 0;
    u32 chunk;
    osInvalDCache(dest, length);
    while (osRecvMesg(&boot_dma_retrace_queue, &event, 0) == 0) {}
    while (done < length) {
        osRecvMesg(&boot_dma_retrace_queue, &event, 1);
        if (*event != 1) {
            continue;
        }
        chunk = length - done < 0x14000 ? length - done : 0x14000;
        osPiStartDma(&io, 0, 0, rom, dest, chunk, &boot_pi_completion_queue);
        osRecvMesg(&boot_pi_completion_queue, &completion, 1);
        done += chunk;
        rom += chunk;
        dest += chunk;
    }
}
