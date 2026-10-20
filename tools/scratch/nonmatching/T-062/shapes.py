import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
for fn in ['func_801B446C','func_801C4E38','func_801C7CD0']:
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 if fn=='func_801B446C':
  for typ in ['u8','s8','u32','s32']:
   for form in ['struct','array']:
    if form=='struct':
     v='typedef struct { '+typ+' value; } FlagCell;\n'+s.replace('u8 *flagsp = &D_802C8CE0;','FlagCell *flagsp = (FlagCell *)&D_802C8CE0;').replace('*flagsp','flagsp->value').replace('FlagCell flagsp->value','FlagCell *flagsp')
    else:
     v=s.replace('u8 *flagsp = &D_802C8CE0;',typ+' (*flagsp)[1] = ('+typ+' (*)[1])&D_802C8CE0;').replace('flags = *flagsp;','flags = (*flagsp)[0];').replace('*flagsp = flags | bit;','(*flagsp)[0] = flags | bit;')
    vs.append((typ+form,v))
  for init in ['flags = *flagsp;', 'flags = *flagsp; bit = 1 << arg0;', 'flags = D_802C8CE0;']:
   for store in ['*flagsp = flags | bit;','*flagsp = *flagsp | bit;','*flagsp = flags = flags | bit;']:
    for cond in ['if (!(flags & bit))','if ((flags & bit) == 0)','if (!(flags & (1 << arg0)))']:
     vs.append((init+store+cond,s.replace('flags = *flagsp;',init).replace('*flagsp = flags | bit;',store).replace('if (!(flags & bit))',cond)))
 if fn=='func_801C4E38':
  for ty in ['u8','s32','u32','u16','s16']:
   for form in ['array','struct']:
    if form=='array':decl=ty+' modes[2];';x='modes[0]';y='modes[1]'
    else:decl='struct { '+ty+' mode, submode; } modes;';x='modes.mode';y='modes.submode'
    for when in [0,1,2]:
     v=s.replace('        D_802D3985 = arg0;',decl+'\n    '+x+' = arg0;\n    '+y+' = arg1;\n        D_802D3985 = '+x+';')
     if when==0:v=v.replace('D_802D3986 = arg1','D_802D3986 = '+y).replace('if (arg0 >= 11)','if ('+x+' >= 11)').replace('switch (arg0)','switch ('+x+')').replace('if (arg0 == 5)','if ('+x+' == 5)')
     elif when==1:v=v.replace('switch (arg0)','switch ('+x+')').replace('if (arg0 == 5)','if ('+x+' == 5)')
     else:v=v.replace('D_802D3986 = arg1','D_802D3986 = '+y)
     vs.append((ty+form+str(when),v))
 if fn=='func_801C7CD0':
  # Preserve natural local aliases, with each use narrowed only where the byte object requires it.
  for rt in ['s32','u32','u16','s16','u8']:
   for expr in ['D_802D3E15','(u8)D_802D3E15','(u32)D_802D3E15']:
    v=s.replace('u8 replay;',rt+' replay;').replace('replay = D_802D3E15;', 'replay = '+expr+';');vs.append((rt+expr,v))
  for mask in range(8):
   v=s
   for j,symbol in enumerate(['D_802D3A00','D_802D3E15','D_802D3A06']):
    if mask>>j&1:
     v=v.replace('    u8 replay;','    u8 replay;\n    u8 *p'+str(j)+' = &'+symbol+';')
     start=v.index('    if (');v=v[:start]+v[start:].replace(symbol,'*p'+str(j))
   vs.append(('ptrs'+str(mask),v))
 for name,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;p.write_text(v);print(fn,name,r,flush=True)
 print(fn,'final',len(vs),best,flush=True)
