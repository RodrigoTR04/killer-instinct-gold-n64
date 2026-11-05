typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023StateBADEC;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3AA0;
extern s32 D_801F3AA4;
extern u8 D_801F3AA8[];

void func_801BADEC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023StateBADEC *arg4, s32 arg5)
{
  s32 x;
  s32 *counter0;
  s32 temp_v0_2;
  s32 y0;
  s32 *counter1;
  s32 temp_v0_3;
  s32 scale = arg4->scale;
  s32 y1;
  counter0 = &D_801F3AA0;
  counter1 = &D_801F3AA4;
  x = (arg1 * 4) + (((s32) ((0x1CD - (arg5 * 4)) * scale)) >> 0xA);
  y0 = ((arg2 * 4) + (((s32) (scale * 0x198)) >> 0xA)) + (arg4->yOffset * 4);
  y1 = ((arg2 * 4) + (((s32) (scale * 0x1E3)) >> 0xA)) + (arg4->yOffset * 4);
  if (arg5 != 0)
  {
    x = 0x9B0 - x;
  }
  temp_v0_2 = (*counter0) + 1;
  *counter0 = temp_v0_2;
  if (temp_v0_2 >= 0x15)
  {
    if (temp_v0_2 >= 0x27)
    {
      D_801F3AA0 = temp_v0_2;
      *counter0 = 0;
    }
    else
    {
      func_801BC1B0(arg0, *((s32 *) (D_801F3AA8 + ((((s32) (temp_v0_2 - 0x15)) >> 1) * 4))), 2, 0x2C, 0x12, 0x2C, 0x12, 0, 0, 0x2B, 0x11, (f32) x, (f32) y0, scale, arg5);
    }
  }
  temp_v0_3 = (*counter1) + 1;
  *counter1 = temp_v0_3;
  if (temp_v0_3 >= 0x1C)
  {
    D_801F3AA4 = temp_v0_3;
    if (temp_v0_3 >= 0x2E)
    {
      *counter1 = 0;
      return;
    }
    D_801F3AA4 = temp_v0_3;
    func_801BC1B0(arg0, (*((s32 *) (D_801F3AA8 + ((((s32) (temp_v0_3 - 0x1C)) >> 1) * 4)))) + 0x318, 2, 0x2C, 0x1A, 0x2C, 0x1A, 0, 0, 0x2B, 0x19, (f32) x, (f32) y1, scale, arg5);
  }
}
