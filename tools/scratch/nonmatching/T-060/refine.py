import sys,re,itertools,json
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
for addr in ['801C4E38','801B6528','801BFB40','801B446C','801C35D8','801C6D40','801C17D0']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);base=probe.probe(fn,pre+s);vs=[]
 def add(l,v):vs.append((l,v))
 if addr=='801C4E38':
  add('K&R',s.replace('void func_801C4E38(u8 arg0, u8 arg1) {','void func_801C4E38(arg0, arg1)\nu8 arg0, arg1;\n{'))
  for typ in ['u8','u32','s32','u16']:
   for init in ['arg0','D_802D3985']:
    v=s.replace('        D_802D3985 = arg0;',typ+' mode;\n    D_802D3985 = arg0;\n    mode = '+init+';')
    start=v.index('    if (arg0 >= 11)');v=v[:start]+v[start:].replace('arg0','mode')
    add(typ+init,v)
  for decl in ['u8','u16','s32','u32']:
   v=s.replace('        D_802D3985 = arg0;',decl+' mode = arg0;\n        D_802D3985 = arg0;').replace('switch (arg0)','switch (mode)').replace('if (arg0 == 5)','if (mode == 5)')
   add('switch cache '+decl,v)
 if addr=='801B6528':
  for typ in ['s32','u32','u8','s16']:
   add('index '+typ,s.replace('s32 index;',typ+' index;'))
  for name in ['card','item']:
   v=s.replace('s32 index;','s32 index;\n    T029Card *'+name+' = arg1;').replace('((T029Card *)arg1)->index',name+'->index')
   add(name,v)
  for expr in ['command = (*arg0)++;','command = *arg0; ++*arg0;']:
   add(expr,s.replace('command = *arg0; *arg0 = command + 1;',expr))
  add('K&R',s.replace('s32 func_801B6528(T029Gfx801B6528 **arg0, void *arg1, void *arg2, s32 arg3) {','s32 func_801B6528(arg0,arg1,arg2,arg3)\nT029Gfx801B6528 **arg0; void *arg1,*arg2; s32 arg3;\n{'))
 if addr=='801BFB40':
  for ea in ['D_802D37EA[1] = D_802D37EA[0] = 0;','D_802D37EA[0] = D_802D37EA[1] = 0;']:
   for x,y in itertools.product(['x','y'],repeat=2):
    v=s.replace('D_802D37EA[1] = 0;\n    D_802D37EA[0] = 0;',ea)
    v=v.replace('D_802D37D8.x = D_802D37D8.y = 40;',f'D_802D37D8.{x} = D_802D37D8.{"y" if x=="x" else "x"} = 40;').replace('D_802D37E0.x = D_802D37E0.y = 32;',f'D_802D37E0.{y} = D_802D37E0.{"y" if y=="x" else "x"} = 32;')
    add(ea+x+y,v)
  for pos in [0,1,2,3,4]:
   lines=['D_802D37EA[1] = 0;\n    D_802D37EA[0] = 0;','D_802D37D8.x = D_802D37D8.y = 40;','D_802D37E0.x = D_802D37E0.y = 32;','D_802D37F0.x = D_80128300.x;\n    D_802D37F0.y = D_80128300.y;']
   copy=lines.pop();lines.insert(pos,copy)
   a=s.index('    D_802D37EA[1]');b=s.index('    D_802D37F8 =')
   add('copy pos '+str(pos),s[:a]+'    '+'\n    '.join(lines)+'\n'+s[b:])
 if addr=='801B446C':
  for bt,pt,ct in itertools.product(['s32','u32','u8'],['u8','u32'],['s32','u8']):
   v=s.replace('s32 bit;',bt+' bit;').replace('u8 pos;',pt+' pos;').replace('s32 choice;',ct+' choice;').replace('extern s8 D_80127CE8','extern u8 D_80127CE8')
   add(bt+pt+ct,v)
  add('direct flags',s.replace('flags = *flagsp;','flags = D_802C8CE0;').replace('*flagsp = flags | bit;','D_802C8CE0 = flags | bit;'))
 if addr=='801C35D8':
  for typ in ['s32','u8','s8']:
   for cond in ['visible = 0;\n            if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1;','if (arg3 >= start && arg3 < end) visible = 1;\n            else if (arg3 + 360 < end) visible = 1;\n            else visible = 0;','visible = 0;\n            if (arg3 >= start && arg3 < end) visible = 1;\n            if (arg3 + 360 < end) visible = 1;']:
    v=s.replace('s8 visible;',typ+' visible;').replace('visible = ((arg3 >= start && arg3 < end) || arg3 + 360 < end);',cond)
    add(typ+cond,v)
 if addr=='801C6D40':
  for decl in ['s32','u32','u8']:
   for phase in ['var_v1 = (D_802D399C += 1);','D_802D399C++;\n        var_v1 = D_802D399C;']:
    v=s.replace('s32 var_v1;',decl+' var_v1;').replace('temp_t7 = D_802D399C + 1;\n        var_v1 = temp_t7 & 0xFF;\n        D_802D399C = temp_t7;',phase)
    v=v.replace('func_801C4BD0(0x85, var_a3)','func_801C4BD0(0x85)').replace('&D_8004A258, var_a3','&D_8004A258')
    add(decl+phase,v)
 if addr=='801C17D0':
  for typ in ['s32','u32','u8']:
   for out in [True,False]:
    v=s.replace('u32 value;',typ+' value;')
    if not out:v=v.replace('    out = &D_802D3800[player];','').replace('*out','D_802D3800[player]')
    add(typ+str(out),v)
 best=base;bs=None;bl=''
 for l,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;bs=v;bl=l
 if bs:p.write_text(bs)
 print(fn,base,best,bl,len(vs),flush=True)
