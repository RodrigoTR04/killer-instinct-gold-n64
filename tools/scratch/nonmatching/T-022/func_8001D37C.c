/* T-022 DRAFT: 38 instruction words differ; compiled 180 bytes, original 176 bytes */

typedef struct { u8 *start; u8 pad[28]; } T022DmaEntry;



extern T022DmaEntry D_80045E68[];
extern u8 D_8004CE90[], D_8004CEB0[], D_8004EA9F;
void func_8001D37C(u8 arg0, u8 arg1) {
    s32 index = arg0 & 0xFF;
    s32 a, b;
    if (D_8004EA9E[0] == 9) a = 0; else a = D_8004EA9E[0];
    boot_dma(D_80045E68[index].start + (a << 5), D_8004CE90, 0x20);
    if (D_8004EA9F == 9) b = 0; else b = D_8004EA9F;
    boot_dma(D_80045E68[arg1].start + (b << 5), D_8004CEB0, 0x20);
}
