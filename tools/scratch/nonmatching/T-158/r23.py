import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155'); sys.path.insert(0,'/tmp/w')
import lib
from gen23 import make
random.seed(int(sys.argv[1]))
D={'player':'u8 player;','actor':'T032Actor23E *actor;','count':'u8 *count;','old':'s32 old;','position':'T020Position position;','facing':'s32 facing;','x':'u32 x;','y':'u32 y;','point':'T032Point23E *point;'}
def bodies():
    out={}
    for snap in ('none','raw','shift','yraw','xraw'):
      for usepoint in (0,1):
        for oldv in (0,1):
          for inc in range(4):
            for order in ('xyf','yxf','xfy','fxy'):
                L=[]
                X,Y='actor->x >> 4','actor->y >> 4'
                if snap=='raw': L+=['x = actor->x;','y = actor->y;']; X,Y='x >> 4','y >> 4'
                if snap=='shift': L+=['x = actor->x >> 4;','y = actor->y >> 4;']; X,Y='x','y'
                if snap=='yraw': L+=['y = actor->y;']; Y='y >> 4'
                if snap=='xraw': L+=['x = actor->x;']; X='x >> 4'
                idx='old' if oldv else '*count'
                if oldv: L.append('old = *count;')
                if usepoint:
                    L.append(f'point = &D_8004F2D0[player][{idx}];'); t='point->'
                else: t=f'D_8004F2D0[player][{idx}].'
                st={'x':f'{t}x = {X};','y':f'{t}y = {Y};','f':f'{t}facing = facing;'}
                seq=[st[c] for c in order]
                incs='*count = old + 1;' if oldv else '(*count)++;'
                seq=seq[:inc]+[incs]+seq[inc:] if inc<=3 else seq+[incs]
                out[(snap,usepoint,oldv,inc,order)]=(L+seq,snap,usepoint,oldv)
    return out
cands=[]
for k,(body,snap,up,ov) in bodies().items():
    for rep in range(3):
        names=['player','actor','count','position','facing']+(['old'] if ov else [])+(['point'] if up else [])+(['x','y'] if snap in('raw','shift') else [])+(['y'] if snap=='yraw' else [])+(['x'] if snap=='xraw' else [])
        if rep: random.shuffle(names)
        cands.append((k+(rep,),make([D[n] for n in names],body)))
print(len(cands),flush=True)
out=lib.run('func_80023EF0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r23_best.c','w').write(res[0][1][1])
