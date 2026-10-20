import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);bs=None
old='visible = 0;\n            if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1;'
for vis,call,order in itertools.product(['if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1; else visible = 0;','visible = ((arg3 >= start && arg3 < end) || arg3 + 360 < end) ? 1 : 0;'],['(u8 *)arg1 + offset','(u8 *)arg1 + offset'],[False,True]):
 v=s.replace(old,vis)
 if order:v=v.replace('offset = 0;\n        cloud = arg1;','cloud = arg1;\n        offset = 0;')
 r=probe.probe(fn,pre+v)
 print(r,vis[:20],order)
 if r<best:best=r;bs=v
if bs:p.write_text(bs)
print('final',best)
