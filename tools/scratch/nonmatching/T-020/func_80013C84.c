/* DRAFT T-020: Same size and operations; three address/prologue instructions scheduled differently. */
extern u8 D_54E7D0, D_551E60;
extern void boot_dma(void *, void *, s32);

void func_80013C84(void) {
    s32 end;
    end = (s32)&D_551E60;
    boot_dma(&D_54E7D0, (void *)0x802D4000, end - (s32)&D_54E7D0);
    boot_inflate((void *)0x802D4000, (void *)0x803A4200, (void *)0x803A2000);
}
