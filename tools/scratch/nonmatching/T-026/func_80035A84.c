/* DRAFT. Remaining diff: 121 differing instruction words; emitted 520 / original 512 bytes (positional comparison). */
extern s32 func_80035C84(u8 *, s32, void *, s32);
s32 func_80035A84(u8 *pak, u16 *inode, s32 wanted, s32 *first, u8 bank, s32 *allocated, s32 *last) {
    u8 zero[32];
    s32 start;
    s32 current;
    s8 next;
    s32 i;
    s32 result = 0;
    start = bank > 0 ? 1 : *(s32 *)(pak + 0x60);
    for (; start < 128; start++) if (inode[start] == 3) break;
    if (start == 128) { *first = -1; return 0; }
    for (i = 0; i < 32; i++) zero[i] = 0;
    current = start;
    next = start + 1;
    *allocated = 1;
    while (*allocated < wanted && next < 128) {
        if (inode[next] == 3) {
            ((u8 *)&inode[current])[0] = bank;
            ((u8 *)&inode[current])[1] = next;
            result = func_80035C84(pak, current, zero, bank);
            if (result != 0) return result;
            current = next;
            (*allocated)++;
        }
        next++;
    }
    *first = start;
    if (next == 128 && *allocated < wanted) { *last = current; return result; }
    inode[current] = 1;
    result = func_80035C84(pak, current, zero, bank);
    *last = 0;
    return result;
}
