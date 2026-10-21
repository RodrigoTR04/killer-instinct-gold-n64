import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801BE660';r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];res=[];best=100
for lit,ptr,local,space in itertools.product([False,True],[False,True],[False,True],[False,True]):
 t=body
 if lit:t=t.replace('D_80292B88','28.5')
 if space:t=t.replace('    f32 width = 0.0f;','    f64 space = '+('28.5' if lit else 'D_80292B88')+';\n    f32 width = 0.0f;').replace('+ '+('28.5' if lit else 'D_80292B88')+' *','+ space *')
 if ptr:t=t.replace('    f32 width = 0.0f;','    f32 *position = &x;\n    f32 width = 0.0f;').replace('x -= width / 2.0f;','*position -= width / 2.0f;')
 if local:t=t.replace('    f32 width = 0.0f;','    f32 halfWidth;\n    f32 width = 0.0f;').replace('x -= width / 2.0f;','halfWidth = width / 2.0f;\n    x -= halfWidth;').replace('*position -= width / 2.0f;','halfWidth = width / 2.0f;\n    *position -= halfWidth;')
 full=s[:a]+t+s[b:];label=str((lit,ptr,local,space));x=compile(fn,full,label,True);res.append(x);print(label,x.get('words'),x.get('bytes'),flush=True)
 if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.float2.c')).write_text(full)
(ROOT/'tools/scratch/nonmatching/T-116/float2.json').write_text(json.dumps(res,indent=2)+'\n')
