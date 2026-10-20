import importlib.util
from pathlib import Path
import json
s=importlib.util.spec_from_file_location('score', 'tools/scratch/nonmatching/T-042/score.py'); m=importlib.util.module_from_spec(s); s.loader.exec_module(m)
base=Path('tools/scratch/nonmatching/T-038/func_80001564.c').read_text()
results=[]
variants={}
for typ,decl,access in [('struct','struct Length { u32 value; } lengths[288];','lengths[i++].value'),('array','u32 lengths[288][1];','lengths[i++][0]')]:
 v=base.replace('u32 lengths[288];',decl).replace('lengths[i++]',access).replace('func_80000960(lengths,','func_80000960((u32 *)lengths,')
 variants[typ]=v
for expr in ['lengths[i + 1 - 1]', '*(lengths + i)', 'lengths[i]']:
 for update in ['i++;','++i;']:
  import re
  v=re.sub(r'lengths\[i\+\+\] = (\d+);',lambda a:'{ '+expr+' = '+a[1]+'; '+update+' }',base)
  variants[expr+update]=v
# Independent four-element records express the fixed Huffman ranges directly.
for order in [(0,1,2,3),(1,2,3,0),(3,2,1,0)]:
 for kind in ['struct','array']:
  decl='struct Length { u32 a,b,c,d; } lengths[72];' if kind=='struct' else 'u32 lengths[72][4];'
  v=base.replace('u32 lengths[288];',decl).replace('func_80000960(lengths,','func_80000960((u32 *)lengths,')
  for bound,val in [(144,8),(256,9),(280,7),(288,8)]:
   stores=' '.join(('lengths[i].'+ 'abcd'[j] if kind=='struct' else 'lengths[i]['+str(j)+']')+' = '+str(val)+';' for j in order)
   v=v.replace('i < '+str(bound)+';) lengths[i++] = '+str(val)+';', 'i < '+str(bound//4)+'; i++) { '+stores+' }')
  v=v.replace('for (i = 0; i < 30;) lengths[i++] = 5;', 'for (i = 0; i < 30;) ((u32 *)lengths)[i++] = 5;')
  variants[str(order)+kind]=v
for op in ['!=', '<=', '<']:
 for step in [1,2,4]:
  for form in ['for','do']:
   v=base
   for init,bound,val in [(True,144,8),(False,256,9),(False,280,7),(False,288,8),(True,30,5)]:
    if step>1 and bound==30: continue
    old='for ('+('i = 0' if init else '')+'; i < '+str(bound)+';) lengths[i++] = '+str(val)+';'
    cond='i '+op+' '+str(bound-1 if op=='<=' else bound)
    body=' '.join('lengths[i++] = '+str(val)+';' for _ in range(step))
    new=('i = 0; ' if init else '') + ('for (; '+cond+';) { '+body+' }' if form=='for' else 'do { '+body+' } while ('+cond+');')
    v=v.replace(old,new)
   variants[f'{op}-{step}-{form}']=v
for width in [2,4]:
 v=base.replace('u32 lengths[288];','union { u32 words[288]; u64 pairs[144]; } storage;\n#define lengths storage.words')
 for bound,val in [(144,8),(256,9),(280,7),(288,8)]:
  if width==2: body=f'storage.pairs[i / 2] = ((u64){val} << 32) | {val}; i += 2;'
  else: body=f'lengths[i+1] = {val}; lengths[i+2] = {val}; lengths[i+3] = {val}; lengths[i] = {val}; i += 4;'
  v=v.replace(f'i < {bound};) lengths[i++] = {val};',f'i < {bound};) {{ {body} }}')
 variants[f'pair-{width}']=v
for name,v in variants.items():
 try:r=m.score(v,'func_80001564')
 except Exception as e: r={'error':str(e)}
 results.append({'variant':name,**r})
 if r.get('match'): Path('tools/scratch/nonmatching/T-049/matched.c').write_text(v)
print(json.dumps(results,indent=2))
