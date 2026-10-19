/* DRAFT. Remaining diff: 169 differing instruction words; emitted 560 / original 688 bytes (positional comparison). */
extern s32 func_8003BC0C(u8 *), func_8003BD24(u8 *, void *, s32, s32), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_80035F10(u8 *pak, s32 file, u8 *state) {
    u16 inode[128];
    u8 entry[32];
    u16 next = 0;
    u8 bank, page;
    s32 count = 0;
    s32 result;
    s32 i;
    if (file >= *(s32 *)(pak+0x50) || file < 0 || !(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry);
    if (result != 0) return result;
    if (*(u16 *)(entry+4) == 0 || *(s32 *)entry == 0) return 5;
    next = *(u16 *)(entry+6);
    if (next < *(s32 *)(pak+0x60)) return 3;
    bank = next >> 8; page = next;
    while (bank < pak[0x64]) {
        result = func_8003BD24(pak, inode, 0, bank); if (result != 0) return result;
        do {
            count++;
            next = inode[page];
            page = next;
        } while (next >= *(s32 *)(pak+0x60) && (next >> 8) == bank);
        if (next == 1) break;
        bank = next >> 8;
    }
    if (next != 1) return 3;
    *(s32 *)state = count << 8;
    *(u16 *)(state+8) = *(u16 *)(entry+4);
    *(s32 *)(state+4) = *(s32 *)entry;
    for (i = 0; i < 16; i++) state[14+i] = entry[16+i];
    for (i = 0; i < 4; i++) state[10+i] = entry[12+i];
    return 0;
}
