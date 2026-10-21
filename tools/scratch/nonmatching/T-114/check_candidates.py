from pathlib import Path
import sys,json,re,concurrent.futures
R=Path.cwd();O=Path('/tmp/kig-t114');sys.path.insert(0,str(R/'tools/scratch/nonmatching/T-096'));from probe import compile;from context import extent
rows=[]
for folder in sorted(O.glob('func_*')):
 if not folder.is_dir():continue
 fn=folder.name;s=(O/(fn+'-full.c')).read_text();a,b,_=extent(s,fn)
 for c in folder.glob('output-*/source.c'):
  t=c.read_text()
  try:aa,bb,_=extent(t,fn)
  except Exception as e: rows.append(dict(function=fn,path=str(c),error=str(e)));continue
  # Retain full original TU; use only the mutated target body and any local changes inside it.
  result=compile(fn,s[:a]+t[aa:bb]+s[b:],'permuter-'+c.parent.name,True)
  result.update(function=fn,path=str(c));rows.append(result)
  print(fn,c.parent.name,result.get('words'),result.get('bytes'),result.get('error','')[:120],flush=True)
(R/'tools/scratch/nonmatching/T-114/candidates.json').write_text(json.dumps(rows,indent=2)+'\n')
