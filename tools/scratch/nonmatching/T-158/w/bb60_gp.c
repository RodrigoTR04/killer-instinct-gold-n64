/* T-158 draft: palette gradients packed with the 5551 macro, 8-bit components. */
extern u8 D_802C8D20[], D_802C9F20[], D_802C9F60[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
extern u8 D_802C9F68, D_802C9F69;
void func_801BBB60(void)
{
    s16 *palette = D_802C9D20;
    s32 i, r, g, b;
    D_802C9F68 = 0;
    D_802C9F69 = 1;
    for (i = 0; i < 0x1000; i++) D_802C8D20[i] = 128;
    for (i = 0; i < 64; i++) D_802C9F20[i] = 124;
    i = 0;
    do
    {
        *palette++ = i++;
    }
    while (i < 128);
    i = 0;
    for (; i != 8; i++) {
        *palette++ = 0;
    }
    if (i < 40) do
    {
        r = (i - 8) << 3; g = 0; b = 0;
        i++;
        *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
    }
    while (i < 40);
    if (i < 72) do
    {
        r = 248; g = (i - 40) << 3; b = 0;
        i++;
        *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
    }
    while (i < 72);
    if (i < 128) do
    {
        r = 248; g = 248; b = (i - 72) << 2;
        *palette++ = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1; i++;
    }
    while (i < 128);
    D_802C9F64 = 0;
}
