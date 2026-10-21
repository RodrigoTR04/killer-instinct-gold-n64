import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801BE660';r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];res=[];best=100
for literal,div,neg in itertools.product([False,True],['2.0f','2.0'],[False,True]):
 t=body
 if literal:t=t.replace('D_80292B88','28.5')
 if neg:t=t.replace('index < 27 && index >= 0','index >= 0 && index < 27')
 t=t.replace('width / 2.0f','width / '+div)
 full=s[:a]+t+s[b:];label=f'{literal}/{div}/{neg}';x=compile(fn,full,label,True);res.append(x);print(label,x.get('words'),x.get('bytes'),flush=True)
 if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.float.c')).write_text(full)
(ROOT/'tools/scratch/nonmatching/T-116/float.json').write_text(json.dumps(res,indent=2)+'\n')
