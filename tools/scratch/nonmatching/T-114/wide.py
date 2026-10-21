from pathlib import Path
import sys,json,re,itertools,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
fn='func_801BD270';s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn);body=s[a:b];jobs=[]
old='result = (result << 32) + ((y << 16) & 0xFFFF0000);'
for shift in ['result <<= 32;','result = result << 32;']:
 for add in ['result += ((y << 16) & 0xFFFF0000);','result = result + ((y << 16) & 0xFFFF0000);','result = ((y << 16) & 0xFFFF0000) + result;']:
  for ret in ['result += buttons;\n    return result;','return result + buttons;','return buttons + result;']:
   t=body.replace(old,shift+'\n'+add).replace('result += buttons;\n    return result;',ret)
   jobs.append(('split-wide-'+str(len(jobs)),t))
for decl,expr in [('u64 storage[1];','storage[0]'),('struct { u64 sum; } storage;','storage.sum'),('union { u64 sum; s64 signedSum; } storage;','storage.sum')]:
 t=body.replace('u64 result;',decl);t=re.sub(r'\bresult\b',expr,t);jobs.append(('wide-storage-'+str(len(jobs)),t))
for i,(name,t) in enumerate(list(jobs)):
 jobs.append((name+'-joined',re.sub(r'\n\s*',' ',t)))
def run(job):
 label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
 if 0<r.get('bytes',0) and r.get('words',999)<7:
  p=O/(fn+'-'+label+'.c');p.write_text(t);r['candidate']=str(p);print('BETTER',r,flush=True)
 return r
with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:rows=list(pool.map(run,jobs))
(R/'tools/scratch/nonmatching/T-114/wide.json').write_text(json.dumps(rows,indent=2)+'\n')
