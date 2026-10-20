import sys,random
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=(OUT/(fn+'-family2-call-store-_counter.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];jobs=[]
for typ in ['s32','u32','s16']:
 for anchor in ['f32 position;','s32 alpha;','T025Gfx2010 *env;']:
  t=body.replace(' s32 *counter = &D_801D309C;','').replace(anchor,anchor+'\n '+typ+' *counter = ('+typ+' *)&D_801D309C;');jobs.append(('pointer-decl-'+typ+'-'+anchor,t))
for expr in ['(*counter = arg1)','(arg1)','arg1 = arg1']:
 t=body.replace('*counter = arg1, 1)',expr+', 1)')
 if expr!='(*counter = arg1)':continue
 jobs.append(('paren-'+expr,t))
random.seed(97);lines=body.splitlines();stop=next(i for i,l in enumerate(lines) if 'guTranslate' in l)
for i in range(64):
 prefix=''
 for line in lines[:stop]:prefix+=line.strip()+(' ' if random.randrange(2) else '\n')
 jobs.append(('layout-random-'+str(i),prefix+'\n'+'\n'.join(lines[stop:])))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<2:
  p=OUT/(fn+'-family5-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=4) as pool:rows=list(pool.map(run,jobs))
(OUT/'family5.json').write_text(json.dumps(rows,indent=2))
