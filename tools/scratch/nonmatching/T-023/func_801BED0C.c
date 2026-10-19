/* DRAFT. Remaining diff: 64-bit divide/remainder code, loop registers and scheduling differ. */
typedef struct { u8 *entries; u8 count, descending; u16 pad; } T023TableD0C;
extern T023TableD0C D_80127D80[];
extern void func_801BEFFC(void);
void func_801BED0C(u32 text, u64 packed) {
    s32 i, j;
    u32 normalized;
    if ((text >> 24) == 0) text |= 0x20000000;
    if (!(text & 0xFF0000)) text |= 0x200000;
    if (!(text & 0xFF00)) text |= 0x2000;
    normalized = text & ~255;
    for (i = 1; i != 4; i++) {
        if (packed % 11 != 0) *(u32 *)(D_80127D80[i].entries + ((u32)(packed % 11) - 1) * 8) = normalized;
        packed /= 11;
    }
    j = 0;
    do {
        if (packed % 6 != 0) *(u32 *)(D_80127D80[i].entries + ((u32)(packed % 6) - 1) * 8) = normalized;
        i++; packed /= 6; j++;
    } while (j != 20);
    func_801BEFFC();
}
