/* DRAFT. Remaining diff: 218 differing instruction words; emitted 872 / original 880 bytes (positional comparison). */
extern s32 func_80035240(u8 *, u8 *, s32, u8 *), func_8003BC0C(u8 *), func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *), func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_80035320(u8 *pak, s32 file, s32 write, s32 offset, s32 length, u8 *buffer) {
    u8 entry[32];
    u16 inode[128];
    u16 page;
    u8 cached = 0xFF;
    s32 result;
    s32 block;
    s32 n;
    write &= 0xFF;
    if (file >= *(s32 *)(pak+0x50) || file < 0 || length <= 0 || (length&31) || offset < 0 || (offset&31)) return 5;
    if (!(*(s32 *)pak & 1)) return 5;
    if (func_8003BC0C(pak) == 2) return 2;
    if (pak[0x65] != 0) { pak[0x65] = 0; result = func_8003BFC0(pak); if (result != 0) return result; }
    result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry);
    if (result != 0) return result;
    page = *(u16 *)(entry+6);
    if (page < *(s32 *)(pak+0x60) || (page >> 8) >= pak[0x64] || (page&0xFF) == 0 || (page&0xFF) >= 128) return page == 1 ? 5 : 3;
    if (write == 0 && !(entry[8]&2)) return 6;
    block = offset / 32;
    while (block >= 8) {
        result = func_80035240(pak, &cached, (s32)inode, (u8 *)&page);
        block -= 8;
        if (result != 0) return result;
    }
    n = length / 32;
    while (n > 0) {
        s32 address;
        if (block == 8) { result = func_80035240(pak, &cached, (s32)inode, (u8 *)&page); block = 0; if (result != 0) return result; }
        if ((page >> 8) != pak[0x65]) { pak[0x65] = page >> 8; result = func_8003BFC0(pak); if (result != 0) return result; }
        address = (((page&0xFF)*8)+block)&0xFFFF;
        if (write == 0) result = func_8003C030(*(s32 *)(pak+4), *(s32 *)(pak+8), address, buffer);
        else result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), address, buffer, 0);
        buffer += 32;
        if (result != 0) return result;
        n--; block++;
    }
    if (write == 1 && !(entry[8]&2)) {
        entry[8] |= 2; pak[0x65] = 0;
        result = func_8003BFC0(pak); if (result != 0) return result;
        result = func_8003C3C0(*(s32 *)(pak+4), *(s32 *)(pak+8), (*(s32 *)(pak+0x5C)+file)&0xFFFF, entry, 0);
        if (result != 0) return result;
    }
    return 0;
}
