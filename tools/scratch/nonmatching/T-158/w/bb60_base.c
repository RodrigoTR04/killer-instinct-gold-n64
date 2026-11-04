/* T-148 draft: two indexed fills and palette generation. */
extern u8 D_802C8D20[], D_802C9F20[], D_802C9F60[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
extern u8 D_802C9F68, D_802C9F69;
void func_801BBB60(void)
{
    s16 *palette = D_802C9D20;
    s32 i, red, green;
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
        red = i - 8;
        i++;
        *palette++ = (red << 11) | 1;
    }
    while (i < 40);
    if (i < 72) do
    {
        green = i - 40;
        i++;
        *palette++ = ((green << 6) & 0x7C0) | 0xF801;
    }
    while (i < 72);
    if (i < 128) do
    {
        *palette++ = (i - 72) | 0xFFC1; i++;
    }
    while (i < 128);
    D_802C9F64 = 0;
}
