/* T-045 DRAFT: 3 standalone/full-TU words remain; 144/144 bytes. Initial ra-save/address-load scheduling only; was 18 words with the integer DMA prototype. Uses the shared signed boot_dma declaration. */
extern void boot_dma(s32, s32, s32);
extern void boot_inflate(void *, void *, void *);
extern u8 D_1F4290, D_1F6700, D_1F7780;
void func_80014250(void) {
    boot_dma((s32)&D_1F4290,0x802D4000,(u32)&D_1F6700-(s32)&D_1F4290);
    boot_inflate((void*)0x802D4000,(void*)0x803A4200,(void*)0x803A2000);
    boot_dma((s32)&D_1F6700,0x802D4000,(u32)&D_1F7780-(s32)&D_1F6700);
    boot_inflate((void*)0x802D4000,(void*)0x803AC908,(void*)0x803A2000);
}
