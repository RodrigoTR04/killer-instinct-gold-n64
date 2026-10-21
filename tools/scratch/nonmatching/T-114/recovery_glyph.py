from pathlib import Path
import sys,re,json,itertools,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
rows={}
for fn in ['func_801BF914']:
 s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn);body=s[a:b];base=compile(fn,s,'baseline',True);jobs=[]
 if 'BF' in fn:
  # Normalize switch selector explicitly, preserving modulo-u32 behavior and every label.
  for delta in [1,26,27,32,44,65]:
   t=body.replace('switch (code)',f'switch (code - {delta}U)')
   t=re.sub(r"case ('[^']*'|[0-9]+):",lambda m:f'case ((u32)({m[1]}) - {delta}U):',t)
   jobs.append(('normalized-switch-'+str(delta),t))
   for brace in [False,True]:
    tt=t.replace('switch (code -', 'code -= '+str(delta)+'U;\n switch (code -',1).replace(f'switch (code - {delta}U)','switch (code)')
    if brace:tt=re.sub(r'case ([^:]+): return ([^;]+);',r'case \1: { return \2; }',tt)
    jobs.append(('destructive-selector-'+str(delta)+'-'+str(brace),tt))
 if fn.endswith('C85C0'):
  old='    *var_s1 = 0;\n    *var_s3 = 0;\n    *var_s2 = 0;\n    *var_s4 = 0;'
  stores=['*var_s1','*var_s3','*var_s2','*var_s4']
  for perm in itertools.permutations(stores):
   for grouping in [1,2,4]:
    lines=[' = '.join(perm[i:i+grouping])+' = 0;' for i in range(0,4,grouping)]
    jobs.append(('chained-clears-'+str(len(jobs)),body.replace(old,'\n'.join(lines))))
 if fn.endswith('17378'):
  for anchor in ['    model = (void **)&D_8004A998;','    func_80028600(0, D_8004AC84, D_8004AC84, 0);']:
   for typ in ['u8 *','T0331383CStageRotation *','void *']:
    t=body.replace('{','{\n '+typ+' end;',1).replace(anchor,'end = ('+typ+')&D_8004AA14;\n'+anchor).replace('if ((u8 *)rot == &D_8004AA14)','if ((void *)rot == (void *)end)')
    jobs.append(('endpoint-'+str(len(jobs)),t))
 def run(job):
  label,t=job;r=compile(fn,s[:a]+t+s[b:],label,True)
  if 0<r.get('bytes',0) and r.get('words',999)<base.get('words',999):
   p=O/(fn+'-'+label+'.c');p.write_text(t);r['candidate']=str(p);print('BETTER',fn,r,flush=True)
  return r
 with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:rows[fn]=[base]+list(pool.map(run,jobs))
 print(fn,'done',flush=True)
 (R/'tools/scratch/nonmatching/T-114/focused.json').write_text(json.dumps(rows,indent=2)+'\n')
