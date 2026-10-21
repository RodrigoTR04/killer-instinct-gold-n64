import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
from search import getdraft
OUT=ROOT/'tools/scratch/nonmatching/T-116'
cases={
'func_801C8004':('output-530-1',lambda t:t.replace('(var_v1 ^ 0)','var_v1')),
'func_801BEEA4':('output-486-1',lambda t:t.replace('      slot = 8;\n','').replace('&entries[i - 2], slot','&entries[i - 2], 8')),
'func_801C0800':('output-543-1',lambda t:t.replace('((g << 5) << 11)','(g << 16)').replace('  FrontendGfxWords *new_var;\n','').replace('  new_var = (*list)++;\n  p = new_var;','  p = (*list)++;')),
'func_801C8AE0':('output-110-1',lambda t:t),
'func_801C48E4':('output-225-1',lambda t:t),
'func_801ADA04':('output-125-1',lambda t:t),
}
res={}
for fn,(cand,clean) in cases.items():
 p=WORK/(fn+'.'+cand+'.full.c')
 if not p.exists():continue
 s=p.read_text();t=clean(s);x=compile(fn,t,'clean-'+cand,True);res[fn]=x;print(fn,x,flush=True)
 if 'words' in x:
  (WORK/(fn+'.clean-improved.c')).write_text(t)
(OUT/'clean-improvements.json').write_text(json.dumps(res,indent=2)+'\n')
