typedef struct { s32 x,y,z; f32 worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T020Position;
typedef struct { u8 kind; u8 pad1[0x23]; u8 facing; u8 pad25[0x43]; u32 x,y; u8 pad70[0x44]; u8 player; u8 tail[0x4B]; } T032Actor23E;
typedef struct { u32 x,y; s8 facing; u8 pad[3]; } T032Point23E;
extern T032Actor23E D_801D5C30[];
extern T032Point23E D_8004F2D0[2][8];
extern u8 D_8004F390[2];
extern void func_8002E08C(T032Actor23E *, void *);
void func_80023EF0(void)
{
    u8 player;
    T032Actor23E *actor;
    u8 *count;
    s32 old;
    T020Position position;
    s32 facing;
  D_8004F390[0] = (D_8004F390[1] = 0);
  actor = (T032Actor23E *)&D_801D3430; do
  {
    if (actor->kind == 31)
    {
      player = actor->player; count = &D_8004F390[player]; if ((*count) >= 8)
      {
        *count = 7;
      }
      func_8002E08C(actor, &position);
      if (actor->facing >= 128) facing = 1; else facing = 0;
      old = *count;
      D_8004F2D0[player][old].x = actor->x >> 4;
      D_8004F2D0[player][old].y = actor->y >> 4;
      D_8004F2D0[player][old].facing = facing;
      *count = old + 1;
    }
    actor++; } while (actor != D_801D5C30);
}
