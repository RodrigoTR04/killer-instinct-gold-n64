import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);bs=None
for store,init,expr in itertools.product([0,1],[0,1,2],['(u8 *)arg1 + offset','(T030Cloud *)(offset + (u32)arg1)','(T030Cloud *)((u32)arg1 + offset)']):
 v=s.replace('(u8 *)arg1 + offset',expr)
 if store:v=v.replace('dl->w0 = 0x06000000;\n    dl->w1 = (u32)D_80290F90;','dl->w1 = (u32)D_80290F90;\n    dl->w0 = 0x06000000;')
 if init==1:v=v.replace('cloud = arg1;\n        offset = 0;','offset = 0;\n        cloud = arg1;')
 if init==2:v=v.replace('i = 0;\n    if (arg2 > 0) {\n        cloud = arg1;\n        offset = 0;','i = 0;\n    offset = 0;\n    if (arg2 > 0) {\n        cloud = arg1;')
 r=probe.probe(fn,pre+v)
 if r<best:best=r;bs=v;print(store,init,expr,r,flush=True)
if bs:p.write_text(bs)
print('final',best)
