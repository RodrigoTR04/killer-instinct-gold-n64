import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801BFB40';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
start=s.index('    D_802D37F0.x');end=s.index('    D_802D37F8 =')
for byte,aa,bb in itertools.product(['D_802D37EA[1] = 0;\n    D_802D37EA[0] = 0;','D_802D37EA[0] = D_802D37EA[1] = 0;','D_802D37EA[1] = D_802D37EA[0] = 0;','D_802D37EA[0] = 0;\n    D_802D37EA[1] = 0;'],range(4),range(4)):
 def stores(name,value,mode):
  x,y=('x','y') if mode%2==0 else ('y','x')
  return f'{name}.{x} = {name}.{y} = {value};' if mode<2 else f'{name}.{x} = {value};\n    {name}.{y} = {value};'
 groups=['D_802D37F0.x = D_80128300.x;\n    D_802D37F0.y = D_80128300.y;',byte,stores('D_802D37D8',40,aa),stores('D_802D37E0',32,bb)]
 for perm in itertools.permutations(groups):
  v=s[:start]+'    '+'\n    '.join(perm)+'\n'+s[end:];r=probe.probe(fn,pre+v);n+=1
  if r<best:best=r;p.write_text(v);print(n,r,perm,flush=True)
  if r[0]==0:break
 if best[0]==0:break
print('final',n,best)
