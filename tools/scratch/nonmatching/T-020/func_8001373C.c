/* T-133 DRAFT: 28 differing words, 256/256 B in prefix context.
 * Compute the bounded Y impulse before updating the three velocity components. */
typedef struct {
    u8 pad0[0xC];
    f32 x, y, z;
    u8 pad18[0x10];
    s16 vx, vy, vz;
} T020ForceTarget;
extern f32 D_800487F4, D_800487F8;
void func_8001373C(T020ForceTarget *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, u8 arg6)
{
  s16 impulseY;
  f32 dx;
  f32 dy;
  f32 dz;
  dy = arg0->x - arg1;
  dx = dy;
  dy = arg0->y - arg2;
  dz = arg0->z - arg3;
  arg1 = ((dx * dx) + (dy * dy)) + (dz * dz);
  if (arg1 < 50000.0f)
  {
    arg1 = 50000.0f;
  }
  impulseY = (s32) (((f32) (arg5 * 30000)) / arg1);
  arg0->vx = arg0->vx + ((s32) (((f32) (arg4 * 30000)) / arg1));
  arg0->vy = arg0->vy + impulseY;
  arg0->vz = arg0->vz + ((s32) (((f32) (arg6 * 30000)) / arg1));
}
