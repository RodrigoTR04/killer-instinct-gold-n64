import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-060')
import tu,probe
for fn in ['func_801C4E38','func_801B6528','func_801BFB40','func_801B446C']:
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);print(fn,probe.probe(fn,pre+s),flush=True)
 variants=[]
 if fn=='func_801C4E38':
  for typ in ['s32','u32','s16','u16','s8','u8']:
   variants.append((typ,s.replace('u8 arg0, u8 arg1',typ+' arg0, u8 arg1')))
  for typ in ['s32','u32','s16','u16','s8']:
   variants.append(('arg1 '+typ,s.replace('u8 arg1',typ+' arg1')))
 if fn=='func_801B6528':
  for typ in ['T029Card *','const T029Card *','u8 *','s32 *']:
   variants.append((typ,s.replace('void *arg1',typ+'arg1')))
  for decl in ['s32 index;\n    f32 y;','f32 y;\n    s32 index;']:
   variants.append((decl,s.replace('f32 y;\n    s32 index;',decl)))
 if fn=='func_801BFB40':
  variants.append(('arity',s.replace('func_801ADAD4(s32, T023PairB40 *, T023PairB40 *, T023PairB40 *)','func_801ADAD4(s32)').replace('func_801ADAD4(42, &D_802D37E0, &D_802D37F0, &D_80128300)','func_801ADAD4(42)')))
  for a,b in itertools.product([False,True],repeat=2):
   v=s
   if a:v=v.replace('D_802D3820 = 2560;\n    D_802D3824 = 2560;','D_802D3820 = D_802D3824 = 2560;')
   if b:v=v.replace('D_802D37F0.x = D_80128300.x;\n    D_802D37F0.y = D_80128300.y;','D_802D37F0 = D_80128300;')
   variants.append((str((a,b)),v))
 if fn=='func_801B446C':
  s=s.replace('extern s8 D_80127CE8','extern u8 D_80127CE8')
  for typ in ['s32','u32','u8','s8']:
   for pos in ['u8','s32','u32']:
    variants.append((typ+pos,s.replace('s32 flags;',typ+' flags;').replace('u8 pos;',pos+' pos;')))
 best=probe.probe(fn,pre+p.read_text());bs=None
 for label,v in variants:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;bs=v;print('best',label,r,flush=True)
 if bs:p.write_text(bs);print('SAVED',fn,best,flush=True)
