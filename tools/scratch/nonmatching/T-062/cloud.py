import sys,itertools,json
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
init='    i = 0;\n    if (arg2 > 0) {\n        cloud = arg1;\n        offset = 0;'
initvars=[]
for perm in itertools.permutations(['i = 0;','cloud = arg1;','offset = 0;']):
 for k in range(4):
  initvars.append('\n'.join('    '+x for x in perm[:k])+'\n    if (arg2 > 0) {\n'+'\n'.join('        '+x for x in perm[k:]))
args=['(u8 *)arg1 + offset','offset + (u8 *)arg1','(T030Cloud *)(offset + (u32)arg1)','(T030Cloud *)((u32)arg1 + offset)','(T030Cloud *)((s32)offset + (s32)arg1)','(T030Cloud *)((u32)offset + (u32)arg1)','(T030Cloud *)((u32)offset + (u8 *)arg1)']
for iv,add,typ in itertools.product(initvars,args,['s32','u32']):
 v=s.replace(init,iv).replace('(u8 *)arg1 + offset',add).replace('s32 i, offset;','s32 i; '+typ+' offset;')
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,'init/add/type',r,iv,add,typ,flush=True)
print('phase1',n,best,flush=True)
s=p.read_text()
old='    dl = (*arg0)++;\n    dl->w0 = 0x06000000;\n    dl->w1 = (u32)D_80290F90;'
for order in itertools.permutations(['dl = (*arg0)++;','dl->w0 = 0x06000000;','dl->w1 = (u32)D_80290F90;']):
 if order[0]!='dl = (*arg0)++;':continue
 for decl in ['extern u32 D_80290F90[];','extern u8 D_80290F90[];','extern CloudCmd D_80290F90[];']:
  for form in ['(u32)D_80290F90','(u32)&D_80290F90[0]']:
   v=s.replace(old,'    '+'\n    '.join(order)).replace('extern u32 D_80290F90[];',decl).replace('(u32)D_80290F90',form)
   r=probe.probe(fn,pre+v);n+=1
   if r<best:best=r;p.write_text(v);print(n,'command',r,flush=True)
# Introduce meaningful command fields as locals in every declaration and assignment order.
for typ in ['u32','s32','CloudCmd *','void *']:
 for before in [True,False]:
  for order in itertools.permutations(['dl = (*arg0)++;','op = 0x06000000;','list = '+('D_80290F90;' if '*' in typ else '(u32)D_80290F90;')]):
   v=s.replace('CloudCmd *dl;','CloudCmd *dl;\n    u32 op;\n    '+typ+' list;').replace(old,'    '+'\n    '.join(order)+'\n    dl->w0 = op;\n    dl->w1 = (u32)list;')
   r=probe.probe(fn,pre+v);n+=1
   if r<best:best=r;p.write_text(v);print(n,'locals',r,typ,order,flush=True)
print('final',n,best)
