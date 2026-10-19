/* DRAFT. Remaining diff: 361 differing instruction words; emitted 1280 / original 1516 bytes (positional comparison). */
extern s32 func_80034DBC(u8 *, u8 *), func_800350A0(u8 *, u8, u8 *), func_8003BA08(u8 *), func_8003BC0C(u8 *), func_8003BFC0(u8 *);
extern s32 func_8003BD24(u8 *, void *, s32, s32), func_8003C030(s32, s32, s32, void *), func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_800347D0(u8 *pak) {
    u8 cache[0x201];
    u16 heads[16], inode[128], repaired[128];
    u8 entry[32];
    s32 result = func_8003BC0C(pak);
    s32 changed = 0;
    s32 file, bank, i;
    if (result == 2) result = func_8003BA08(pak);
    if (result != 0) return result;
    result = func_80034DBC(pak, cache); if (result != 0) return result;
    for (file = 0; file < *(s32 *)(pak+0x50); file++) {
        s32 broken = 0;
        result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry);
        if (result != 0) return result;
        if (*(s32 *)entry != 0 && *(u16 *)(entry+4) != 0) {
            u16 page = *(u16 *)(entry+6);
            u8 cached = 0xFF;
            s32 first = 0;
            while (page >= *(s32 *)(pak+0x60) && (page>>8) < pak[0x64] && (page&0xFF) > 0 && (page&0xFF) < 128) {
                if ((page>>8) != cached) {
                    cached = page>>8;
                    result = func_8003BD24(pak, inode, 0, cached);
                    if (result != 0 && result != 3) return result;
                }
                broken = func_800350A0(pak, page>>8, cache) - first;
                if (broken != 0) break;
                first = 1;
                page = inode[page&0xFF];
            }
            if (page != 1) broken = 1;
        } else if (*(s32 *)entry != 0 || *(u16 *)(entry+4) != 0) broken = 1;
        if (broken) {
            *(s32 *)entry = 0; *(u16 *)(entry+4) = 0; *(u16 *)(entry+6) = 0; entry[8] = 0; *(u16 *)(entry+10) = 0;
            if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
            result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry, 0);
            if (result != 0) return result;
            changed++;
        }
    }
    for (file = 0; file < *(s32 *)(pak+0x50); file++) {
        result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry); if (result != 0) return result;
        heads[file] = (*(s32 *)entry != 0 && *(u16 *)(entry+4) != 0 && *(u16 *)(entry+6) >= *(u16 *)(pak+0x62)) ? *(u16 *)(entry+6) : 0;
    }
    for (bank = 0; bank < pak[0x64]; bank++) {
        s32 first = bank > 0 ? 1 : *(s32 *)(pak+0x60);
        result = func_8003BD24(pak, inode, 0, bank); if (result != 0 && result != 3) return result;
        for (i = 0; i < first; i++) repaired[i] = inode[i];
        for (; i < 128; i++) repaired[i] = 3;
        for (file = 0; file < *(s32 *)(pak+0x50); file++) {
            while ((heads[file]>>8) == bank && heads[file] >= *(u16 *)(pak+0x62)) {
                u8 page = heads[file];
                repaired[page] = inode[page];
                heads[file] = inode[page];
            }
        }
        result = func_8003BD24(pak, repaired, 1, bank); if (result != 0) return result;
    }
    if (changed != 0) *(s32 *)pak |= 2;
    else *(s32 *)pak &= ~2;
    return 0;
}
