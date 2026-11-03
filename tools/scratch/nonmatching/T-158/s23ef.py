import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
decls={'player':'u8 player;','point':'T032Point23E *point;','actor':'T032Actor23E *actor;','count':'u8 *count;','old':'s32 old;',
'position':'T020Position position;','facing':'s32 facing;','x':'u32 x;','y':'u32 y;'}
pre="""typedef struct { s32 x,y,z; f32 worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T020Position;
typedef struct { u8 kind; u8 pad1[0x23]; u8 facing; u8 pad25[0x43]; u32 x,y; u8 pad70[0x44]; u8 player; u8 tail[0x4B]; } T032Actor23E;
typedef struct { u32 x,y; s8 facing; u8 pad[3]; } T032Point23E;
extern T032Actor23E D_801D5C30[];
extern T032Point23E D_8004F2D0[2][8];
extern u8 D_8004F390[2];
extern void func_8002E08C(T032Actor23E *, void *);
void func_80023EF0(void)
{
"""
F="      if (actor->facing >= 128) facing = 1; else facing = 0;\n"
def body(k):
    b="""  D_8004F390[0] = (D_8004F390[1] = 0);
  actor = (T032Actor23E *)&D_801D3430; do
  {
    if (actor->kind == 31)
    {
      player = actor->player; count = &D_8004F390[player]; if ((*count) >= 8)
      {
        *count = 7;
      }
      func_8002E08C(actor, &position);
"""+F+K[k]+"    }\n    actor++; } while (actor != D_801D5C30);\n}\n"
    return b
K={
'w1':"      x = actor->x; y = actor->y;\n      old = *count;\n      point = &D_8004F2D0[player][old];\n      point->x = x >> 4;\n      point->y = y >> 4;\n      point->facing = facing;\n      *count = old + 1;\n",
'w5':"      x = actor->x; y = actor->y;\n      old = *count;\n      point = &D_8004F2D0[player][old];\n      *count = old + 1;\n      point->x = x >> 4;\n      point->y = y >> 4;\n      point->facing = facing;\n",
'w3':"      x = actor->x; y = actor->y;\n      point = &D_8004F2D0[player][*count];\n      (*count)++;\n      point->x = x >> 4;\n      point->y = y >> 4;\n      point->facing = facing;\n",
'y1':"      y = actor->y;\n      old = *count;\n      point = &D_8004F2D0[player][old];\n      point->x = actor->x >> 4;\n      point->y = y >> 4;\n      point->facing = facing;\n      *count = old + 1;\n",
'y2':"      y = actor->y;\n      point = &D_8004F2D0[player][*count];\n      (*count)++;\n      point->x = actor->x >> 4;\n      point->y = y >> 4;\n      point->facing = facing;\n",
}
res=[]
random.seed(int(sys.argv[1]) if len(sys.argv)>1 else 1)
cands=[]
for k in K:
    names=[n for n in decls if (n not in('x','old') or ('x' in K[k] and n=='x') or ('old' in K[k] and n=='old'))]
    names=[n for n in names if n!='x' or 'x = actor' in K[k]]
    names=[n for n in names if n!='y' or 'y = actor' in K[k]]
    names=[n for n in names if n!='old' or 'old =' in K[k]]
    for _ in range(60):
        o=names[:]; random.shuffle(o); cands.append((k,o))
srcs=[pre+''.join('    '+decls[n]+'\n' for n in o)+body(k) for k,o in cands]
srcs=[s.replace('(T032Actor23E *)&D_801D3430','(T032Actor23E *)&D_801D3430') for s in srcs]
srcs=[open('tools/scratch/nonmatching/T-148/func_80023EF0.c').read().split('void func_80023EF0')[0].replace('typedef','typedef',1)[0:0]+s for s in srcs]
out=lib.run('func_80023EF0',srcs)
best=sorted(zip(out,cands,srcs),key=lambda t:(t[0] or (999,999))[1] if t[0] else 999)
for r,c,s in best[:8]: print(r,c)
open('tools/scratch/nonmatching/T-158/a/best23.c','w').write(best[0][2])
