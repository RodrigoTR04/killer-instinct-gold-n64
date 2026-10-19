/* DRAFT. Remaining diff: Font traversal, float registers, call arguments and scheduling differ. */
typedef struct { s32 image; f32 width; } T023Glyph660;
extern T023Glyph660 D_80282C48[];
extern f64 D_80292B88;
extern s32 func_801BDF94(s32, s32, u8 *, f32, f32, f32, s32, f32, f32);
s32 func_801BE660(s32 list, s32 matrix, u8 *text, f32 x, f32 y, f32 z, f32 scale) {
    f32 width = 0.0f;
    u8 *p = text;
    s8 index;
    T023Glyph660 *glyph;
    if (*text) {
        do {
            index = *p - 'A';
            if (index == -19) index = 26;
            if (index < 27 && index >= 0 && (glyph = &D_80282C48[index], glyph->image != 0)) {
                width += 19.0f * glyph->width * scale;
            } else if (index < 0) {
                width = (f64)width + D_80292B88 * (f64)scale;
            }
            p++;
        } while (*p);
    }
    x -= width / 2.0f;
    return func_801BDF94(list, matrix, text, x, y, z, 0, scale, 0.0f);
}
