import sys,itertools,concurrent.futures
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts

def run(fn):
 r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];v=[]
 if fn=='func_801C7F90':
  for init,order,ptr in itertools.product([False,True],[False,True],[False,True]):
   t=body.replace('D_80127CC0.fields.first=D_80127CC1=0;','D_80127CC0.bytes[0]=zero; D_80127CC1=zero;')
   t=t.replace('s32 i;','s32 i; s32 zero = 0;')
   if order:t=t.replace('D_80127CC0.bytes[0]=zero; D_80127CC1=zero;','D_80127CC1=zero; D_80127CC0.bytes[0]=zero;')
   if ptr:t=t.replace('s32 i;','u8 *second = &D_80127CC1; s32 i;').replace('D_80127CC1=', '*second=')
   if init:t=t.replace('for(i=0;i<32;) D_80127CC2[i++]=0;','for(i=0;i<32;i++) D_80127CC2[i]=zero;')
   v.append((str((init,order,ptr)),s[:a]+t+s[b:]))
 if fn=='func_801BD200':
  for order in itertools.permutations(['limit','flags','result']):
   for local in [False,True]:
    decl={'limit':'s32 limit = D_800684A0;','flags':'u8 *flags = D_802D369C;','result':'s32 *result = &D_80282A60;'}
    t=body.replace('{','{\n'+ '\n'.join(decl[k] for k in order),1).replace('D_800684A0','limit').replace('s32 limit = limit;','s32 limit = D_800684A0;').replace('D_802D369C[','flags[').replace('D_80282A60 =','*result =')
    if local:t=t.replace('s32 limit =','s32 one = 1;\n s32 limit =').replace(' = 1;',' = one;').replace('s32 one = one;','s32 one = 1;')
    v.append((str(order)+str(local),s[:a]+t+s[b:]))
 res=[];best=100
 for l,t in v:
  x=compile(fn,t,l,True);res.append(x)
  if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.pointer.c')).write_text(t)
  print(fn,l,x.get('words'),x.get('bytes'),flush=True)
 (ROOT/'tools/scratch/nonmatching/T-116'/(fn+'.pointer.json')).write_text(json.dumps(res,indent=2)+'\n')
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as p:list(p.map(run,['func_801C7F90','func_801BD200']))
