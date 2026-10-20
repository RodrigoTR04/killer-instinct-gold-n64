from attempts import *
rows=[]
for p in paths:
 s=(ROOT/(p.stem+'-best.c')).read_text();baseline=probe(s,p.stem)
 if 'words' not in baseline:continue
 constants=[]
 for m in re.finditer(r'extern (f32|f64|float|double) ([^;]+);',s):
  for name in re.findall(r'\bD_80048[0-9A-F]{3}\b(?!\[)',m[2]):
   off=int(name[2:],16)-0x8000f960;fmt='>f' if m[1] in ['f32','float'] else '>d';val=struct.unpack_from(fmt,base,off)[0]
   literal=format(val,'.17g');literal+=('.0' if '.' not in literal and 'e' not in literal else '');literal+=('f' if fmt=='>f' else '')
   constants.append((name,literal))
 if not constants:continue
 # Preserve extern declarations while changing executable uses.
 split=s.index('{',s.index('void '+p.stem)) if 'void '+p.stem in s else s.index('{',s.index(p.stem+'('))
 head,body=s[:split],s[split:];allbody=body
 variants=[]
 for name,lit in constants:
  variants.append((name,head+re.sub(r'\b'+name+r'\b','('+lit+')',body)))
  allbody=re.sub(r'\b'+name+r'\b','('+lit+')',allbody)
 variants.append(('all literals',head+allbody))
 results=[]
 for tag,c in variants:
  r=probe(c,p.stem);results.append({'tag':tag,**r})
  if 'words' in r and r['words']<baseline['words']:
   (ROOT/(p.stem+'-literal-'+tag.replace(' ','_')+'.c')).write_text(c);print(p.stem,tag,baseline['words'],'->',r['words'],r['bytes'],flush=True)
 rows.append({'function':p.stem,'baseline':baseline,'attempts':results})
(ROOT/'literals.json').write_text(json.dumps(rows,indent=2)+'\n')
