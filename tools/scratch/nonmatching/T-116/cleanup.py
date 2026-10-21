import sys,re
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
fn='func_801C8C24';s=(WORK/(fn+'.output-80-1.full.c')).read_text();a,b=bodybounds(s,fn);body=s[a:b];v=[]
v.append(('unchanged',s))
t=body.replace('D_80127D30[i * 2] = arg0[c = i] & 0xF;','c = i;\n    D_80127D30[i * 2] = arg0[c] & 0xF;');v.append(('separate-assignment',s[:a]+t+s[b:]))
t=body.replace('  u16 c;','  u16 c;\n  u16 byteIndex;').replace('arg0[c = i]','arg0[byteIndex = i]').replace('(c * 2) + 1','(byteIndex * 2) + 1').replace('arg0[c] >> 4','arg0[byteIndex] >> 4');v.append(('named-index',s[:a]+t+s[b:]))
t=t.replace('D_80127D30[i * 2] = arg0[byteIndex = i] & 0xF;','byteIndex = i;\n    D_80127D30[i * 2] = arg0[byteIndex] & 0xF;');v.append(('named-separate-index',s[:a]+t+s[b:]))
res=[]
for label,t in v:
 for l,u in [('default',t),*layouts(t,fn)]:
  x=compile(fn,u,label+'/'+l,True);res.append(x);print(label,l,x.get('words'),x.get('bytes'),flush=True)
  if x.get('words')==0:(WORK/(fn+'.clean.'+label+'.'+l+'.c')).write_text(u)
(ROOT/'tools/scratch/nonmatching/T-116/match-cleanup.json').write_text(json.dumps(res,indent=2)+'\n')
