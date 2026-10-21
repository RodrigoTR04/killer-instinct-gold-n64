import sys,itertools,concurrent.futures
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
r=next(r for r in ROWS if r['function']=='func_801C8C24');fn=r['function'];s=source(r);a,b=bodybounds(s,fn);body=s[a:b];beg=body[:body.index('    for (i = 0; i < 4; i++)')]
v=[]
for form in range(8):
 tail=''
 for i in range(4):
  low=f'D_80127D30[{2*i}]';high=f'D_80127D30[{2*i+1}]'
  if form==0:tail+=f'{low}=*arg0++ & 15; {high}=arg0[-1]>>4;\n'
  if form==1:tail+=f'{low}=arg0[0]&15; arg0++; {high}=arg0[-1]>>4;\n'
  if form==2:tail+=f'{low}=*arg0&15; {high}=*arg0>>4; '+('arg0++;\n' if i<3 else '\n')
  if form==3:tail+=f'{high}=*arg0>>4; {low}=*arg0++&15;\n'
  if form==4:tail+=f'p{i}=arg0+{i}; {low}=*p{i}&15; {high}=*p{i}>>4;\n'
  if form==5:tail+=f'p{i}=arg0++; {low}=*p{i}&15; {high}=*p{i}>>4;\n'
  if form==6:tail+=f'{low}=*(arg0+{i})&15; {high}=*(arg0+{i})>>4;\n'
  if form==7:tail+=f'c=arg0[{i}]; {low}=c&15; {high}=arg0[{i}]>>4;\n'
 t=beg+tail+'}'
 if form in [4,5]:t=t.replace('    s32 i;','    u8 *p0,*p1,*p2,*p3;\n    s32 i;')
 v.append((str(form),s[:a]+t+s[b:]))
res=[];best=1000
for label,t in v:
 x=compile(fn,t,label,True);res.append(x)
 print(label,x.get('words'),x.get('bytes'),flush=True)
 if x.get('words',1000)<best:best=x['words'];(WORK/(fn+'.tail.c')).write_text(t)
(ROOT/'tools/scratch/nonmatching/T-116/tail.json').write_text(json.dumps(res,indent=2)+'\n')
