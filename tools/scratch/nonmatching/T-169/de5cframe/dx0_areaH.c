extern s32 D_8004EA78;
extern s32 D_8004F2C8;
extern s32 D_8004F2CC;
void func_80031050(u8 *, s32, s32);
void func_80031DD0(u8 *, s32, s32);

void func_8001DE5C(u8 *arg0, u8 *arg1, u8 arg2)
{
  s32 x = (arg0[1] << 8) + arg0[0];
  s32 y = (arg0[3] << 8) + arg0[2];
  s32 x2 = (arg0[5] << 8) + arg0[4];
  s32 y2 = (arg0[7] << 8) + arg0[6];
  s32 bx;
  s32 by;
  s32 bx2;
  s32 by2;
  s32 mx;
  s32 my;
  s32 dx;
  s32 dy;
  s32 dyb;
  s32 spanX;
  s32 spanY;
  s32 rx;
  s32 ry;
  u32 areaW;
  T022Sprite *sprite;
  if (arg1 != 0)
  {
    bx = (arg1[1] << 8) + arg1[0];
    by = (arg1[3] << 8) + arg1[2];
    bx2 = (arg1[5] << 8) + arg1[4];
    by2 = (arg1[7] << 8) + arg1[6];
  }
  if (x >= 0x8000)
  {
    x -= 0x10000;
  }
  if (bx >= 0x8000)
  {
    bx -= 0x10000;
  }
  bx -= 1;
  if (y >= 0x8000)
  {
    do
    {
      y -= 0x10000;
    }
    while (0);
  }
  if (by >= 0x8000)
  {
    by -= 0x10000;
  }
  mx = x;
  my = y;
  if (arg1 != 0)
  {
    if (bx >= x)
    {
      mx = bx;
    }
    if (by >= y)
    {
      my = by;
    }
  }
  dx = mx - (u16) bx;
  spanX = bx2 + dx;
  dy = my - y;
  dyb = my - by;
  x2 += (mx - x);
  y2 += dy;
  spanY = by2 + dyb;
  do
  {
    rx = x2;
  }
  while (0);
  ry = y2;
  if (arg1 != 0)
  {
    if (spanX >= x2)
    {
      rx = spanX;
    }
    if (spanY >= y2)
    {
      ry = spanY;
    }
  }
  areaW = (rx + 9) & 0xFFF8;
  if (((s32) (areaW * ((ry + 1) & 0xFFFE))) < 0x8891)
  {
    sprite = &D_8004CED0[D_8004EA78];
    do
    {
      sprite->halfWidth = mx;
    }
    while (0);
    sprite->halfHeight = my;
    sprite->width = x2;
    sprite->height = ry;
    sprite->width2 = areaW;
    ((s16 *) sprite)[10] = rx;
    ((s16 *) sprite)[11] = ry;
    ((s16 *) sprite)[13] = arg2;
    func_80031050(arg0, (mx - x), ((ry - y2) << 16) | dy);
    D_8004F2C8 = D_8004F2CC;
    if (arg1 != 0)
    {
      func_80031DD0(arg1, dx, ((ry - ry) << 16) | dyb);
    }
  }
}
