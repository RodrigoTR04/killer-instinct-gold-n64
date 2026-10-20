/* DRAFT. Remaining diff: 8 differing words at equal size; store order in unrolled fill loops. */
extern u16 D_80006574[], D_800065B4[], D_800065D4[], D_80006610[];
extern s32 func_80000960(u32 *, u32, u32, u16 *, u16 *, void **, s32 *);
extern s32 func_80000FA0(void *, void *, s32, s32);

s32 func_80001564(void) {
    u32 i;
    void *literalTable;
    void *distanceTable;
    s32 literalBits;
    s32 distanceBits;
    u32 lengths[288];
    for (i = 0; i < 144;) lengths[i++] = 8;
    for (; i < 256;) lengths[i++] = 9;
    for (; i < 280;) lengths[i++] = 7;
    for (; i < 288;) lengths[i++] = 8;
    literalBits = 7;
    func_80000960(lengths, 288, 257, D_80006574, D_800065B4, &literalTable, &literalBits);
    for (i = 0; i < 30;) lengths[i++] = 5;
    distanceBits = 5;
    func_80000960(lengths, 30, 0, D_800065D4, D_80006610, &distanceTable, &distanceBits);
    func_80000FA0(literalTable, distanceTable, literalBits, distanceBits);
    return 0;
}
