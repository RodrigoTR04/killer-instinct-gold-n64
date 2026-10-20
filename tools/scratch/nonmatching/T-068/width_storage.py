import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-068')
import probe,tu
from pathlib import Path
for fn in ['func_801C7998','func_801C5064','func_801C6A80','func_801C2D34']:
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s); vs=[]
 if fn.endswith('7998'):
  for ty in ['u64','s64']:
   for expr in ['(u32)buttons','buttons & 0xFFFFU','(u64)buttons & 0xFFFFULL','(u64)(u32)buttons & 0xFFFFULL','(u64)buttons & (u64)0xFFFF','(u64)(buttons & 0xFFFF) + 0ULL']:
    vs.append((ty+expr,s.replace('switch ((u64)(buttons & 0xFFFF))','switch (('+ty+')('+expr+'))')))
 if fn.endswith('5064'):
  for init in ['zero = 0.0f; depth = D_80294890;','depth = D_80294890; zero = 0.0f;']:
   for decl in ['f32 zero;','f32 zero = 0.0f;']:
    for place in ['depth = D_80294890;','scale = D_8029488C;']:
     v=s.replace('f32 depth;','f32 depth; '+decl).replace(place,init + (' scale = D_8029488C;' if place.startswith('scale') else '')).replace(', 0.0f,',', zero,')
     vs.append((init+decl+place,v))
  for exp in ['D_80294890','(depth = D_80294890)','depth + 0.0f']:
   vs.append((exp,s.replace(', depth,',', '+exp+',')))
 if fn.endswith('6A80'):
  for load,store in itertools.product(['D_802D3984','*(volatile u8 *)&D_802D3984','*(u8 *)(u32)&D_802D3984'], ['D_802D3984 = 1','D_802D3984++','D_802D3984 = temp_v0 + 1','*(volatile u8 *)&D_802D3984 = 1']):
   v=s.replace('if (D_802D3984 == 0)', 'if ('+load+' == 0)').replace('D_802D3984 += 1',store)
   if 'temp_v0 + 1' in store: continue
   vs.append((load+store,v))
 if fn.endswith('2D34'):
  for ty in ['u32','s32','u64','void *']:
   vs.append((ty,s.replace('extern u8 D_80285168[];', 'extern '+ty+' D_80285168[];')))
  for n in [0,6]:
   name='temp_v0' if n==0 else 'temp_v0_7'
   val='0xBA00130100080000ULL' if n==0 else '((u64)0x06000000 << 32) | (u32)&D_80285168'
   a= name+'->words.w0 = '+('0xBA001301;' if n==0 else '0x06000000;')
   b= name+'->words.w1 = '+('0x80000;' if n==0 else '(u32)&D_80285168;')
   vs.append((name,s.replace(a+'\n    '+b,name+'->full = '+val+';')))
 for label,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r; print(fn,r,label,flush=True);Path('/tmp/'+fn+'-best.c').write_text(v)
