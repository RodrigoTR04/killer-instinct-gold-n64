import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C35D8';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
a=s.index('    CloudCmd *dl;');b=s.index('    dl = (*arg0)++;',a)
decls=['CloudCmd *dl;','s32 i;','s32 offset;','s32 visible;','T030Cloud *cloud;','s16 start;','s32 end;']
for perm in itertools.permutations(decls):
 v=s[:a]+'    '+'\n    '.join(perm)+'\n'+s[b:];r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,r,perm,flush=True)
 if r[0]==0:break
print('final',n,best,flush=True)
