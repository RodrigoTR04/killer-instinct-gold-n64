import sys, itertools, re, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
src=open('tools/scratch/nonmatching/T-158/w_2b8c_sib.c').read()
head,rest=src.split("s32 func_801B2B8C",1)
body_start=rest.index("{\n")+2
decl_end=rest.index("    if ((s32) D_801D3088")
sig="s32 func_801B2B8C"+rest[:body_start]
body=rest[decl_end:]
decls=["u8 alpha;","s32 *counter = &D_801D30B8;","s32 *timer = &D_801D30BC;","T025Gfx2B8C *p0, *p1, *p2, *p3, *p4, *p5;","u8 color;","s32 color2;","s32 packed;","u32 value;","u32 primitive;","u8 matrix[64];","f64 phase;","CameraEye eye;"]
random.seed(int(sys.argv[1]))
cands=[]
for _ in range(int(sys.argv[2])):
    o=decls[:]; random.shuffle(o)
    cands.append((o,head+sig+''.join('    '+d+'\n' for d in o)+body))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
from collections import Counter
print(Counter((r[2] if r else None) for r in out))
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999,999))[2]!=184,(t[0] or (999,999))[1]))
for r,(o,s) in res[:6]: print(r,[d.split()[1] if 'T025' not in d else 'ptrs' for d in o])
open('/tmp/w/r2b8c5_best.c','w').write(res[0][1][1])
