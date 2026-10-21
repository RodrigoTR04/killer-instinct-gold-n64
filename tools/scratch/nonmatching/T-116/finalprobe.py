import sys,itertools,concurrent.futures
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts

def run(fn):
 r=next(r for r in ROWS if r['function']==fn);s=source(r);a,b=bodybounds(s,fn);body=s[a:b];v=[]
 if fn=='func_801C48E4':
  for p1,p2 in itertools.product([0,1],[0,1]):
   t=body.replace('arg1 = (u16)arg1; arg2 = (u16)arg2;','')
   decl=('s32 *first = &arg1;\n' if p1 else '')+('s32 *second = &arg2;\n' if p2 else '')
   t=t.replace('    u8 *temp_v0;','    u8 *temp_v0;\n'+decl).replace('arg0 + 2, arg1, arg2,','arg0 + 2, (u16)'+('*first' if p1 else 'arg1')+', (u16)'+('*second' if p2 else 'arg2')+',')
   v.append((str((p1,p2)),s[:a]+t+s[b:]))
 if fn=='func_801C7F90':
  s=(WORK/(fn+'.pointer.c')).read_text();a,b=bodybounds(s,fn);body=s[a:b]
  old='for(i=0;i<32;) D_80127CC2[i++]=0;'
  loops=['for(i=0;i<32;i++) D_80127CC2[i]=0;','i=0; do { D_80127CC2[i]=0; i++; } while(i<32);','i=0; while(i<32) {D_80127CC2[i]=0; i++;}','for(i=32;i>0;i--) D_80127CC2[32-i]=0;','for(i=0;i!=32;i++) D_80127CC2[i]=0;']
  for i,l in enumerate(loops):v.append((str(i),s[:a]+body.replace(old,l)+s[b:]))
 res=[];best=100;bs=s
 for l,t in v:
  for lab,u in [('default',t),*layouts(t,fn)]:
   x=compile(fn,u,l+'/'+lab,True);res.append(x);print(fn,l,lab,x.get('words'),x.get('bytes'),flush=True)
   if x.get('words',100)<best:best=x['words'];bs=u
 (WORK/(fn+'.finalprobe.c')).write_text(bs)
 (ROOT/'tools/scratch/nonmatching/T-116'/(fn+'.finalprobe.json')).write_text(json.dumps(res,indent=2)+'\n')
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as p:list(p.map(run,['func_801C48E4','func_801C7F90']))
