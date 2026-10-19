/* DRAFT. Remaining diff: 101 differing instruction words; emitted 408 / original 416 bytes (positional comparison). */
extern s32 func_8003BD24(u8 *, void *, s32, s32);
s32 func_800350A0(u8 *pak, u8 page, u8 *cache) {
    s32 count = 0;
    u8 bank = 0;
    if (pak[0x64] > 0) {
        do {
            s32 first = bank > 0 ? 1 : *(s32 *)(pak + 0x60);
            if (page == bank || (cache[0x101 + page / 4 + ((page % 8) << 5)] & (1 << (bank % 8)))) {
                if (cache[0x100] != bank) {
                    s32 result = func_8003BD24(pak, cache, 0, bank);
                    if (result != 0 && result != 3) return result;
                    cache[0x100] = bank;
                }
                for (; count < 2 && first < 0x80; first++) if (*(u16 *)(cache + first*2) == page) count++;
                if (count >= 2) return 2;
            }
            bank++;
        } while (bank < pak[0x64]);
    }
    return count;
}
