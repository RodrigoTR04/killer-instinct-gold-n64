/* DRAFT. Remaining diff: 245 differing instruction words; emitted 988 / original 1012 bytes (positional comparison). */
extern s32 func_80034630(u8 *, s32, s32, u8 *, u8 *, s32 *), func_80035A84(u8 *, u16 *, s32, s32 *, u8, s32 *, s32 *);
extern s32 func_8003BC0C(u8 *), func_8003BD24(u8 *, void *, s32, s32), func_8003C750(u8 *, s32 *);
extern s32 func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_80035690(u8 *pak, u16 company, s32 game, u8 *name, u8 *extension, s32 bytes, s32 *file) {
    u16 previous[128], current[128];
    u8 entry[32];
    s32 freeBytes, result, start = -1, allocated, last = 0;
    s32 remaining = (bytes+255)/256;
    s32 chainCount = 0;
    u8 bank = 0, firstBank = 0, firstPage = 0;
    s32 i;
    if (company == 0 || game == 0 || !(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    result = func_80034630(pak, company, game, name, extension, file);
    if (result != 0 && result != 5) return result;
    if (*file != -1) return 9;
    func_8003C750(pak, &freeBytes);
    if (freeBytes < bytes) return 7;
    if (remaining == 0) return 5;
    result = func_80034630(pak, 0, 0, 0, 0, file);
    if (result != 0 && result != 5) return result;
    if (*file == -1) return 8;
    while (bank < pak[0x64]) {
        result = func_8003BD24(pak, current, 0, bank); if (result != 0) return result;
        result = func_80035A84(pak, current, remaining, &start, bank, &allocated, &last); if (result != 0) return result;
        if (start != -1) {
            if (chainCount == 0) { firstPage = start; firstBank = bank; }
            else {
                ((u8 *)&previous[last])[0] = bank; ((u8 *)&previous[last])[1] = start;
                result = func_8003BD24(pak, previous, 1, entry[0]); if (result != 0) return result;
            }
            for (i = 0; i < 128; i++) previous[i] = current[i];
            entry[0] = bank;
            chainCount++;
            if (allocated >= remaining) { remaining = 0; break; }
            remaining -= allocated;
        }
        bank++;
    }
    if (remaining > 0 || start == -1) return 3;
    ((u8 *)&previous[last])[0] = bank; ((u8 *)&previous[last])[1] = start;
    result = func_8003BD24(pak, previous, 1, entry[0]); if (result != 0) return result;
    *(s32 *)entry = game;
    *(u16 *)(entry+4) = company;
    entry[6] = firstBank; entry[7] = firstPage;
    entry[8] = 0; entry[10] = 0; entry[11] = 0;
    for (i = 0; i < 16; i++) entry[16+i] = name[i];
    for (i = 0; i < 4; i++) entry[12+i] = extension[i];
    result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*file+*(s32 *)(pak+0x5C))&0xFFFF, entry, 0);
    return result;
}
