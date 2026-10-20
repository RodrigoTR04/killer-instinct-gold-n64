/* DRAFT. Remaining diff: 4 words (T-040; was 11): the two branch arms emit addiu v0 before addiu a0 (original: a0 first); 108/108 bytes. D_803A5200/4 are read as constant-address words. */
extern u8 D_A69A20[], D_A69A40[], D_A69A70[];
extern s16 D_80061CD8, D_80061CDA;
extern void boot_dma(void *, void *, s32);
void func_800281C4(s32 index) {
    u8 *start, *end;
    if (index == 0) {
        start = D_A69A20; end = D_A69A40;
    } else {
        start = D_A69A40; end = D_A69A70;
    }
    boot_dma(start, (void *)0x803A5200, end - start);
    D_80061CD8 = ((s32 *)0x803A5200)[0];
    D_80061CDA = ((s32 *)0x803A5200)[1];
}
