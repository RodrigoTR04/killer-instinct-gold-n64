/* DRAFT. Remaining diff: 36 differing words at equal size; saved-register allocation. */
extern void osInvalDCache(s32, u32);
extern void osPiStartDma(void *, s32, s32, s32, s32, u32, void *);
extern s32 osRecvMesg(void *, void *, s32);
extern s32 D_8000BF18, D_8000BF50;

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
        if (*event == 1) {
            chunk = length - done < 0x14000 ? length - done : 0x14000;
            osPiStartDma(io, 0, 0, rom, dest, chunk, &D_8000BF18);
            osRecvMesg(&D_8000BF18, &completion, 1);
            done += chunk;
            rom += chunk;
            dest += chunk;
        }
    }
}
