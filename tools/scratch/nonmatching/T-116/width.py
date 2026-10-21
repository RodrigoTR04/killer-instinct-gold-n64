import sys,itertools,concurrent.futures
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *

def run(fn):
 r=next(r for r in ROWS if r['function']==fn);s=source(r);res=[];v=[]
 if fn=='func_801C8AE0':
  for typ in ['s16','u16','s32','u32']:
   for cast in ['', '(u16)', '(u32)', '(s32)']:
    t=s.replace('extern s32 func_801BF914(s32);','extern '+typ+' func_801BF914(s32);').replace('c |= func_801BF914((D_80127D00[i] >> 8) & 0xFF);','c |= '+cast+'func_801BF914((D_80127D00[i] >> 8) & 0xFF);')
    v.append((typ+cast,t))
 if fn=='func_801C48E4':
  # Address-based conversion without writing the converted word back to its home.
  for use in ['*(u16 *)((u8 *)&arg1 + 2)','((u16 *)&arg1)[1]']:
   t=s.replace('arg1 = (u16)arg1; arg2 = (u16)arg2;','').replace('arg0 + 2, arg1, arg2,','arg0 + 2, '+use+', '+use.replace('arg1','arg2')+',')
   v.append((use,t))
 best=100
 for l,t in v:
  x=compile(fn,t,l,True);res.append(x);print(fn,l,x.get('words'),x.get('bytes'),flush=True)
  if x.get('words',100)<best:best=x['words'];(WORK/(fn+'.width.c')).write_text(t)
 (ROOT/'tools/scratch/nonmatching/T-116'/(fn+'.width.json')).write_text(json.dumps(res,indent=2)+'\n')
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as p:list(p.map(run,['func_801C8AE0','func_801C48E4']))
