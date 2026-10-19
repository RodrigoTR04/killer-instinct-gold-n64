/* DRAFT. Remaining diff: 116 differing instruction words; emitted 496 / original 516 bytes (positional comparison). */
extern s32 func_8003B45C(u16 *, u16 *, u16 *), func_8003B558(u8 *, u8 *, u8 *), func_8003B8A4(u8 *, u16 *), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
s32 func_8003BA08(u8 *pak) {
    u16 sum, inverse;
    u8 id[32], repaired[32];
    u8 *chosen;
    s32 i;
    s32 result;
    s32 banks;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 1, id); if (result != 0) return result;
    func_8003B45C((u16 *)id, &sum, &inverse);
    chosen = id;
    if (sum != *(u16 *)(id+28) || inverse != *(u16 *)(id+30)) {
        result = func_8003B8A4(pak, (u16 *)id);
        if (result == 10) {
            result = func_8003B558(pak, id, repaired); if (result != 0) return result;
            chosen = repaired;
        } else if (result != 0) return result;
    }
    if (!(chosen[24] & 1)) {
        result = func_8003B558(pak, chosen, repaired); if (result != 0) return result;
        chosen = repaired;
        if (!(repaired[24] & 1)) return 11;
    }
    for (i = 0; i != 32; i++) pak[12+i] = chosen[i];
    *(s32 *)(pak+0x4C) = chosen[27];
    banks = chosen[26];
    *(s32 *)(pak+0x60) = banks*2+3;
    *(s32 *)(pak+0x50) = 16;
    *(s32 *)(pak+0x54) = 8;
    *(s32 *)(pak+0x58) = banks*8+8;
    *(s32 *)(pak+0x5C) = banks*16+8;
    pak[0x64] = banks;
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), 7, pak+0x2C);
    if (result != 0) return result;
    return 0;
}
