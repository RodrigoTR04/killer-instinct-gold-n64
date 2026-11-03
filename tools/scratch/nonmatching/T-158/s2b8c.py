import sys, random, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
src=open('tools/scratch/nonmatching/T-025/func_801B2B8C.c').read()
old="""    u8 alpha;
AnimationState *state = &D_801D30B8; u8 matrix[64];
    u32 value; T025Gfx2B8C *p1;
    u8 color;
    T025Gfx2B8C *p0;
    f64 phase; CameraEye eye;
"""
assert old in src
decls=['u8 alpha;','AnimationState *state = &D_801D30B8;','u8 matrix[64];','u32 value;','T025Gfx2B8C *p1;','u8 color;','T025Gfx2B8C *p0;','f64 phase;','CameraEye eye;']
random.seed(int(sys.argv[1]))
cands=[]
for _ in range(int(sys.argv[2])):
    o=decls[:]; random.shuffle(o)
    cands.append((o,src.replace(old,'    '+'\n    '.join(o)+'\n')))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])
for r,(o,s) in res[:5]: print(r,o)
from collections import Counter
print(Counter(r[1] if r else None for r in out).most_common(8))
open('tools/scratch/nonmatching/T-158/best2b8c.c','w').write(res[0][1][1])
