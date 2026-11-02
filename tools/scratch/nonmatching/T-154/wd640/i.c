typedef struct { u32 w0, w1; } T154Gfx;
typedef union { u64 align; u8 bytes[64]; } T154Mtx;
typedef struct { u32 image; f32 width; } T154Glyph;
extern void guScale(void *, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern T154Glyph D_80282A70[];

s32 func_801BD640(T154Gfx **dl, T154Mtx *matrices, u8 *text, f32 x, f32 y, f32 z,
                  u8 r, u8 g, u8 b, u8 a)
{
  T154Glyph *glyph;
  f32 pos = x;
  s32 count;
  s32 mode = 0;
  u8 *p;
  u8 index;
  u8 alpha = a;
  f64 width;
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0xE7000000;
  cmd->w1 = 0;
  }
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0xFA000000;
  cmd->w1 = (r << 24) | (g << 16) | (b << 8) | alpha;
  }
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w1 = 0xFFFDF6FB; cmd->w0 = 0xFCFFFFFF;
  }
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w1 = 0x20000;
  cmd->w0 = 0xB6000000;
  }
  if (alpha == 0xFF) {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0xB900031D; cmd->w1 = 0x552048;
  }
  else {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0xB900031D; cmd->w1 = 0x5041C8;
  }
  guScale(matrices, 0.75f, 0.75f, 1.0f);
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0x01020040;
  cmd->w1 = (u32)matrices;
  }
  count = 1;
  for (p = text; *p; p++) {
  index = *p - 0x20;
  if (index < 59 && index > 0 && (glyph = &D_80282A70[index])->image) {
  if (mode) width = mode * 5.0;
  else width = glyph->width * 10.0f;
  pos = pos + width;
  guTranslate(&matrices[count], pos, y, z);
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w1 = (u32)&matrices[count];
  cmd->w0 = 0x01040040;
  }
  {
  T154Gfx *cmd = (*dl)++;
  cmd->w0 = 0x06000000;
  cmd->w1 = glyph->image;
  }
  {
  T154Gfx *cmd = (*dl)++;
  count++;
  cmd->w0 = 0xBD000000;
  cmd->w1 = 0;
  }
  if (mode) width = 25.0;
  else width = glyph->width * 10.0f;
  pos = pos + width;
  }
  else if (*p == 9) {
  pos = x + ((s32)(f32)((pos - x) / 400.0) * 20 + 20) * 2.5 * 8.0;
  }
  else if (*p == 0x6A) {
  mode = 5;
  }
  else if (*p == 0x6B) {
  mode = 2;
  }
  else {
  if (mode) width = 50.0;
  else width = 30.0;
  pos = pos + width;
  }
  }
  return count;
}
