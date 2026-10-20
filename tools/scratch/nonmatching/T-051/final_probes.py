from probe import *
import itertools,re
rows=[]
def run(fn,v,tag):
 r=probe(v,fn,tag);rows.append({'function':fn,'variant':tag,**r});return r
# CBCC scheduling variants that retain the external address and ordinary operations.
s=Path('tools/scratch/nonmatching/T-022/func_8001CBCC.c').read_text();best=(2,s)
for order,operand,form in itertools.product(itertools.permutations('xyz'),[0,1],range(4)):
 a=s.index('    x *=');b=s.index('    sinx =',a)
 lines=[]
 for c in order:
  expr='D_80045C00 * '+c if operand else c+' * D_80045C00'
  if form==0:lines.append('    '+c+' = '+expr+';')
  elif form==1:lines.append('    '+c+' = (f32)('+expr+');')
  elif form==2:lines.append('    '+c+' = '+c+' * *(&D_80045C00);')
  else:lines.append('    '+c+' *= factor;')
 v=s[:a]+('    const f32 factor = D_80045C00;\n' if form==3 else '')+'\n'.join(lines)+'\n'+s[b:]
 r=run('func_8001CBCC',v,'cbfinal%d'%len(rows))
 if r.get('words',999)<best[0]:best=(r['words'],v)
print('CBCC',best[0]);
if best[0]<2:(ROOT/'1CBCC-best.c').write_text(best[1])
# 21B6C: standalone declarations from the real TU, retaining its own types.
s=Path('tools/scratch/nonmatching/T-032/func_80021B6C.c').read_text();context=Path('src/main/main_2FF0.c').read_text();b=context.index('} T022Sprite;')+len('} T022Sprite;');a=context.rfind('typedef struct',0,b)
s=context[a:b]+'''\nextern T022Sprite D_8004CED0[];
extern u8 D_8004AC88,D_8004A9D8,D_8004A998,D_8004AA28;
extern s8 D_8004AC89,D_8004AC8A;
'''+s
for mode in [0,1,2]:
 v=s
 if mode:v=re.sub(r'switch \(([^\n]+)\) \{',r'switch (('+('u32' if mode==1 else 's32')+r')(\1)) {',v)
 r=run('func_80021B6C',v,'21final%d'%mode);print('21',mode,{k:v for k,v in r.items() if k!='offsets'})
# 249: keep genuine improvements with equivalent lookup behavior.
s=Path('tools/scratch/nonmatching/T-032/func_800249DC.c').read_text();best=(10,s)
for cond,op,bound in itertools.product(['<','<=','!='],['+=2','+=1+1'],[13,14]):
 if (cond,bound) not in [('<',13),('<',14),('<=',13),('!=',14)]:continue
 v=s.replace('i+=2;', 'i'+op+';').replace('i<14','i'+cond+str(bound))
 r=run('func_800249DC',v,'249final%d'%len(rows))
 if r.get('words',999)<best[0]:best=(r['words'],v)
print('249',best[0]);(ROOT/'249DC-best.c').write_text(best[1])
(ROOT/'final_probes.json').write_text(json.dumps(rows,indent=2)+'\n')
