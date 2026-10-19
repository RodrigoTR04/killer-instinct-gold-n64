/* DRAFT. Remaining diff: 21 differing instruction words; emitted 108 / original 112 bytes (positional comparison). */
extern s32 func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_8003BFC0(u8 *pak) {
    u8 block[32];
    s32 i;
    for (i = 0; i < 32; i++) block[i] = pak[0x65];
    return func_8003C3C0(*(s32 *)(pak + 4), *(s32 *)(pak + 8), 0x400, block, 0);
}
