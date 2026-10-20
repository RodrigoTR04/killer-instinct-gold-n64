import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
fn='func_801B2010';s=(OUT/(fn+'-family2-call-store-_counter.c')).read_text();a,b,br=extent(s,fn);body=s[a:b];jobs=[]
lines=body.splitlines(True)
for i in range(len(lines)-1):
 t=''.join(lines[:i])+lines[i].rstrip()+' '+lines[i+1].lstrip()+''.join(lines[i+2:]);jobs.append(('join-'+str(i),t))
for expr in ['arg1++ < 1','arg1++ <= 0','(arg1++) < 1','arg1 < 1','arg1 <= 0']:
 t=body.replace('arg1++ < 1',expr)
 if '++' not in expr:t=t.replace('    if ('+expr+')','    ++arg1;\n    if (arg1 <= 1)')
 jobs.append(('condition-'+expr,t))
for decl in ['s32 limit = 1;','s32 limit;']:
 t=body.replace('s32 alpha;','s32 alpha;\n '+decl).replace('*counter = arg1, 1)', '*counter = arg1, limit)')
 if decl=='s32 limit;':t=t.replace('arg1 = *counter;','arg1 = *counter;\n limit = 1;')
 jobs.append(('limit-'+decl,t))
rows=[]
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if r.get('words',999)<2:
  p=OUT/(fn+'-family3-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(s[:a]+t+s[b:]);r['candidate']=str(p);print(r,flush=True)
 return r
with ThreadPoolExecutor(max_workers=4) as pool:rows=list(pool.map(run,jobs))
(OUT/'family3.json').write_text(json.dumps(rows,indent=2))
