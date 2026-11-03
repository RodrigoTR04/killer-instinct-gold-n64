extern s16 D_801D73C8[];
extern u8 D_80047BF0[];
void func_80026738(T032Gfx269AC **dl)
{
  T032Size268 *size;
  T032Gfx269AC *p;
  s32 scale;
  u32 width;
  u8 kind;
  s32 x;
  s32 y;
  s32 i = 0;
  if (D_801D73C8[0] != 0)
  {
    D_8004EA78 = 15;
    while (D_801D73C8[i] != 0)
    {
      kind = D_80047BF0[D_801D73C8[i] - 1];
      scale = (u16) D_801D73C8[i + 1];
      x = ((u16) D_801D73C8[i + 2]) >> 7;
      y = (((u16) D_801D73C8[i + 3]) >> 8) + 4;
      i += 4;
      if (kind >= 19)
      {
        scale = 0x1000;
      }
      size = &D_80061368[kind];
      D_8004CED0[D_8004EA78].halfW = size->halfW;
      D_8004CED0[D_8004EA78].halfH = size->halfH;
      width = size->w;
      D_8004CED0[D_8004EA78].w = width;
      D_8004CED0[D_8004EA78].w2 = width;
      D_8004CED0[D_8004EA78].h = size->h;
      D_8004CED0[D_8004EA78].pixels = (u16 *) D_800612D8[kind];
      p = (*dl)++;
      p->w0 = 0xE7000000;
      p->w1 = 0;
      func_8001EC74(dl, x << 12, y << 12, scale, scale, 8, 0, 0);
    }

  }
}
