#ifndef BOOT_H
#define BOOT_H
#include "common.h"

/* ROM bounds are exclusive; entry zero is main, followed by 26 payloads. */
typedef struct BootRomRange {
    s32 rom_start;
    s32 rom_end;
} BootRomRange;
extern BootRomRange boot_overlay_table[27];

/* PI DMA message layout used by osPiStartDma (20 bytes on o32). */
typedef struct BootDmaMessage {
    u16 type;
    u8 priority, status;
    void *return_queue;
    void *dram_address;
    u32 rom_address;
    u32 size;
} BootDmaMessage;

/* gzip 1.2.4 decode entry: operation/extra bits, consumed bits, value/link. */
typedef struct huft {
    u8 e, b;
    union { u16 n; struct huft *t; } v;
} huft;
extern u8 *inflate_input, *inflate_output;
extern s32 inflate_inptr;
extern u32 wp, bb, bk, hufts;
extern huft *inflate_huft_pool;
extern u8 border[], cplext[], cpdext[];
extern u16 cplens[], cpdist[], mask_bits[];
extern s32 lbits, dbits;

void boot_start(void);
void boot_idle_thread(s32);
void boot_load_main(s32);
void boot_decode_backrefs(u8 *source, u8 *destination, s32 length);
void boot_init_pi(void);
void boot_init_dma_events(void);
void boot_dma(s32 rom, s32 destination, s32 length);
void boot_dma_chunked(s32 rom, s32 destination, u32 length);
s32 boot_inflate(u8 *source, u8 *destination, huft *scratch);
s32 huft_build(u32 *, u32, u32, u16 *, u8 *, huft **, s32 *);
s32 inflate_codes(huft *, huft *, s32, s32);
s32 inflate_stored(void);
s32 inflate_fixed(void);
s32 inflate_dynamic(void);
s32 inflate_block(s32 *);
s32 inflate(void);
void boot_init_scheduler(void);
/* The first argument is unused, but retained for the original ABI. */
void boot_subscribe_retrace(void *, void *);
void boot_scheduler_thread(s32);
void boot_start_graphics_task(void);
void boot_schedule_graphics(void);

/* Only fields accessed by boot are interpreted. Embedded OSTask is 0x40 B. */
typedef struct BootTask {
    s32 dp_buffer;
    s32 dp_size;
    u8 unknown_08[8];
    s32 framebuffer;
    u8 unknown_14[4];
    u8 task[0x40];
    s32 completion_queue;
    s16 *completion_message;
} BootTask;
extern BootTask *boot_graphics_task, *boot_audio_task;

/* PI manager command buffer, also used as the main-loader stack top. */
extern u8 D_8000BE30[];

/* These loose SDK declarations preserve the matched boot callers' ABI. */
extern void bzero(void *, s32);
extern void osInvalDCache(s32, s32);
extern void osCreateThread(void *, s32, void (*)(s32), s32, void *, s32);
extern void osStartThread(void *);
extern void osCreateMesgQueue(void *, void *, s32);
extern s32 osRecvMesg(void *, void *, s32);
#endif
