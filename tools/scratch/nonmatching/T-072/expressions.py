import re,random,json,pathlib
import tu,probe
out=pathlib.Path(__file__).parent
rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);count=0;rng=random.Random(720)
 # Token-preserving breaks within assignments, call arguments and conditions.
 m=re.search(r'\b'+fn+r'\s*\([^)]*\)\s*\{',s);start=m.end();head=s[:start];body=s[start:]
 for k in range(40):
  c=head+re.sub(r'(?<=,)\s*|(?<=[^=!<>]=)(?!=)\s*|\s+(?=&&|\|\|)',lambda m:'\n' if rng.random()<[.2,.5,.8][k%3] else ' ',body)
  r=probe.probe(fn,pre+'\n'+c);count+=1
  if r[0]<best[0]:best=r;s=c;print(fn,k,best,flush=True)
 (out/(fn+'.best.c')).write_text(s);row['expression_probes']=count;row['new']=best
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
