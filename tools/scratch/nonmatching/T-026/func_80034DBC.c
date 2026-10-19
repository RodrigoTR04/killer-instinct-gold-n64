/* DRAFT. Remaining diff: 176 differing instruction words; emitted 692 / original 740 bytes (positional comparison). */
extern s32 func_8003BD24(u8 *, void *, s32, s32);
s32 func_80034DBC(u8 *pak, u8 *cache) {
    u16 inode[128];
    s32 bank = 0;
    s32 i;
    for (i = 0; i < 256; i++) cache[0x101+i] = 0;
    cache[0x100] = 0xFF;
    if (pak[0x64] > 0) {
        do {
            s32 first = bank > 0 ? 1 : *(s32 *)(pak+0x60);
            s32 result = func_8003BD24(pak, inode, 0, bank & 0xFF);
            if (result != 0 && result != 3) return result;
            for (i = first; i < 128; i++) {
                u16 next = inode[i];
                if (next >= *(s32 *)(pak+0x60) && bank != (u8)next) {
                    s32 slot = (next & 0xFF)/4 + (((next >> 8)%8)<<5);
                    cache[0x101+slot] |= 1 << (bank%8);
                }
            }
            bank = (bank+1)&0xFF;
        } while (bank < pak[0x64]);
    }
    return 0;
}
