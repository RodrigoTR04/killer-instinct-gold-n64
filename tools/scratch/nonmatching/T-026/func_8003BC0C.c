/* DRAFT. Remaining diff: 54 differing instruction words; emitted 280 / original 280 bytes (positional comparison). */
extern s32 func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_8003BC0C(u8 *pak) {
    u8 block[32];
    s32 result;
    s32 i;
    if (pak[0x65] != 0) {
        pak[0x65] = 0;
        result = func_8003BFC0(pak);
        if (result != 0) return result;
    }
    result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), 1, block);
    if (result == 2) {
        result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), 1, block);
        if (result != 0) return result;
    } else if (result != 0) return result;
    for (i = 0; i < 32; i++) if (pak[0xC + i] != block[i]) return 2;
    return 0;
}
