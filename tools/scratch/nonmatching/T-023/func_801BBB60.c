/* T-138 DRAFT: 29 differing words; 292 bytes. Not matching. */
extern u8 D_802C8D20[], D_802C9F20[], D_802C9F60[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
extern u8 D_802C9F68, D_802C9F69;
void func_801BBB60(void)
{
    u8 *p;
    s16 *palette = (s16 *)(D_802C8D20 + 0x1000);
    s32 i;
    D_802C9F68 = 0;
    D_802C9F69 = 1;
    p = D_802C8D20; do
    {
        *p++ = 128;
    }
    while ((u32)p < (u32)D_802C9D20);
    p = D_802C9F20;
    do
    {
        *p++ = 124;
    }
    while ((u32)p < (u32)D_802C9F60);
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
        *palette++ = ((i - 8) << 11) | 1; i++;
    }
    while (i < 40);
    if (i < 72) do
    {
        *palette++ = (((i - 40) << 6) & 0x7C0) | 0xF801; i++;
    }
    while (i < 72);
    if (i < 128) do
    {
        *palette++ = (i - 72) | 0xFFC1; i++;
    }
    while (i < 128);
    D_802C9F64 = 0;
}
