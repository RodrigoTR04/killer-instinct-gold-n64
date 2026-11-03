import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre=open('tools/scratch/nonmatching/T-158/s23ef.py').read().split('decls=')[0]  # unused
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
# statement variants; letters: x,y snapshot or not; old or not; point or not; facing pre or inline
def stm(xs, ys, old, pt, order):
    L=[]
    if xs: L.append("x = actor->x;")
    if ys: L.append("y = actor->y;")
    idx = "old" if old else "*count"
    if old: L.append("old = *count;")
    X = "x" if xs else "actor->x"
    Y = "y" if ys else "actor->y"
    if pt:
        L.append(f"point = &D_8004F2D0[player][{idx}];")
        t="point->"
    else:
        t=f"D_8004F2D0[player][{idx}]."
    st={'x':f"{t}x = {X} >> 4;",'y':f"{t}y = {Y} >> 4;",'f':f"{t}facing = facing;"}
    inc = "*count = old + 1;" if old else "(*count)++;"
    seq=[st[c] for c in order]
    return L, seq, inc
def build(xs,ys,old,pt,order,incpos,decl_names):
    L,seq,inc=stm(xs,ys,old,pt,order)
    body=L+(seq[:incpos]+[inc]+seq[incpos:])
    D={'player':'u8 player;','point':'T032Point23E *point;','actor':'T032Actor23E *actor;','count':'u8 *count;','old':'s32 old;','position':'T020Position position;','facing':'s32 facing;','x':'u32 x;','y':'u32 y;'}
    names=[n for n in decl_names if (n=='old' and old) or (n=='point' and pt) or (n=='x' and xs) or (n=='y' and ys) or n in('player','actor','count','position','facing')]
    s=pre+''.join('    '+D[n]+'\n' for n in names)
    s+="""  D_8004F390[0] = (D_8004F390[1] = 0);
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
"""
    s+=''.join('      '+l+'\n' for l in body)
    s+="    }\n    actor++; } while (actor != D_801D5C30);\n}\n"
    return s
base_decl=['player','point','actor','count','old','position','facing','x','y']
cands=[]
random.seed(7)
for xs in (0,1):
 for ys in (0,1):
  for old in (0,1):
   for pt in (0,1):
    for order in ('xyf','yxf','xfy','fxy','yfx','fyx'):
     for incpos in range(4):
      for rep in range(3):
        dn=base_decl[:]
        if rep: random.shuffle(dn)
        cands.append(((xs,ys,old,pt,order,incpos),build(xs,ys,old,pt,order,incpos,dn)))
print(len(cands))
out=lib.run('func_80023EF0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[0],(t[0] or (999,999))[1]))
for r,(k,s) in res[:12]: print(r,k)
open('tools/scratch/nonmatching/T-158/a/bestg.c','w').write(res[0][1][1])
