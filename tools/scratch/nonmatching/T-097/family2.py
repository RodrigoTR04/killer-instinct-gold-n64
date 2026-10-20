import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=(OUT/(fn+'-family-arg1-post-True.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];jobs=[]
for sym in ['*counter','D_801D309C']:
 for value in ['arg1','++*counter','(*counter += 1)']:
  t=body.replace('        *counter = arg1;\n        position = func_801B19F0(-6.0f, -150.0f, arg1, 1);','        position = func_801B19F0(-6.0f, -150.0f, '+sym+' = '+value+', 1);')
  if value!='arg1':continue
  jobs.append(('call-store-'+sym,t))
for typ in ['s32','u32']:
 for arg in ['arg1','arg3','count']:
  t=body.replace('        *counter = arg1;\n        position = func_801B19F0(-6.0f, -150.0f, arg1, 1);','        position = func_801B19F0(-6.0f, -150.0f, *counter = arg1, 1);')
  if arg!='arg1':t=t.replace('arg1 = *counter','count = *counter').replace('arg1++','count++').replace('*counter = arg1','*counter = count').replace('s32 alpha;','s32 alpha;\n '+typ+' count;')
  if arg=='arg3':t=t.replace('count','arg3').replace(typ+' arg3;','')
  jobs.append(('call-'+typ+'-'+arg,t))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<10:
  p=OUT/(fn+'-family2-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=3) as pool:rows=list(pool.map(run,jobs))
(OUT/'family2.json').write_text(json.dumps(rows,indent=2))
