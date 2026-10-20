/* DRAFT. Remaining diff: 3 linked words with the TU's boot_dma(void *, void *, s32) prototype; 84/84 bytes. T-040: this exact C matches standalone (0 words) when boot_dma is prototyped boot_dma(u32, u32, u32) as below, but main_2FF0.c declares it with pointer args for already-matched callers, so it can't go into src without changing that shared prototype. */
extern u8 D_54E7D0[], D_551E60[];
extern void boot_dma(u32, u32, u32);
extern void boot_inflate(void *, void *, void *);

void func_80013C84(void) {
    boot_dma((u32)D_54E7D0, 0x802D4000, (u32)D_551E60 - (u32)D_54E7D0);
    boot_inflate((void *)0x802D4000, (void *)0x803A4200, (void *)0x803A2000);
}
