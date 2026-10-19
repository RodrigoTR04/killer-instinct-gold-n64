/* DRAFT. Remaining diff: 55 differing instruction words; emitted 292 / original 304 bytes (positional comparison). */
extern s32 func_8003BC0C(u8 *), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_80035DE0(u8 *pak, s32 *total, s32 *used) {
    u32 block[8];
    s32 result;
    s32 i;
    s32 count = 0;
    if (!(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    if (pak[0x65] != 0) {
        pak[0x65] = 0;
        result = func_8003BFC0(pak);
        if (result != 0) return result;
    }
    for (i = 0; i < *(s32 *)(pak + 0x50); i++) {
        result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), (*(s32 *)(pak + 0x5C) + i) & 0xFFFF, block);
        if (result != 0) return result;
        if (block[1] != 0 && block[0] != 0) count++;
    }
    *used = count;
    *total = *(s32 *)(pak + 0x50);
    return 0;
}
