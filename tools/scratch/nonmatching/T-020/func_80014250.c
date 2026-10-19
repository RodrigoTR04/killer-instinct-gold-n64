/* DRAFT T-020: Address-load scheduling differs; integer-address variants also introduce stack/register differences. */
extern u8 D_1F4290, D_1F6700, D_1F7780;

void func_80014250(void) {
    s32 end;
    end = (s32)&D_1F6700;
    boot_dma(&D_1F4290, (void *)0x802D4000, end - (s32)&D_1F4290);
    boot_inflate((void *)0x802D4000, (void *)0x803A4200, (void *)0x803A2000);
    end = (s32)&D_1F7780;
    boot_dma(&D_1F6700, (void *)0x802D4000, end - (s32)&D_1F6700);
    boot_inflate((void *)0x802D4000, (void *)0x803AC908, (void *)0x803A2000);
}
