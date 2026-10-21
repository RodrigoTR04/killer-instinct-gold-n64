"""Recheck permuter function bodies against the complete original TU context."""
from probe import *
import concurrent.futures
OUT=ROOT/'tools/scratch/nonmatching/T-116'
def definition(s,fn):
 a,b=bodybounds(s,fn); start=s.rfind('\n',0,s.rfind(fn,0,a))+1
 return s[start:b]
def run(r):
 fn=r['function'];s=source(r);a,b=bodybounds(s,fn);start=s.rfind('\n',0,s.rfind(fn,0,a))+1
 results=[]
 for p in sorted((WORK/('perm-'+fn)).glob('output-*/source.c')):
  t=p.read_text()
  if re.search(r'\bregister\b|\basm\b|#line',t):
   results.append({'candidate':p.parent.name,'rejected':'forbidden construct'});continue
  try:
   d=definition(t,fn);full=s[:start]+d+s[b:];res=compile(fn,full,p.parent.name)
   if 'words' in res:
    (WORK/(fn+'.'+p.parent.name+'.full.c')).write_text(full)
   res['candidate']=p.parent.name;results.append(res)
  except Exception as e:results.append({'candidate':p.parent.name,'error':str(e)})
 (OUT/(fn+'.harvest.json')).write_text(json.dumps(results,indent=2)+'\n')
 valid=[x for x in results if 'words' in x]
 print(fn,[(x['candidate'],x['words'],x['bytes']) for x in valid],flush=True)
 return fn,results
if __name__=='__main__':
 with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:list(pool.map(run,[r for r in ROWS if r["function"]!="func_801C8C24"]))
