/* DRAFT. Remaining diff: 126 differing instruction words; emitted 448 / original 516 bytes (positional comparison). */
extern s32 func_80036644(u8 *, s32, u16 *, s32);
s32 func_80036440(u8 *pak, u16 *inode, u8 page, u16 *sum, u8 bank, u16 *nextOut, s32 release) {
    u16 next = inode[page];
    s32 minimum = (next != 1 ? ((u8)next > 0) : (bank > 0)) ? 1 : *(s32 *)(pak + 0x60);
    s32 result;
    if ((next & 0xFF) < minimum && next != 1) return 3;
    *nextOut = next;
    if (release == 1) inode[page] = 3;
    result = func_80036644(pak, page, sum, bank);
    if (result != 0) return result;
    if (next == 1) return 0;
    while (next >= *(s32 *)(pak + 0x60)) {
        u16 previous = next;
        next = inode[next & 0xFF];
        inode[previous & 0xFF] = 3;
        result = func_80036644(pak, previous & 0xFF, sum, bank);
        if (result != 0) return result;
        if (bank != (u8)next || next < *(s32 *)(pak + 0x60)) break;
    }
    if (next >= *(s32 *)(pak + 0x60)) inode[next & 0xFF] = 3;
    *nextOut = next;
    return 0;
}
