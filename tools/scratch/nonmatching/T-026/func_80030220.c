/* DRAFT. Remaining diff: 85 differing instruction words; emitted 340 / original 348 bytes (positional comparison). */
extern s32 guRandom(void);
extern u8 D_80069930;
void func_80030220(s16 *vertices, s16 *out, s32 count) {
    s16 *end = vertices + count * 8;
    s16 z;
    if (count > 0) {
        do {
            out[0] = ((guRandom() & 15) + ((vertices[0] / D_80069930) >> 3)) - 8;
            out[1] = ((guRandom() & 15) + ((vertices[1] / D_80069930) >> 4)) - 8;
            z = vertices[2];
            vertices += 24;
            out += 3;
            out[-1] = ((guRandom() & 15) + ((z / D_80069930) >> 3)) - 8;
        } while ((u32)vertices < (u32)end);
    }
}
