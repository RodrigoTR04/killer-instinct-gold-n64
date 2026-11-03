import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre=open('tools/scratch/nonmatching/T-158/s23eg.py').read().split('pre="""')[1].split('"""')[0]
pre='"""'.join([pre]) 
pre=pre
hdr="""  D_8004F390[0] = (D_8004F390[1] = 0);
  actor = (T032Actor23E *)&D_801D3430; do
  {
    if (actor->kind == 31)
    {
      player = actor->player; count = &D_8004F390[player]; if ((*count) >= 8)
      {
        *count = 7;
      }
      func_8002E08C(actor, &position);
"""
tail="    }\n    actor++; } while (actor != D_801D5C30);\n}\n"
FAC={'if':"      if (actor->facing >= 128) facing = 1; else facing = 0;\n",
     'tern':"      facing = actor->facing >= 128 ? 1 : 0;\n",
     'cmp':"      facing = actor->facing >= 128;\n"}
BODY={
'b1':"      x = actor->x; y = actor->y; old = *count;\n      D_8004F2D0[player][old].x = x >> 4;\n      *count = old + 1;\n      D_8004F2D0[player][old].y = y >> 4;\n      D_8004F2D0[player][old].facing = facing;\n",
'b2':"      x = actor->x; y = actor->y; old = *count;\n      D_8004F2D0[player][old].x = x >> 4;\n      D_8004F2D0[player][old].y = y >> 4;\n      D_8004F2D0[player][old].facing = facing;\n      *count = old + 1;\n",
'b3':"      old = *count; x = actor->x; y = actor->y;\n      D_8004F2D0[player][old].x = x >> 4;\n      *count = old + 1;\n      D_8004F2D0[player][old].y = y >> 4;\n      D_8004F2D0[player][old].facing = facing;\n",
'b4':"      x = actor->x >> 4; y = actor->y >> 4; old = *count;\n      D_8004F2D0[player][old].x = x;\n      *count = old + 1;\n      D_8004F2D0[player][old].y = y;\n      D_8004F2D0[player][old].facing = facing;\n",
'b5':"      old = *count; x = actor->x; y = actor->y; *count = old + 1;\n      D_8004F2D0[player][old].x = x >> 4;\n      D_8004F2D0[player][old].y = y >> 4;\n      D_8004F2D0[player][old].facing = facing;\n",
}
random.seed(int(sys.argv[1]))
D={'player':'u8 player;','actor':'T032Actor23E *actor;','count':'u8 *count;','old':'s32 old;','position':'T020Position position;','facing':'s32 facing;'}
cands=[]
for fk in FAC:
 for bk in BODY:
  for xt in ('u32','s32'):
   for ft in ('s32','u8','u32'):
    for rep in range(12):
        names=list(D)+['x','y']
        if rep: random.shuffle(names)
        dd=dict(D); dd['x']=f'{xt} x;'; dd['y']=f'{xt} y;'; dd['facing']=f'{ft} facing;'
        s=pre+''.join('    '+dd[n]+'\n' for n in names)+hdr+FAC[fk]+BODY[bk]+tail
        cands.append(((fk,bk,xt,ft,tuple(names)),s))
print(len(cands))
out=lib.run('func_80023EF0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[0],(t[0] or (999,999))[1]))
for r,(k,s) in res[:10]: print(r,k)
open('tools/scratch/nonmatching/T-158/a/besth.c','w').write(res[0][1][1])
