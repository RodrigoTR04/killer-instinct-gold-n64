import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801C48E4';r=next(r for r in ROWS if r['function']==fn);s=(WORK/(fn+'.arg.c')).read_text();v=[]
for typ,casts in itertools.product(['u16','s16'],[False,True]):
 t=s.replace('s32 arg1, s32 arg2',typ+' arg1, '+typ+' arg2').replace('s32 *first',typ+' *first').replace('s32 *second',typ+' *second')
 if not casts:t=t.replace('    arg1 = (u16)arg1; arg2 = (u16)arg2;','')
 v.append((typ+str(casts),t))
res=[]
for l,t in v:
 for layout,u in [('default',t),*layouts(t,fn)]:
  x=compile(fn,u,l+layout,True);res.append(x);print(l,layout,x.get('words'),x.get('bytes'),flush=True)
  if x.get('words')==0:(WORK/(fn+'.match.c')).write_text(u)
(ROOT/'tools/scratch/nonmatching/T-116/args2.json').write_text(json.dumps(res,indent=2)+'\n')
