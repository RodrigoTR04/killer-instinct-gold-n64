from pathlib import Path
import sys,json,re,subprocess,concurrent.futures
R=Path.cwd();sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'))
from probe import source,compile
from context import extent
O=Path('/tmp/kig-t114');O.mkdir(exist_ok=True)
fns=['8002F6F4','801BF720','801BF914','801C4E38','801CC908','801B6528','801B695C','801C85C0','801BD270','80017378']
rows={}
for n in fns:
 fn='func_'+n;s=source(fn);a,b,br=extent(s,fn);body=s[a:b];base=compile(fn,s,'baseline',True)
 rows[fn]=[base];(O/(fn+'-full.c')).write_text(s);print(fn,base,flush=True)
 # Full-context source is stripped only for the permuter importer; target draft remains untouched.
 p=O/(fn+'-draft.c');p.write_text(s[a:b])
 # importer includes original prefix; reconcile declarations by using preprocessed complete TU separately later
 jobs=[]
 if n in ['801BF720','801BF914']:
  for expression in ['result + 0','result | 0','(u32)result','code = result','result == 0 ? 0 : result']:
   jobs.append(('return-'+expression,body.replace('return result;','return '+expression+';')))
  for typ in ['u32','s16','u16','long']:
   jobs.append(('input-reuse-'+typ,body.replace('s32 result;',typ+' result;').replace('return result;','return code = result;')))
  # Single exit, maintaining every case and the original input ABI.
  t=re.sub(r'case ([^:]+): return ([^;]+);',r'case \1: result = \2; goto done;',body).replace('return result;','done:\n return result;')
  jobs.append(('case-goto-single-exit',t))
 # Wrapping each actual scalar in a one-element array changes addressability/allocation without padding.
 decls=list(re.finditer(r'(?m)^([ \t]+)((?:s32|u32|s16|u16|u8|s8|\w+ \*)\s*)(\w+)(\s*=\s*[^;]+)?;',body))
 for m in decls:
  name=m[3]
  if m[4]:continue
  t=body[:m.start()]+m[1]+m[2]+name+'[1];'+body[m.end():]
  t=t[:t.index(name+'[1];')+len(name+'[1];')]+re.sub(r'\b'+name+r'\b',name+'[0]',t[t.index(name+'[1];')+len(name+'[1];'):])
  jobs.append(('array-'+name,t))
 # Uniform line grouping sweep, unlike previous all-joined probes: pairs/triples and offsets.
 ls=body.splitlines()
 for group in [2,3,4,5,7]:
  for shift in range(group):
   t='\n'.join(' '.join(ls[i:i+group]) for i in range(shift,len(ls),group))
   if shift:t='\n'.join(ls[:shift])+'\n'+t
   jobs.append((f'line-groups-{group}-{shift}',t))
 def run(item):
  label,t=item;r=compile(fn,s[:a]+t+s[b:],label,True)
  if r.get('bytes',0)>0 and r.get('words',999)<base.get('words',999):
   out=O/(fn+'-'+re.sub(r'\W','_',label)+'.c');out.write_text(t);r['candidate']=str(out);print('BETTER',fn,r,flush=True)
  return r
 with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:rows[fn]+=list(pool.map(run,jobs))
 (R/'tools/scratch/nonmatching/T-114/experiments.json').write_text(json.dumps(rows,indent=2)+'\n')
