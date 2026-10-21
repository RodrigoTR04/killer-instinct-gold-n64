import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801C7F90';r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];res=[];best=100
for order in [(0,1,2,3),(1,2,3,0)]:
 for before in [False,True]:
  for sep in [False,True]:
   t='''{\n    u8 *count = &D_80127CC1;\n    u8 *p;\n    D_80127CC0.bytes[0] = 0;\n    *count = 0;\n    p = D_80127CC2;\n    do {\n'''
   if before:t+='p += 4;\n'
   for i in order:t+='p[%d] = 0;\n'%(i-4 if before else i)
   if not before:t+='p += 4;\n'
   t+='} while (p != &D_80127CE2);\n    *count = 2;\n    func_801C7E4C(0);\n    func_801C7E4C(1);\n    func_801C7F10();\n}'
   if sep:t=t.replace('    *count = 0;','    *count = 0;\n\n')
   full=s[:a]+t+s[b:];full=full.replace('extern u8 D_80127CC1,D_80127CC2[];','extern u8 D_80127CC1,D_80127CC2[], D_80127CE2;')
   x=compile(fn,full,str((order,before,sep)),True);res.append(x);print(x,flush=True)
   if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.clear.c')).write_text(full)
(ROOT/'tools/scratch/nonmatching/T-116/clear.json').write_text(json.dumps(res,indent=2)+'\n')
