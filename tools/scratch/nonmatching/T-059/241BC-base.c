/* T-054 DRAFT: 161 relocation-masked positional words differ; 840 emitted bytes. See T-054/REPORT.md. */

typedef struct { u8 pad0[3672]; u8 *slotE58; u8 *slotE5C; u8 padE60[424]; u8 *slot1008; u8 *slot100C; u8 pad1010[64]; u8 *slot1050; u8 *slot1054; u8 pad1058[16]; u8 *slot1068; u8 *slot106C; u8 pad1070[16]; u8 *slot1080; u8 *slot1084; } T032Resource1BC;
extern u8 D_119F0[],D_13200[],D_1D640[],D_24D60[],D_2ECB0[],D_471440[],D_472FB0[],D_48FD0[],D_543D10[],D_54D720[],D_8004D278[],D_8004EA9C[],D_8023E408[],D_8B70[];
extern u8 D_8004F395;
extern void boot_dma(s32,s32,s32),boot_dma_chunked(void *,void *,s32),func_800245B4(s32,void *,s32),func_80030220(void *,void *,s32);
void func_800241BC(s32 arg0) {
    u32 sp20;
    u8 *temp_a1;
    u8 *temp_a1_2;
    u8 *var_s0;
    s32 temp_v0;
    void *temp_a2;
    u8 *temp_s0;
    T032Resource1BC *temp_v0_2;
    T032Resource1BC *temp_v0_3;
    T032Resource1BC *temp_v0_4;
    T032Resource1BC *temp_v0_5;
    T032Resource1BC *temp_v0_6;

    if (arg0 == 0) {
        var_s0 = (u8 *)0x8020B480;
    } else {
        var_s0 = (u8 *)0x802D7A40;
    }
    temp_v0 = D_8004EA9C[arg0];
    switch (temp_v0) {                              /* irregular */
    case 2:
        boot_dma((s32)(D_13200), (s32)( var_s0),  (s32)D_1D640 - (s32)D_13200);
        temp_v0_2 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
        temp_v0_2->slotE58 = var_s0;
        temp_v0_2->slotE5C = 0;
        temp_s0 = (var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10);
        temp_v0_2->slot1008 = temp_s0;
        temp_v0_2->slot100C = 0;
        temp_v0_2->slot1050 = 0;
        temp_v0_2->slot1054 = (void *) ((temp_s0[7] << 0x18) + temp_s0 + temp_s0[4] + (temp_s0[5] << 8) + (temp_s0[6] << 0x10));
        break;
    case 3:
        boot_dma((s32)(D_1D640), (s32)( var_s0),  (s32)D_24D60 - (s32)D_1D640);
        temp_v0_3 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
        temp_v0_3->slot1050 = var_s0;
        temp_v0_3->slot1054 = 0;
        break;
    case 4:
        boot_dma_chunked(D_24D60, var_s0, D_2ECB0 - D_24D60);
        temp_v0_4 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
        temp_a2 = D_472FB0 - D_471440;
        temp_v0_4->slot1008 = var_s0;
        temp_v0_4->slot100C = 0;
        sp20 = temp_a2;
        boot_dma_chunked(D_471440, 0x8023D400, temp_a2);
        func_80030220(D_8023E408, sp20 + 0x8023D580, 0x93);
        func_800245B4(0, 0x8023D400, sp20);
        break;
    case 5:
        boot_dma((s32)(D_543D10), (s32)( var_s0),  (s32)D_54D720 - (s32)D_543D10);
        temp_v0_5 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
        temp_v0_5->slot1050 = var_s0;
        temp_v0_5->slot1054 = 0;
        temp_a1 = (u8 *)((u32)((var_s0[7] << 0x18) + var_s0 + var_s0[4] + (var_s0[5] << 8) + (var_s0[6] << 0x10) + 0xF) & ~0xF);
        sp20 = (u32)temp_v0_5;
        boot_dma((s32)(D_119F0), (s32)( temp_a1),  (s32)D_13200 - (s32)D_119F0);
        temp_v0_5->slot1080 = 0;
        temp_v0_5->slot1084 = temp_a1;
        temp_v0_5->slot1068 = 0;
        temp_v0_5->slot106C = (s32) ((temp_a1[7] << 0x18) + temp_a1 + temp_a1[4] + (temp_a1[5] << 8) + (temp_a1[6] << 0x10));
        break;
    default:
        temp_a1_2 = (u8 *)((u32)(((u32)var_s0 + (u32)D_48FD0 - (u32)D_2ECB0) + 0xF) & ~0xF);
        boot_dma((s32)(D_8B70), (s32)( temp_a1_2),  (s32)D_119F0 - (s32)D_8B70);
        temp_v0_6 = (T032Resource1BC *)(D_8004D278 + arg0 * 8);
        temp_v0_6->slot1080 = 0;
        temp_v0_6->slot1084 = temp_a1_2;
        break;
    }
    D_8004F395 = 1;
}
