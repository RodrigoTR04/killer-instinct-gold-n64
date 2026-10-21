"""T-116 full-TU compiler measurements; disposable products live in /tmp."""
from pathlib import Path
import sys, importlib.util, json, re
ROOT=Path(__file__).resolve().parents[4]
sys.path.insert(0,str(ROOT/'tools/permuter'))
import screen
spec=importlib.util.spec_from_file_location('prior_probe',ROOT/'tools/scratch/nonmatching/T-096/probe.py')
prior=importlib.util.module_from_spec(spec);spec.loader.exec_module(prior)
compile=prior.compile
WORK=Path('/tmp/kig-t116');WORK.mkdir(exist_ok=True)
ROWS=json.loads((ROOT/'tools/scratch/nonmatching/T-116/selection.json').read_text())[:15]
def source(r):
 p=WORK/(r['function']+'.full.c')
 try:screen.measure(r['function'],ROOT/r['draft'],source_output=p)
 except Exception as e:
  s=p.read_text()
  if r['function']=='func_801BEEA4':
   s=s.replace('extern void *memcpy(void *, const void *, u32);','')
   # The TU and draft table layouts agree; retain the draft view only in its body.
   s=s.replace('extern T023TableEA4 D_80127D80[];','')
   start=s.index('s32 func_801BEEA4(');s=s[:start]+s[start:].replace('&D_80127D80[table]','&((T023TableEA4 *)D_80127D80)[table]')
  elif r['function']=='func_801C8C24':
   s=s.replace('extern s32 func_801BF720(s32);','extern s32 func_801BF720(u32);')
  else:raise
  p.write_text(s)
 return p.read_text()
def bodybounds(s,fn):
 m=re.search(r'\b'+fn+r'\([^;{}]*\)\s*\{',s);a=m.end()-1; depth=1;b=a+1
 while depth:
  depth+=(s[b]=='{')-(s[b]=='}');b+=1
 return a,b
if __name__=='__main__':
 out={}
 for r in ROWS:
  fn=r['function']
  try:
   s=source(r);res=compile(fn,s,'baseline',True)
  except Exception as e:res={'error':str(e)}
  out[fn]=res;print(fn,res,flush=True)
 (ROOT/'tools/scratch/nonmatching/T-116/baseline.json').write_text(json.dumps(out,indent=2)+'\n')
