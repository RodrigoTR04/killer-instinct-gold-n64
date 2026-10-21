import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801C48E4';r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];res=[];best=100
for p1,p2,order in itertools.product([0,1],[0,1],[0,1,2]):
 t=body
 decl=''
 if p1:decl+='s32 *first = &arg1;\n'
 if p2:decl+='s32 *second = &arg2;\n'
 if order==0:t=t.replace('    u8 *temp_v0;','    u8 *temp_v0;\n'+decl)
 elif order==1:t=t.replace('    arg1 = (u16)arg1; arg2 = (u16)arg2;','    '+decl+'arg1 = (u16)arg1; arg2 = (u16)arg2;')
 else:
  decl=decl.replace(' = &arg1','').replace(' = &arg2','')
  t=t.replace('    u8 *temp_v0;','    u8 *temp_v0;\n'+decl)
  t=t.replace('    D_8004F2C8 = 0;',('first = &arg1;\n' if p1 else '')+('second = &arg2;\n' if p2 else '')+'    D_8004F2C8 = 0;')
 if p1:t=t.replace('arg0 + 2, arg1,','arg0 + 2, *first,')
 if p2:t=t.replace('arg1, arg2, 0,','arg1, *second, 0,').replace('*first, arg2, 0,','*first, *second, 0,')
 full=s[:a]+t+s[b:];label=str((p1,p2,order));x=compile(fn,full,label,True);res.append(x);print(label,x.get('words'),x.get('bytes'),flush=True)
 if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.arg.c')).write_text(full)
(ROOT/'tools/scratch/nonmatching/T-116/args.json').write_text(json.dumps(res,indent=2)+'\n')
