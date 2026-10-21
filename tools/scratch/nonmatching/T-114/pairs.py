from pathlib import Path
import sys,re,json,itertools,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
rows={}
for fn in ['func_801B695C','func_801CC908','func_801B6528']:
 s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn);body=s[a:b];jobs=[]
 decls=list(re.finditer(r'(?m)^\s+(?:s32|u8 \*|f32|T029Gfx801B6528 \*)\s*\w+;',body))
 for m1,m2 in itertools.combinations(decls,2):
  t=body[:m1.start()]+m2[0]+body[m1.end():m2.start()]+m1[0]+body[m2.end():]
  jobs.append(('pair-swap-'+str(len(jobs)),t))
 if fn.endswith('B695C'):
  for typ in ['u8 *','void *','s32']:
   t=body.replace('u8 *frame;', 'u8 *frame;\n '+typ+' frames;')
   t=t.replace('if (arg0 != 0 && arg0->frames != 0)', 'if (arg0 != 0 && (frames = ('+typ+')arg0->frames) != 0)')
   pos=t.index('{',t.index('if (arg0'))+1
   t=t[:pos]+t[pos:].replace('arg0->frames','((u8 *)frames)')
   jobs.append(('snapshot-source-'+typ,t))
  for expr in ['(arg0->frames != 0 && arg0 != 0)','(arg0 && arg0->frames)']:
   if expr.startswith('(arg0->'):continue # preserves null guard
   jobs.append(('logical-pointer-condition',body.replace('(arg0 != 0 && arg0->frames != 0)',expr)))
 def run(job):
  label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
  baseline={'func_801B695C':4,'func_801CC908':2,'func_801B6528':3}[fn]
  if 0<r.get('bytes',0) and r.get('words',999)<baseline:
   p=O/(fn+'-'+re.sub(r'\W','_',label)+'.c');p.write_text(t);r['candidate']=str(p);print('BETTER',fn,r,flush=True)
  return r
 with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:rows[fn]=list(pool.map(run,jobs))
 (R/'tools/scratch/nonmatching/T-114/pairs.json').write_text(json.dumps(rows,indent=2)+'\n')
