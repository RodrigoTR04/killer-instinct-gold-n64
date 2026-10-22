/* T-052 DRAFT: 67 relocation-masked positional words differ; 296/312 bytes. */
typedef struct { u8 pad[12]; f32 x,y,z; } T020Position;
typedef struct { u8 kind; u8 pad1[0x23]; u8 facing; u8 pad25[0x43]; u32 x,y; u8 pad70[0x44]; u8 player; u8 tail[0x4B]; } T032Actor23E;
typedef struct { u32 x,y; s8 facing; u8 pad[3]; } T032Point23E;
extern T032Actor23E D_801D3430[], D_801D5C30[];
extern T032Point23E D_8004F2D0[2][8];
extern u8 D_8004F390[2];
extern void func_8002E08C(T032Actor23E *, void *);
void func_80023EF0(void)
{
  T020Position position;
  T032Actor23E *actor;
  u8 player;
  unsigned int new_var2;
  u8 *count;
  u8 *new_var;
  u8 old;
  T032Point23E *point;
  s8 facing;
  D_8004F390[0] = (D_8004F390[1] = 0);
  for (actor = D_801D3430; actor != D_801D5C30; actor++)
  {
    if (actor->kind == 31)
    {
      player = actor->player;
      count = &D_8004F390[player];
      if ((*count) >= 8)
      {
        *count = 7;
      }
      func_8002E08C(actor, &position);
      new_var = count;
      new_var2 = actor->facing;
      facing = new_var2 >= 128;
      old = (*new_var)++;
      point = &D_8004F2D0[player][old];
      point->x = actor->x >> 4;
      point->y = actor->y >> 4;
      point->facing = facing;
    }
  }

}
