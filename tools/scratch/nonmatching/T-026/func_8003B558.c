/* DRAFT. Remaining diff: 208 differing instruction words; emitted 832 / original 844 bytes (positional comparison). */
extern s32 func_8003B45C(u16 *, u16 *, u16 *), func_8003BFC0(u8 *), osGetCount(void);
extern s32 func_8003C030(s32, s32, s32, void *), func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_8003B558(u8 *pak, u8 *old, u8 *id) {
    u8 writeBlock[32], readBlock[32];
    u16 locations[4];
    u8 bank = 0;
    s32 result;
    s32 i;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    *(s32 *)id = -1;
    *(s32 *)(id+4) = osGetCount();
    *(s32 *)(id+12) = *(s32 *)(old+12); *(s32 *)(id+8) = *(s32 *)(old+8);
    *(s32 *)(id+20) = *(s32 *)(old+20); *(s32 *)(id+16) = *(s32 *)(old+16);
    do {
        pak[0x65] = bank;
        result = func_8003BFC0(pak); if (result != 0) return result;
        result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 0, writeBlock); if (result != 0) return result;
        writeBlock[0] = bank | 0x80;
        for (i = 1; i < 32; i++) writeBlock[i] = ~writeBlock[i];
        result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), 0, writeBlock, 0); if (result != 0) return result;
        result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 0, readBlock); if (result != 0) return result;
        for (i = 0; i < 32; i++) if (readBlock[i] != writeBlock[i]) break;
        if (i != 32) break;
        if (bank > 0) {
            pak[0x65] = 0;
            result = func_8003BFC0(pak); if (result != 0) return result;
            result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 0, writeBlock); if (result != 0) return result;
            if (writeBlock[0] != 0x80) break;
        }
        bank++;
    } while (bank < 0x3E);
    pak[0x65] = 0;
    result = func_8003BFC0(pak); if (result != 0) return result;
    id[26] = bank;
    *(u16 *)(id+24) = (*(u16 *)(old+24) & 0xFFFE) | (bank > 0);
    id[27] = old[27];
    func_8003B45C((u16 *)id, (u16 *)(id+28), (u16 *)(id+30));
    locations[0] = 1; locations[1] = 3; locations[2] = 4; locations[3] = 6;
    for (i = 0; i < 4; i++) {
        result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), locations[i], id, 1); if (result != 0) return result;
    }
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 1, writeBlock); if (result != 0) return result;
    for (i = 0; i < 32; i++) if (writeBlock[i] != id[i]) return 10;
    return 0;
}
