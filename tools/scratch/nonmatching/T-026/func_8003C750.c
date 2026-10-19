/* DRAFT. Remaining diff: 91 differing instruction words; emitted 296 / original 432 bytes (positional comparison). */
extern s32 func_8003BC0C(u8 *), func_8003BD24(u8 *, void *, s32, s32);
s32 func_8003C750(u8 *pak, s32 *bytes) {
    u16 inode[128];
    s32 freePages = 0;
    s32 bank = 0;
    if (!(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    if (pak[0x64] > 0) {
        do {
            s32 i;
            s32 result = func_8003BD24(pak, inode, 0, bank & 0xFF);
            if (result != 0) return result;
            i = bank > 0 ? 1 : *(s32 *)(pak + 0x60);
            for (; i < 128; i++) if (inode[i] == 3) freePages++;
            bank = (bank + 1) & 0xFF;
        } while (bank < pak[0x64]);
    }
    *bytes = freePages << 8;
    return 0;
}
