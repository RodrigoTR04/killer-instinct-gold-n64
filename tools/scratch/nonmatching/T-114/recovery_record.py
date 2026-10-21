from pathlib import Path
import sys,json,re,itertools,concurrent.futures,random
R=Path.cwd();sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
O=Path('/tmp/kig-t114');rows={}
for fn in ['func_801BD270']:
 s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn);body=s[a:b];base=compile(fn,s,'reconciled-baseline',True);jobs=[]
 if fn.endswith('BF914'):
  for expr in ['result + 0','result | 0','(u32)result','code = result','result == 0 ? 0 : result']:
   jobs.append(('return-'+expr,body.replace('return result;','return '+expr+';')))
 # Pack pairs of real independent scalar variables into a record; unlike separate padding or single-scalar records.
 decls=list(re.finditer(r'(?m)^([ \t]+)(s32|s16|u32|u16|u8|s8)\s+(\w+);',body))
 for m1,m2 in itertools.combinations(decls,2):
  for reverse in [False,True]:
   pair=[m1,m2][::(-1 if reverse else 1)]
   rec='struct { '+ ' '.join(m[2]+' '+m[3]+';' for m in pair)+' } state;'
   t=body
   for m in sorted([m1,m2],key=lambda m:m.start(),reverse=True):t=t[:m.start()]+(rec if m==m1 else '')+t[m.end():]
   # Replace only tokens outside record's declaration.
   pos=t.index(rec)+len(rec)
   suffix=t[pos:]
   for m in pair:suffix=re.sub(r'(?<![.>])\b'+m[3]+r'\b','state.'+m[3],suffix)
   t=t[:pos]+suffix
   jobs.append(('record-'+m1[3]+'-'+m2[3]+('-reverse' if reverse else ''),t))
 # Random token-preserving layout is a scheduling diagnostic with no semantic mutations.
 rng=random.Random(114);ls=body.splitlines()
 for i in range(0):
  t=ls[0]
  for l in ls[1:]:t+=(' ' if rng.random()<0.65 else '\n')+l
  jobs.append(('random-layout-'+str(i),t))
 def run(job):
  label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
  if 0<r.get('bytes',0) and r.get('words',999)<base.get('words',999):
   p=O/(fn+'-'+label+'.c');p.write_text(t);r['candidate']=str(p);print('BETTER',fn,r,flush=True)
  return r
 with concurrent.futures.ThreadPoolExecutor(max_workers=4) as pool:rows[fn]=[base]+list(pool.map(run,jobs))
 print(fn,'done',len(rows[fn]),flush=True)
 (R/'tools/scratch/nonmatching/T-114/extra.json').write_text(json.dumps(rows,indent=2)+'\n')
