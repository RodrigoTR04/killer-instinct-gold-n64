/* T-045 DRAFT: 2 words remain, full TU and standalone; 196/196 bytes. The size spill is at 0x24 instead of 0x20. Was 25 words/192 bytes. Signed boot_dma prototype, signed address subtraction and u32 size restore the original register/scheduling shape. */
extern void boot_dma(s32, s32, s32);
extern void func_800245B4(s32, void *, s32);
extern u8 D_8B70[], D_119F0[], D_48FD0[], D_2ECB0[];
typedef struct { s32 zero; void *data; } T032Bank;
extern struct { u8 pad[0x12A8]; T032Bank banks[2]; } D_8004D278;
void func_800244F0(s32 player) {
    u8 *base;
    u32 size;
    if (player == 0) base = (u8 *)0x8020B480;
    else base = (u8 *)0x802D7A40;
    func_800245B4(player, base + 0x493E0, 0x2F760);
    base = (u8 *)(((u32)(base + (u32)D_48FD0 - (u32)D_2ECB0) + 15) & ~15);
    size = (s32)D_119F0 - (s32)D_8B70;
    boot_dma((s32)D_8B70, (s32)base, size);
    func_800245B4(player, base, size);
    D_8004D278.banks[player].data = base;
    D_8004D278.banks[player].zero = 0;
}
