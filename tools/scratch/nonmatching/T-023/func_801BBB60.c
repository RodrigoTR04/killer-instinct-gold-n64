/* DRAFT. Remaining diff: Palette-loop types, unrolled store order and global-base scheduling differ. */
extern u8 D_802C8D20[], D_802C9F20[], D_802C9F60[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
extern u8 D_802C9F68, D_802C9F69;
void func_801BBB60(void) {
    u8 *p;
    s16 *palette;
    s16 i;
    s32 j;
    D_802C9F68 = 0;
    palette = D_802C9D20;
    D_802C9F69 = 1;
    p = D_802C8D20;
    do { *p++ = 128; } while ((u32)p < (u32)D_802C9D20);
    p = D_802C9F20;
    do { *p++ = 124; } while ((u32)p < (u32)D_802C9F60);
    i = 0;
    do { *palette++ = i++; } while (i < 128);
    j = 0;
    do { j++; *palette = 0; palette++; } while (j != 8);
    if (j < 40) do { *palette++ = ((j - 8) << 11) | 1; j++; } while (j < 40);
    if (j < 72) do { *palette++ = (((j - 40) << 6) & 0x7C0) | 0xF801; j++; } while (j < 72);
    if (j < 128) do { *palette++ = (j - 72) | 0xFFC1; j++; } while (j < 128);
    D_802C9F64 = 0;
}
