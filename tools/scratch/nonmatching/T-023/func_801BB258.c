/* T-106: 20 differing words, 524/524 bytes. Remaining: scale/shared-x register allocation. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB258;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3C10;
extern u8 D_801F3C14[];
extern u8 D_801F3C18[];

void func_801BB258(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB258 *arg4, s32 arg5)
{
  s32 x1;
  s32 y1;
  s32 *counter;
  s32 y0;
  s32 nextFrame;
  s32 x0;
  x1 = (arg1 * 4) + (((s32) (arg4->scale * 0xC4)) >> 0xA);
  counter = &D_801F3C10;
  x0 = x1;
  y1 = ((arg2 * 4) + (((s32) (((u32) arg4->scale) * 0x153)) >> 0xA)) + (arg4->yOffset * 4);
  y0 = ((arg2 * 4) + (((s32) (arg4->scale * 0xD7)) >> 0xA)) + (arg4->yOffset * 4);
  if (arg5 != 0)
  {
    x1 = 0x9B0 - x1;
    x0 = 0x9B0 - x0;
  }
  func_801BC1B0(arg0, *((s32 *) (D_801F3C14 + ((((s32) (*counter)) / 3) * 8))), 2, 0x2C, 0x20, 0x2C, 0x20, 0, 0, 0x2B, 0x1F, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
  func_801BC1B0(arg0, *((s32 *) (D_801F3C18 + ((((s32) (*counter)) / 3) * 8))), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
  nextFrame = (*counter) + 1;
  *counter = nextFrame;
  if (nextFrame >= 0xC)
  {
    *counter = 0;
  }
}
