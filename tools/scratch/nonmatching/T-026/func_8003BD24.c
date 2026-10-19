/* DRAFT. Remaining diff: 166 differing instruction words; emitted 660 / original 668 bytes (positional comparison). */
extern s32 func_8003B3E0(u8 *, s32), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *), func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_8003BD24(u8 *pak, void *buffer, s32 write, s32 bank) {
    u8 *inode = buffer;
    u8 *p;
    s32 first;
    s32 i;
    s32 result;
    s32 offset;
    u8 checksum;
    bank &= 0xFF; write &= 0xFF;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    first = bank > 0 ? 1 : *(s32 *)(pak+0x60);
    if (write == 1) inode[1] = func_8003B3E0(inode+first*2, 256-first*2);
    p = inode;
    offset = bank*8;
    for (i = 0; i < 8; i++, p += 32) {
        if (write == 1) {
            func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x54)+offset+i)&0xFFFF, p, 0);
            result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x58)+offset+i)&0xFFFF, p, 0);
        } else result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x54)+offset+i)&0xFFFF, p);
        if (result != 0) return result;
    }
    if (write == 0) {
        checksum = func_8003B3E0(inode+first*2, 256-first*2);
        if (checksum != inode[1]) {
            for (i = 0, p = inode; i < 8; i++, p += 32) func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x58)+offset+i)&0xFFFF, p);
            if (checksum != inode[1]) return 3;
            for (i = 0, p = inode; i < 8; i++, p += 32) func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x54)+offset+i)&0xFFFF, p, 0);
        } else {
            for (i = 0, p = inode; i < 8; i++, p += 32) func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x58)+offset+i)&0xFFFF, p, 0);
        }
    }
    return 0;
}
