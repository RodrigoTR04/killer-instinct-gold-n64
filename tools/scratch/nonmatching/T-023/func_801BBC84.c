/* DRAFT. Remaining diff: Fire-effect traversal, random-call temporaries and loop scheduling differ. */
extern s32 guRandom(void);
extern u8 D_801F3D64, D_802C9F68, D_802C9F69;
extern u8 D_802C8D20[], D_802C8DA0[], D_802C9D20[], D_802C9F20[], D_802C9F60[];
void func_801BBC84(void) {
    u8 *row, *p, *src, *dst;
    s32 column, value, random, i;
    u8 tick;
    tick = D_802C9F68 + 1;
    D_802C9F68 = tick;
    if ((tick & 255) >= (s32)D_802C9F69) {
        D_802C9F68 = 0;
        dst = D_802C8D20;
        src = D_802C9F20;
        do { value = *src++; dst++; dst[0xD7F] = value; } while ((u32)src < (u32)D_802C9F60);
        column = 0;
        do {
            row = D_802C8DA0;
            p = row + column;
            do {
                value = (*p - 128) * 2;
                if (value < (s32)D_801F3D64) *p = 128;
                else {
                    random = guRandom();
                    p[-(random % 3) - 63] = ((value - guRandom() % (s32)D_801F3D64) >> 1) + 128;
                    *p -= 1;
                }
                row += 64; p += 64;
            } while (row != D_802C9D20);
            column++;
        } while (column < 64);
        i = 0;
        do {
            value = guRandom() & 255;
            if (value < 10) D_802C9F20[i] = 255;
            else if (value < 20) D_802C9F20[i] = 128;
            i++;
        } while (i != 64);
    }
}
