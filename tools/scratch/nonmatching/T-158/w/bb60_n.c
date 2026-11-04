/* T-158 draft: 5551 palette ramps via the SDK-style pack macro. */
#define GPACK_RGBA5551(r, g, b, a) ((((r) << 8) & 0xF800) | (((g) << 3) & 0x7C0) | (((b) >> 2) & 0x3E) | ((a) & 1))
extern u8 D_802C8D20[], D_802C9F20[], D_802C9F60[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
extern u8 D_802C9F68, D_802C9F69;
void func_801BBB60(void)
{
    s16 *palette = D_802C9D20;
    s32 i;
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
    for (; i < 40; i++)
        *palette++ = GPACK_RGBA5551((i - 8) << 3, 0, 0, 1);
    for (; i < 72; i++)
        *palette++ = GPACK_RGBA5551(248, (i - 40) << 3, 0, 1);
    for (; i < 128; i++)
        *palette++ = GPACK_RGBA5551(248, 248, (i - 72) << 2, 1);
    D_802C9F64 = 0;
}
