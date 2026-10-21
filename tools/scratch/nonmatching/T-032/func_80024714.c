/* T-102 DRAFT: 69 differing words, 712/712 bytes; address and store scheduling remain. */
extern u8 D_8004AC88;
typedef struct { u8 pad0[3144]; u8 *slotC48; u8 *slotC4C; u8 padC50[16]; u8 *slotC60; u8 *slotC64; u8 padC68[16]; u8 *slotC78; u8 *slotC7C; u8 padC80[16]; u8 *slotC90; u8 *slotC94; u8 padC98[928]; u8 *slot1038; u8 *slot103C; u8 pad1040[352]; u8 *slot11A0; u8 *slot11A4; } T032Resource714;
extern u8 D_1EB6D0[],D_1F3200[],D_2C2280[],D_2CF0A0[],D_469660[],D_470390[],D_53CC40[],D_543D10[],D_8004D278[],D_8004EA9C[],D_8004F396[];
extern u8 D_8004F395;
extern void boot_dma(s32,s32,s32),boot_dma_chunked(void *,void *,s32),func_800245B4(s32,void *,s32),func_80030220(void *,void *,s32);
void func_80024714(s32 arg0) {
    s32 temp_v0;
    T032Resource714 *temp_v0_2;
    T032Resource714 *temp_v0_3;
    u8 *var_s0;
    T032Resource714 *var_v0;

    if (arg0 == 0) {
        var_s0 = (void *)0x802A9F90;
    } else {
        var_s0 = (void *)0x80376550;
    }
    if (D_8004AC88 == 0xC) {
        var_s0 = (void *)0x80320000;
    }
    temp_v0 = D_8004EA9C[arg0];
    switch (temp_v0) {                              /* irregular */
    case 1:
        boot_dma((s32)(D_1EB6D0), (s32)( var_s0),  (s32)D_1F3200 - (s32)D_1EB6D0);
        temp_v0_2 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
        temp_v0_2->slotC60 = var_s0;
        temp_v0_2->slotC64 = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        temp_v0_2->slotC78 = var_s0;
        temp_v0_2->slotC7C = 0;
        break;
    case 2:
        boot_dma((s32)(D_2C2280), (s32)( var_s0),  (s32)D_2CF0A0 - (s32)D_2C2280);
        temp_v0_3 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
        temp_v0_3->slotC60 = var_s0;
        temp_v0_3->slotC64 = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        temp_v0_3->slotC90 = var_s0;
        temp_v0_3->slotC94 = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        temp_v0_3->slot1038 = var_s0;
        temp_v0_3->slot103C = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        temp_v0_3->slot11A0 = var_s0;
        temp_v0_3->slot11A4 = 0;
        break;
    case 4:
        boot_dma((s32)(D_469660), (s32)( var_s0),  (s32)D_470390 - (s32)D_469660);
        var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
        var_v0->slotC78 = var_s0;
        var_v0->slotC7C = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        var_v0->slotC90 = var_s0;
block_14:
        var_v0->slotC94 = 0;
        break;
    case 5:
        boot_dma((s32)(D_53CC40), (s32)( var_s0),  (s32)D_543D10 - (s32)D_53CC40);
        var_v0 = (T032Resource714 *)(D_8004D278 + arg0 * 8);
        var_v0->slotC48 = var_s0;
        var_v0->slotC4C = 0;
        var_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        var_v0->slotC90 = var_s0;
        goto block_14;
    }
    D_8004F396[arg0] = 1;
}
