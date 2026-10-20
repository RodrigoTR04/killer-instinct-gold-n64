import sys,re,itertools,json
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
fns=['801B1210','801C7998','801C35D8','801C0610','801BBB60','801C6D40','801C7CD0','801C49A8','801C5064','801C3E40','801C17D0']
results=[]
for addr in fns:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);base=probe.probe(fn,pre+s);variants=[]
 def add(label,v):variants.append((label,v))
 if addr=='801B1210':
  for typ in ['s32','u8','u16']:
   add('alpha '+typ,s.replace('u32 alpha;',typ+' alpha;'))
  add('query prototype','extern s32 func_801AF67C(s32);\n'+s)
  for n in [0,1,2,3]:
   v=s
   if n&1:v=v.replace('g->w0 = 0xBA000402;\n    g->w1 = 0x30;','g->w1 = 0x30;\n    g->w0 = 0xBA000402;')
   if n&2:v=v.replace('g->w1 = 0;\n    g->w0 = 0xB9000002;','g->w0 = 0xB9000002;\n    g->w1 = 0;')
   add('stores '+str(n),v)
 if addr=='801C7998':
  for typ in ['u8','u16','s8','s16','s32','u32']:
   for st in ['switch ((u64)buttons)','{ u64 key = buttons; switch (key)','{ volatile u64 key = buttons; switch (key)']:
    v=s.replace('s32 index = 0;',typ+' index = 0;').replace('switch ((u64)buttons)',st)
    if st.startswith('{'):v=v.replace('return index;','} return index;')
    add(typ+st,v)
 if addr=='801C35D8':
  for typ in ['u8','s8','s32','u32']:
   v=s.replace('s32 visible;',typ+' visible;')
   for call in ['(u8 *)arg1 + offset','cloud']:
    add(typ+call,v.replace('(u8 *)arg1 + offset',call).replace('extern void func_801C3758();','extern void func_801C3758(u32 **, T030Cloud *, s32);'))
  add('branch visibility',s.replace('visible = ((arg3 >= start && arg3 < end) || arg3 + 360 < end);','visible = 0;\n            if (arg3 >= start && arg3 < end) visible = 1;\n            if (arg3 + 360 < end) visible = 1;'))
 if addr=='801C0610':
  for expr in ['D_802CA068','*(s32 *)(D_802C9F70 + 0xF8)']:
   for n in range(4):
    v=s.replace('*(s32 *)(D_802C9F70 + 0xF8)',expr)
    if n&1:v=v.replace('p->w0 = 0xFB000000; p->w1 = 0x0F000410;','p->w1 = 0x0F000410; p->w0 = 0xFB000000;')
    if n&2:v=v.replace('p->w1 = 0x3C010110;\n    p->w0 = 0xFA000000;','p->w0 = 0xFA000000; p->w1 = 0x3C010110;')
    add(expr+str(n),v)
 if addr=='801BBB60':
  for it,jt in itertools.product(['s32','u32','s16','u16'],repeat=2):
   add(it+jt,s.replace('s16 i;',it+' i;').replace('s32 j;',jt+' j;'))
  add('indexed palette',s.replace('do { *palette++ = i++; } while (i < 128);','do { palette[i] = i; i++; } while (i < 128);\n    palette += 128;'))
 if addr=='801C6D40':
  for phase in ['D_802D399C += 1;\n        var_v1 = D_802D399C;','var_v1 = (D_802D399C += 1);']:
   for extra in [True,False]:
    v=s.replace('temp_t7 = D_802D399C + 1;\n        var_v1 = temp_t7 & 0xFF;\n        D_802D399C = temp_t7;',phase)
    if not extra:v=v.replace('&D_8004A258, var_a3','&D_8004A258').replace('func_801C4BD0(0x85, var_a3)','func_801C4BD0(0x85)')
    add(phase+str(extra),v)
 if addr=='801C7CD0':
  for typ in ['s32','u32','u8']:
   for arity in [True,False]:
    v=s.replace('u8 mode;',typ+' mode;')
    if not arity:v=v.replace('extern void func_801ADAD4(s32, s32 *, s32 *, u8 *);','extern void func_801ADAD4(s32);').replace('func_801ADAD4(40, &D_80295700, &D_802956FC, &D_802D3A00)','func_801ADAD4(40)')
    add(typ+str(arity),v)
  add('replay direct',s.replace('replay = D_802D3E15;\n        if (!replay) {\n            D_802D3E15 = 1;\n            replay = 1;\n        }','if (D_802D3E15 == 0) D_802D3E15 = 1;\n        replay = D_802D3E15;'))
 if addr=='801C49A8':
  for typ in ['s32','u32','u8']:
   for temps in [True,False]:
    v=s.replace('u8 temp_v1;',typ+' temp_v1;')
    if not temps:
     for n in [3,4,5,6]:v=v.replace('    T030Cmd49A8 *temp_v0_'+str(n)+';\n','').replace('temp_v0_'+str(n),'temp_v0_2')
    add(typ+str(temps),v)
 if addr=='801C5064':
  for typ in ['u8','s16','s32']:
   for expr in ['((count-i)*67)*scale + origin','origin + ((count-i)*67)*scale','(count-i)*(67.0f*scale) + origin']:
    add(typ+expr,s.replace('s32 count;',typ+' count;').replace('((count-i)*67)*scale + origin',expr))
 if addr=='801C3E40':
  for expr in ['s32 count, index, slot;','s32 count; u8 index, slot;','s32 count, index; u8 slot;']:
   for ptr in [False,True]:
    v=s.replace('s32 count, index, slot;',expr)
    if ptr:
     v=v.replace('s8 dx, dy;','s8 dx, dy;\n    T030Triangle3E40 *triangle;').replace('slot = index & 255;','slot = index & 255;\n                triangle = &D_802D3940[slot];').replace('D_802D3940[slot].','triangle->')
    add(expr+str(ptr),v)
 if addr=='801C17D0':
  v=s.replace('extern u8 D_8004EA9C[], D_80128308[], D_8012830A[], D_80128310[], D_80128328[];','extern u8 D_8004EA9C[];').replace('D_80128328 + player * 11 + character','&D_80128328[player][character]').replace('D_80128310 + player * 11 + character','&D_80128310[player][character]').replace('D_80128310 + player * 11','D_80128310[player]').replace('D_80128328 + player * 11','D_80128328[player]')
  add('TU tables',v)
  for typ in ['u32','s32','u8']:
   for ret in ['return *out != 0;','return D_802D3800[player] != 0;']:
    add(typ+ret,v.replace('u8 player',typ+' player').replace('return *out != 0;',ret))
 best=base;bs=None;bl='';
 for label,v in variants:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;bs=v;bl=label
 if bs:p.write_text(bs)
 print(fn,base,'->',best,bl,len(variants),flush=True);results.append([fn,base,best,bl,len(variants)])
open('tools/scratch/nonmatching/T-060/results.json','w').write(json.dumps(results,indent=2)+'\n')
