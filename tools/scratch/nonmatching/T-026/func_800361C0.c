/* DRAFT. Remaining diff: 154 differing instruction words; emitted 612 / original 640 bytes (positional comparison). */
extern s32 func_80034630(u8 *, s32, s32, u8 *, u8 *, s32 *);
extern s32 func_80036440(u8 *, u16 *, u8, u16 *, u8, u16 *, s32);
extern s32 func_8003BC0C(u8 *), func_8003BD24(u8 *, void *, s32, s32), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *), func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_800361C0(u8 *pak, s32 company, s32 game, u8 *name, u8 *extension) {
    s32 file;
    u16 inode[128];
    u8 entry[32];
    u16 sum = 0, next;
    u8 bank, page, finalBank;
    s32 result;
    s32 i;
    company &= 0xFFFF;
    if (company == 0 || game == 0 || !(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    result = func_80034630(pak, company, game, name, extension, &file);
    if (result != 0) return result;
    if (file == -1) return 5;
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry);
    bank = entry[6]; page = entry[7]; finalBank = bank;
    if (result != 0) return result;
    while (bank < pak[0x64]) {
        result = func_8003BD24(pak, inode, 0, bank); if (result != 0) return result;
        result = func_80036440(pak, inode, page, &sum, bank, &next, 1); if (result != 0) return result;
        result = func_8003BD24(pak, inode, 1, bank); if (result != 0) return result;
        if (next == 1) break;
        bank = next >> 8; page = next & 0xFF; finalBank = bank;
    }
    if (finalBank >= pak[0x64]) return 3;
    for (i = 0; i < 32; i++) entry[i] = 0;
    return func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry, 0);
}
