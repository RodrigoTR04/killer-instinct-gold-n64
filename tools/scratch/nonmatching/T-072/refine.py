import re,json,pathlib,random
import tu,probe
out=pathlib.Path(__file__).parent
rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);vs=[];count=0
 # Split/merge genuine local declarations, without changing their order.
 m=re.search(r'\b'+fn+r'\s*\([^)]*\)\s*\{',s);start=m.end()
 body=s[start:]
 for d in re.finditer(r'\b(s32|u32|f32|u8|u16|s16)\s+(\*?\w+(?:\s*,\s*\*?\w+)+)\s*;',body):
  a,b=start+d.start(),start+d.end();vs.append(s[:a]+'\n'.join(d[1]+' '+v.strip()+';' for v in d[2].split(','))+s[b:])
 for d in re.finditer(r'\b(s32|u32|f32|u8|u16|s16)\s+(\w+);\s*\1\s+(\w+);',body):
  a,b=start+d.start(),start+d.end();vs.append(s[:a]+d[1]+' '+d[2]+', '+d[3]+';'+s[b:])
 # Assignment chain line breaks and equivalent individual stores.
 atom=r'\w+(?:\[\d+\])?(?:->\w+)?'
 for d in re.finditer(r'((?:'+atom+r'\s*=\s*){2,})(0|255|0xFF);',body):
  a,b=start+d.start(),start+d.end();lhs=re.findall('('+atom+r')\s*=',d[1]);vs.append(s[:a]+'\n'.join(v+' = '+d[2]+';' for v in reversed(lhs))+s[b:]);vs.append(s[:a]+re.sub(r'=\s*','=\n',d[0])+s[b:])
 rng=random.Random(72)
 for v in vs:
  for style in range(4):
   c=v
   if style&1:c=re.sub(r';[^\S\n]+',';\n',c)
   if style&2:c=re.sub(r'\)\s*\{',')\n{',c)
   r=probe.probe(fn,pre+'\n'+c);count+=1
   if r[0]<best[0]:best=r;s=c;print(fn,'decl/chain',best,flush=True)
 # Prefer readable separate lines wherever the best score survives.
 for repeat in range(1):
  matches=list(re.finditer(r'(?<=[;{}])[^\S\n]+(?=\S)',s))
  for m in reversed(matches):
   c=s[:m.start()]+'\n'+s[m.end():];r=probe.probe(fn,pre+'\n'+c);count+=1
   if r[0]<=best[0]:s=c;best=r
 lines=[];depth=0
 for line in s.splitlines():
  t=line.strip()
  if not t:continue
  d=max(0,depth-(1 if t.startswith('}') else 0));lines.append('    '*d+t);depth+=t.count('{')-t.count('}')
 s='\n'.join(lines)+'\n'
 r=probe.probe(fn,pre+'\n'+s);assert r==best,(fn,r,best)
 (out/(fn+'.best.c')).write_text(s);row['new']=best;row['refine_probes']=count
 print(fn,best,flush=True)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
