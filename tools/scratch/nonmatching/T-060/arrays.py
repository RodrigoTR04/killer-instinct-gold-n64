import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-060');import tu,probe
fn='func_801BFB40';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);bs=None
for arrays in itertools.product([False,True],repeat=4):
 v=s
 names=['D_80128300','D_802D37D8','D_802D37E0','D_802D37F0']
 v=v.replace('extern T023PairB40 D_80128300, D_802D37D8, D_802D37E0, D_802D37F0;','\n'.join('extern '+('s32 '+n+'[2];' if a else 'T023PairB40 '+n+';') for n,a in zip(names,arrays)))
 for n,a in zip(names,arrays):
  if a:v=v.replace(n+'.x',n+'[0]').replace(n+'.y',n+'[1]').replace('&'+n,'(T023PairB40 *)'+n)
 r=probe.probe(fn,pre+v)
 if r<best:best=r;bs=v;print(arrays,r,flush=True)
if bs:p.write_text(bs)
print('final',best)
