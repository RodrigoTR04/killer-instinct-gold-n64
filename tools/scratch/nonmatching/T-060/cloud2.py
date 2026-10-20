import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);bs=None
for cmd,order,add in itertools.product([0,1,2],[0,1,2],['(u8 *)arg1 + offset','offset + (u8 *)arg1']):
 v=s.replace('(u8 *)arg1 + offset',add)
 if cmd:
  v=v.replace('typedef struct {','typedef struct { u32 w0,w1; } CloudCmd;\n\ntypedef struct {',1).replace('u32 **','CloudCmd **').replace('u32 *dl;','CloudCmd *dl;').replace('dl + 2','dl + 1').replace('dl[0]','dl->w0').replace('dl[1]','dl->w1')
  if cmd==2:v=v.replace('dl = *arg0;\n    *arg0 = dl + 1;','dl = (*arg0)++;')
 if order==1:v=v.replace('cloud = arg1;\n        offset = 0;','offset = 0;\n        cloud = arg1;')
 if order==2:v=v.replace('i = 0;\n    if (arg2 > 0) {\n        cloud = arg1;\n        offset = 0;','cloud = arg1;\n    i = 0;\n    if (arg2 > 0) {\n        offset = 0;')
 r=probe.probe(fn,pre+v)
 if r<best:best=r;bs=v;print(cmd,order,add,r,flush=True)
if bs:p.write_text(bs)
print('final',best)
