typedef struct { s32 image; f32 width; } T023Glyph540;
extern T023Glyph540 D_80282A70[];
extern s32 func_801BDA6C(s32, s32, u8 *, f32, f32, f32, u8, u8, u8, u8, f32);
s32 func_801BE540(s32 list, s32 matrix, u8 *text, f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, u8 a, f32 scale)
{
  f32 width = 0.0f;
  u8 *p;
  s8 index;
  T023Glyph540 *glyph;
  if (*text != 0) {
    p = text;
    do {
      index = *p - 32;
      if ((index < 59) && (index > 0) && ((glyph = &D_80282A70[index]), glyph->image != 0)) {
        width += (10.0f * glyph->width) * scale;
      } else if (index <= 0) {
        width += 15.0 * scale;
      }
      p++;
    } while (*p != 0);
  }
  x -= width;
  return func_801BDA6C(list, matrix, text, x, y, z, r, g, b, a, scale);
}
