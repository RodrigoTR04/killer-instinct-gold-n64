/* DRAFT. Remaining diff: 32 differing instruction words; emitted 156 / original 172 bytes (positional comparison). */
extern s32 func_8003BFC0(u8 *);
extern s32 func_8003C3C0(s32, s32, s32, void *, s32);
void func_80035C84(u8 *pak, s32 page, void *data, s8 bank) {
    s32 i = 0;
    s32 address;
    pak[0x65] = bank;
    if (func_8003BFC0(pak) != 0) return;
    address = page * 8;
    do {
        i++;
        if (func_8003C3C0(*(s32 *)(pak + 4), *(s32 *)(pak + 8), address & 0xFFFF, data, 0) != 0) break;
        address++;
    } while (i != 8);
    pak[0x65] = 0;
    func_8003BFC0(pak);
}
