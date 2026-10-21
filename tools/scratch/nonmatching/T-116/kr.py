import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801C48E4';r=next(r for r in ROWS if r['function']==fn);s=source(r);res=[]
for typ in ['u16','s16','u8','s32']:
 t=s.replace('void func_801C48E4(s32 arg0, s32 arg1, s32 arg2)','void func_801C48E4(arg0, arg1, arg2)\ns32 arg0;\n'+typ+' arg1, arg2;').replace('    arg1 = (u16)arg1; arg2 = (u16)arg2;','')
 for label,u in [('default',t),('one-line',t[:t.index('{',t.index('void func_801C48E4('))]+' '.join(t[t.index('{',t.index('void func_801C48E4(')):t.rfind('#pragma GLOBAL_ASM')].split())+'\n'+t[t.rfind('#pragma GLOBAL_ASM'):])]:
  x=compile(fn,u,typ+label,True);res.append(x);print(typ,label,x.get('words'),x.get('bytes'),flush=True)
  if x.get('words')==0:(WORK/(fn+'.match.c')).write_text(u)
(ROOT/'tools/scratch/nonmatching/T-116/kr.json').write_text(json.dumps(res,indent=2)+'\n')
