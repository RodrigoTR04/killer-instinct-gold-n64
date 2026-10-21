"""Bounded local permuter searches; no generated search directory enters git."""
from probe import *
import subprocess,concurrent.futures,time
OUT=ROOT/'tools/scratch/nonmatching/T-116'
def getdraft(r,s):
 tu=next(p for p in (ROOT/'src').glob('*/*.c') if re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/'+r['function']+r'\.s"\)',p.read_text()))
 t=tu.read_text();m=re.search(r'#pragma GLOBAL_ASM\("[^"\n]*/'+r['function']+r'\.s"\)',t)
 # Reconciliations are confined to the inserted draft.
 prefix=t[:m.start()];suffix=t[m.end():]
 assert s.startswith(prefix) and s.endswith(suffix)
 return s[len(prefix):len(s)-len(suffix)]
def run(r):
 fn=r['function'];s=(WORK/(fn+'.best.c')).read_text()
 # Signed/width diagnostic is intentionally not a search seed.
 if fn=='func_801C48E4':s=source(r)
 d=WORK/(fn+'.seed.c');d.write_text(getdraft(r,s))
 out=WORK/('perm-'+fn)
 p=subprocess.run([str(ROOT/'.venv/bin/python'),'tools/permuter/import_fn.py',fn,str(out),'--draft',str(d)],cwd=ROOT,capture_output=True,text=True)
 if p.returncode:
  return fn,{'error':p.stdout+p.stderr}
 start=time.time()
 with (WORK/(fn+'.permuter.log')).open('w') as log:
  p=subprocess.run(['timeout','--signal=INT','--kill-after=15s','900s',str(ROOT/'.venv/bin/python'),str(ROOT/'tools/ext/decomp-permuter/permuter.py'),str(out),'--stack-diffs','--stop-on-zero','--best-only','--better-only','-j','5'],cwd=ROOT,stdout=log,stderr=subprocess.STDOUT)
 result={'exit':p.returncode,'elapsed_seconds':round(time.time()-start),'directory':str(out)}
 print(fn,result,flush=True);return fn,result
if __name__=='__main__':
 # Independent bounded searches; -j5 per target.
 with concurrent.futures.ThreadPoolExecutor(max_workers=15) as pool:
  for fn,result in pool.map(run,ROWS):
   (OUT/(fn+'.search.json')).write_text(json.dumps(result,indent=2)+'\n')
