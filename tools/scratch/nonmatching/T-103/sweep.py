import sys,json,itertools
from pathlib import Path
sys.path.insert(0,'tools/scratch/nonmatching/T-098')
from harness import compile,source,extent
s=source('func_801B2EF4'); a,b,_=extent(s,'func_801B2EF4'); base=s[a:b]
out=[]; best=19
variants=[]
# Retain statement semantics while exposing counter and flag address lifetimes.
for flag in ['D_801D308C','*flag']:
 for store in ['*counter = arg1;','D_801D30C0 = arg1;']:
  for old in ['alpha','(alpha & 0xFF)','(u8)alpha']:
   for const in ['0xFA000000','primitive']:
    t=base.replace('*counter = arg1;',store).replace('| alpha);','| '+old+');')
    if flag=='*flag':
     t=t.replace('    u8 alpha;','    u8 alpha;\n    u8 *flag = &D_801D308C;').replace('(s32) D_801D308C','(s32) *flag').replace('D_801D308C += 1','*flag += 1')
    if const=='primitive': t=t.replace('    u8 alpha;','    u32 primitive = 0xFA000000;\n    u8 alpha;').replace('->w0 = 0xFA000000','->w0 = primitive')
    variants.append((f'life-{flag}-{store}-{old}-{const}',t))
# Source-line boundaries drive scheduling; search contiguous line joins in both paths and prefix.
lines=base.splitlines()
for start in range(len(lines)):
 for count in [2,3,4,5,8]:
  if start+count<=len(lines): variants.append((f'join-{start}-{count}','\n'.join(lines[:start]+[' '.join(lines[start:start+count])]+lines[start+count:])))
# Local declaration order can alter graph traversal and stale byte allocation.
items=['    u8 alpha;','    s32 *counter = &D_801D30C0;','    T025Gfx2EF4 *p0, *p1, *p2, *p3;','    u8 color;','    s32 color2;','    s32 packed;','    u32 value;']
for i in range(len(items)):
 for j in range(len(items)):
  order=items.copy(); x=order.pop(i);order.insert(j,x)
  variants.append((f'decl-{i}-{j}',base.replace('\n'.join(items),'\n'.join(order))))
for label,t in variants:
 r=compile('func_801B2EF4',s[:a]+t+s[b:],label)
 out.append(r)
 if r.get('words',999)<best:
  best=r['words'];Path('/tmp/kig-t103-best.c').write_text(s[:a]+t+s[b:]);Path('/tmp/kig-t103-best-body.c').write_text(t);print(label,best,flush=True)
Path('tools/scratch/nonmatching/T-103/sweep.json').write_text(json.dumps(out,indent=2)+'\n')
print('done',len(out),best,flush=True)
