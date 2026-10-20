import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
for addr in ['801BFB40','801C35D8','801C17D0','801C7998','801C4E38']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);base=probe.probe(fn,pre+s);vs=[]
 if addr=='801BFB40':
  for types in itertools.product(['s32','u32','f32'],repeat=1):
   vs.append((str(types),s.replace('s32 x, y;',types[0]+' x, y;')))
  # Explicit value temporaries reflect the two original loads before all stores.
  for typ in ['s32','u32']:
   v=s.replace('    D_802D37D0 = -1;',typ+' x, y;\n    D_802D37D0 = -1;').replace('D_802D37F0.x = D_80128300.x;\n    D_802D37F0.y = D_80128300.y;','x = D_80128300.x;\n    y = D_80128300.y;').replace('    D_802D37F8 = 0;','    D_802D37F0.x = x;\n    D_802D37F0.y = y;\n    D_802D37F8 = 0;')
   vs.append(('temps '+typ,v))
 if addr=='801C35D8':
  for n in range(8):
   v=s
   if n&1:v=v.replace('dl[0] = 0x06000000;\n    dl[1] = (u32)D_80290F90;','dl[1] = (u32)D_80290F90;\n    dl[0] = 0x06000000;')
   if n&2:v=v.replace('extern void func_801C3758(u32 **, T030Cloud *, s32);','extern void func_801C3758(u32 **, T030Cloud *, s8);')
   if n&4:v=v.replace('alpha = cloud->alpha;','').replace('cloud->alpha = alpha + 1;','cloud->alpha += 1;').replace('cloud->alpha = alpha - 2;','cloud->alpha -= 2;')
   vs.append((str(n),v))
  for ct in ['u8','s8','s16','s32']:
   vs.append(('visible '+ct,s.replace('s32 visible;',ct+' visible;')))
 if addr=='801C17D0':
  s=s.replace('func_801BEA74(u8, u8, u8,','func_801BEA74(u8, u8, s32,')
  vs.append(('score third arg s32',s))
  for cmp in ['0ULL','(u64)0','0LL']:
   vs.append(('compare '+cmp,s.replace('return *out != 0;',f'return *out != {cmp};')))
  for ct in ['s32','u32','u8']:
   v=s.replace('u8 character = D_8004EA9C[player];',ct+' character = D_8004EA9C[player];')
   vs.append(('char '+ct,v))
  # Compute each table address in its branch, as the original duplicates address arithmetic.
  v=s.replace('    b = &D_80128328[player][character];\n    a = &D_80128310[player][character];','')
  v=v.replace('value = stats[3];','b = &D_80128328[player][character];\n        value = stats[3];').replace('value = stats[4];','b = &D_80128328[player][character];\n        value = stats[4];').replace('value = stats[1];','a = &D_80128310[player][character];\n        value = stats[1];').replace('value = stats[2];','a = &D_80128310[player][character];\n        value = stats[2];')
  vs.append(('branch pointers',v))
 if addr=='801C7998':
  for typ,qual,expr in itertools.product(['u8','u32'],['','volatile '],['(u64)buttons','(s64)buttons','(u64)(u32)buttons']):
   v=s.replace('s32 index = 0;',typ+' index = 0;\n    '+qual+'u64 key;\n    key = '+expr+';').replace('switch ((u64)buttons)','switch (key)')
   vs.append((typ+qual+expr,v))
 if addr=='801C4E38':
  for ret in ['void','s32','u32']:
   for arg in ['u8','s32','u32']:
    v=s.replace('extern void func_80012A8C(u8);',f'extern {ret} func_80012A8C({arg});')
    vs.append((ret+arg,v))
  for decl in ['void','s32']:
   v=s.replace('extern void (*D_800451EC[])(void);',f'extern {decl} (*D_800451EC[])();')
   vs.append(('callback '+decl,v))
 best=base;bs=None;bl=''
 for l,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;bs=v;bl=l
 if bs:p.write_text(bs)
 print(fn,base,best,bl,len(vs),flush=True)
