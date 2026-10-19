/* DRAFT. Remaining diff: 39 differing instruction words; emitted 228 / original 236 bytes (positional comparison). */
extern s32 func_8003B3E0(u8 *, s32), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_80036644(u8 *pak, s32 page, u16 *sum, s8 bank) {
    s32 saved;
    u8 block[32];
    s32 result;
    s32 i = 0;
    pak[0x65] = bank;
    result = func_8003BFC0(pak);
    if (result != 0) return result;
    do {
        result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), (((page & 0xFF) * 8) + i) & 0xFFFF, block);
        if (result != 0) {
            pak[0x65] = 0;
            saved = result;
            func_8003BFC0(pak);
            return saved;
        }
        i++;
        *sum += func_8003B3E0(block, 32);
    } while (i != 8);
    pak[0x65] = 0;
    return func_8003BFC0(pak);
}
