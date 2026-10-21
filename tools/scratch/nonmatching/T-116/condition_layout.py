import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801ADA04';r=next(r for r in ROWS if r['function']==fn);s=(WORK/(fn+'.clean-improved.c')).read_text();v=[]
for condition in ['mode < 14','(mode < 14) != 0','(mode < 14) != 0U']:
 t=s.replace('(mode < 14) != 0U',condition)
 for l,u in layouts(t,fn):v.append((condition+l,u))
res=[]
for l,t in v:
 x=compile(fn,t,l,True);res.append(x);print(l,x.get('words'),flush=True)
 if x.get('words',100)<18 and '!= 0' not in l:(WORK/(fn+'.honest.c')).write_text(t)
(ROOT/'tools/scratch/nonmatching/T-116/condition-layout.json').write_text(json.dumps(res,indent=2)+'\n')
