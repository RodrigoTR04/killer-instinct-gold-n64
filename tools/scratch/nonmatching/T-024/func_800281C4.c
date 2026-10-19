/* DRAFT. Remaining diff: 11 differing words; 108/108 bytes */
extern u8 D_A69A20[],D_A69A40[],D_A69A70[];
extern s32 D_803A5200,D_803A5204;
extern s16 D_80061CD8,D_80061CDA;
s32 func_800281C4(s32 index) { u8 *start,*end; if (index == 0) { start=D_A69A20; end=D_A69A40; } else { start=D_A69A40; end=D_A69A70; } boot_dma(start,(void *)0x803A5200,end-start); D_80061CD8=D_803A5200; D_80061CDA=D_803A5204; }
