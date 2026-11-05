extern s32 D_80285574;
extern s32 D_80285578;
extern FrontendRenderContext D_802C9F70;
extern s32 D_802956F4;
extern s32 D_802D3830;
extern s32 D_802D3834;
extern f32 D_802937B8;
extern f32 D_802937BC;

s32 func_801C317C(FrontendGfxWords **arg0, s32 arg1, s32 arg2, s32 arg3)
{
  u8 *table;
  s32 drawn;
  u8 *entry;
  u8 **slots;
  s32 first;
  s32 y;
  s32 fade;
  s32 index;
  drawn = 0;
  if (arg3 < 0)
  {
    D_80285578 = 0;
    D_802D3830 = 0x1F4;
    D_802D3834 = 0;
  }
  D_802956F4 += func_801BDF94(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *(*((u8 ***) (&D_80285574))), (f32) (((arg1 * (-2)) / 3) - 0x5A), 200.0f, (f32) (arg2 - 0x3E8), 1, 1.0f, (((f32) (arg3 + 0x1E)) / 30.0f) * 360.0f);
  index = D_80285578;
  ;
  slots = ((u8 **) table) + index;
  table = *((u8 **) (&D_80285574));
  entry = *slots;
  if (entry != 0)
  {
    if (arg3 > 0)
    {
      do
      {
        first = index == 0;
      }
      while (0);
      do
      {
        y = 0xB4;
      }
      while (0);
      if (D_802D3830 < arg3)
      {
        D_802D3830 += 0x1F4;
        D_802D3834 = -1;
      }
      fade = D_802D3834;
      if ((fade < 0x100) && (fade >= 0))
      {
        do
        {
          fade += 0x10;
        }
        while (0);
        if (fade >= 0x100)
        {
          fade = 0xFF;
        }
      }
      else
      {
        fade -= 0x10;
        if (fade < (-0xFF))
        {
          D_80285578 = index + 1;
          do
          {
            slots = (((u8 **) table) + index) + 1;
          }
          while (0);
          entry = *slots;
          fade = 0;
        }
      }
      if ((entry == 0) || ((fade < 0) && (slots[1] == 0)))
      {
        if (entry == 0)
        {
          D_80285578 = index - 1;
          do
          {
            entry = ((u8 **) table)[index - 1];
          }
          while (0);
        }
        if (fade == 0)
        {
          fade = -0xFF;
        }
        drawn = 1;
      }
      slots = (u8 **) (entry + (first * 4));
      D_802D3834 = fade;
      while ((*slots) != 0)
      {
        D_802956F4 = func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *slots, D_802937BC, (f32) (y - 5), (f32) (arg2 - 0x5DC), 0, 0, 0, ((s32) (D_802D3834 & 0xFF)) >> 1);
        D_802956F4 += func_801BD640(arg0, (u8 *) ((D_802956F4 << 6) + ((s32) D_802C9F70.matrices)), *((u8 **) (((u8 *) ((u8 **) table)[D_80285578]) + (first * 4))), D_802937B8, (f32) y, (f32) (arg2 - 0x5DC), 0xFF, 0xFF, 0xFF, D_802D3834);
        slots = (u8 **) (((u8 *) slots) + 4);
        y -= 0x37;
      }

    }
  }
  return drawn;
}
