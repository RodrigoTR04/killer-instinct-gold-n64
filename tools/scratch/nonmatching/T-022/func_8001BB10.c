/* T-022 DRAFT: 3 instruction words differ; compiled 84 bytes, original 84 bytes */


extern u8 *D_8004ACD8;
extern u8 D_803A4200[], D_A68A20, D_A69A20;
void func_8001BB10(void) {
    s32 size = &D_A69A20 - &D_A68A20;
    boot_dma(&D_A68A20, D_8004ACD8, size);
    if (D_8004AA28 == 0) D_8004ACD8 = D_803A4200;
}
