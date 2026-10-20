import re,json,pathlib,random
import tu,probe
out=pathlib.Path(__file__).parent
results=json.loads((out/'results.json').read_text())
for fn,row in results.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);count=0
 # Small declaration and chain spelling changes, each screened with current layout.
 variants=[]
 for m in re.finditer(r'\b(s32|u32|f32|T021Gfx)\s+(\*?\w+(?:,\s*\*?\w+)+);',s):
  typ=m[1];vs=m[2].split(',');variants.append(s[:m.start()]+('\n'.join(typ+' '+v.strip()+';' for v in vs))+s[m.end():])
 for m in re.finditer(r'((?:\w+\s*=\s*){2,})0;',s):
  vs=re.findall(r'(\w+)\s*=',m[1]);variants.append(s[:m.start()]+' '.join(v+' = 0;' for v in reversed(vs))+s[m.end():])
 for cand in variants:
  count+=1;r=probe.probe(fn,pre+'\n'+cand)
  if r[0]<best[0]:s=cand;best=r
 # Prefer splitting every shared statement/brace boundary, retaining only necessary joins.
 for repeat in range(2):
  matches=list(re.finditer(r'(?<=[;{}])[^\S\n]+(?=\S)',s))
  for m in reversed(matches):
   cand=s[:m.start()]+'\n'+s[m.end():];count+=1;r=probe.probe(fn,pre+'\n'+cand)
   if r[0]<=best[0]:s=cand;best=r
 # Indentation only; preserve all line boundaries.
 lines=[];depth=0
 for line in s.splitlines():
  t=line.strip()
  if not t:lines.append('');continue
  d=max(0,depth-(1 if t.startswith('}') else 0));lines.append('    '*d+t)
  depth+=t.count('{')-t.count('}')
 s='\n'.join(lines).strip()+'\n'
 r=probe.probe(fn,pre+'\n'+s)
 assert r==best,(fn,r,best)
 (out/(fn+'.best.c')).write_text(s);row['new']=best;row['refine_probes']=count
 print(fn,best,flush=True)
(out/'results.json').write_text(json.dumps(results,indent=2)+'\n')
