import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=(OUT/(fn+'-family2-call-store-_counter.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];jobs=[]
for point in ['arg1 = *counter;','if (arg1++ < 1)','position = func_801B19F0']:
 for val in ['arg3','limit']:
  t=body.replace('*counter = arg1, 1)', '*counter = arg1, '+val+')')
  if val=='limit':t=t.replace('s32 alpha;','s32 alpha;\n s32 limit;')
  if point=='arg1 = *counter;':t=t.replace(point,point+'\n '+val+' = 1;')
  elif point=='if (arg1++ < 1)':t=t.replace(point,val+' = 1;\n '+point)
  else:t=t.replace(point,val+' = 1;\n '+point)
  jobs.append(('arg-limit-'+point+'-'+val,t))
for point in ['arg1 = *counter;','if (arg1++ < 1)']:
 t=body.replace('s32 *counter = &D_801D309C;','s32 *counter;').replace(point,'counter = &D_801D309C;\n '+point);jobs.append(('pointer-assignment-'+point,t))
for expr in ['arg1++ <= 0','0 >= arg1++','1 > arg1++','!(arg1++ > 0)']:
 jobs.append(('predicate-'+expr,body.replace('arg1++ < 1',expr)))
for decl in ['s32 *const counter = &D_801D309C;','s32 (*counter)[1] = (s32 (*)[1])&D_801D309C;']:
 t=body.replace('s32 *counter = &D_801D309C;',decl)
 if '[1]' in decl:t=t.replace('*counter','(*counter)[0]').replace('s32 ((*counter)[0])[1]','s32 (*counter)[1]')
 jobs.append(('declaration-'+decl,t))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<2:
  p=OUT/(fn+'-family4-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=4) as pool:rows=list(pool.map(run,jobs))
(OUT/'family4.json').write_text(json.dumps(rows,indent=2))
