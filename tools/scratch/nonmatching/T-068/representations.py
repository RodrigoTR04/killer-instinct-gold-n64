import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-068')
import probe,tu
from pathlib import Path
for fn in ['func_801C7998','func_801C2D34','func_801C5064']:
 s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 if fn.endswith('7998'):
  for ty in ['u32','s32']:
   for order in [0,1]:
    for expr in ['buttons','buttons & 0xffff','(u32)buttons']:
     init=['key.words.hi = 0;', 'key.words.lo = '+expr+';'];init=init if order==0 else init[::-1]
     v=s.replace('u8 index = 0;', 'union { u64 full; struct { '+ty+' hi, lo; } words; } key;\n    u8 index = 0;\n    '+' '.join(init)).replace('(u64)(buttons & 0xFFFF)','key.full')
     vs.append((str((ty,order,expr)),v))
  for expr in ['(u64)(u32)(buttons & 0xffff) & 0xffffffffULL','(u64)buttons & 0xffffffffULL','(u64)buttons & 0xffffULL','(u64)(buttons | 0U)','(u64)(buttons ^ 0U)']:
   vs.append((expr,s.replace('(u64)(buttons & 0xFFFF)',expr)))
 if fn.endswith('2D34'):
  for a,b in itertools.product(['u32','s32'],['u64','f64']):
   vs.append((a+b,s.replace('u32 w0, w1',a+' w0, w1').replace('u64 full',b+' full')))
  for expr in ['(u32)D_80285168','(u32)&D_80285168[0]','(u32)(D_80285168 + 0)']:
   vs.append((expr,s.replace('(u32)&D_80285168',expr)))
 if fn.endswith('5064'):
  for expr in ['0.0f','(f32)0.0']:
   for depth in ['const f32 depth = D_80294890;','f32 depth = D_80294890;']:
    for zero in ['f32 zero = '+expr+';', 'const f32 zero = '+expr+';']:
     v=s.replace('f32 depth;',zero+' '+depth).replace('depth = D_80294890;\n        do', 'do').replace(', 0.0f,',', zero,')
     vs.append((depth+zero,v))
 for label,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;print(fn,r,label,flush=True);Path('/tmp/'+fn+'-best.c').write_text(v)
