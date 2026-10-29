/* T-136 draft: 43 differing words, 324 bytes in prefix context. */
typedef struct {
    u8 kind;
    u8 pad1[11];
    s32 x;
    u8 pad10[0x44];
    u8 active, pad55, index;
    u8 pad57[0x2D];
    s16 speed;
    u8 pad86[0x7A];
} T033RotatingObject;
typedef struct { f32 pitch, yaw; u8 pad[12]; } T033Rotation;
extern u8 D_8004A9D8;
extern T033RotatingObject D_801D3430[], D_801D5C30[];

void func_80015450(s32 arg0)
{
  T033RotatingObject *new_var;
  u8 *cursor; T033RotatingObject *obj; u8 kind; cursor = (u8 *)D_801D3430; do
  {
    obj = (T033RotatingObject *)cursor; kind = obj->kind;
    if (kind == 0x3B)
    {
      new_var = obj;
      ((T033Rotation *) (&D_8004A9D8))[new_var->index].yaw = ((T033Rotation *) (&D_8004A9D8))[new_var->index].yaw + (new_var->speed / 50.0);
      while (((T033Rotation *) (&D_8004A9D8))[new_var->index].yaw >= 360.0f)
      {
        ((T033Rotation *) (&D_8004A9D8))[new_var->index].yaw -= 360.0f;
      }

      if ((new_var->active != 0) && (((T033Rotation *) (&D_8004A9D8))[new_var->index].pitch < 90.0f))
      {
        ((T033Rotation *) (&D_8004A9D8))[new_var->index].pitch += 2.0f;
      }
      if (new_var->active != 0)
      {
        if (arg0 < new_var->x)
        {
          new_var->x -= 128;
        }
        else
          if (new_var->x < arg0)
        {
          new_var->x = arg0;
        }
      }
    }
    cursor += 0x100;
  }
  while (cursor != (u8 *)D_801D5C30);
}
