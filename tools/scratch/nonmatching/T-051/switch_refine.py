from probe import *
import re,itertools
rows=[]
p=Path('tools/scratch/nonmatching/T-033/func_8001346C.c');s=p.read_text();a=s.index('    if (mode == 1 || mode == 2) {');b=s.index('    if ((part->flags',a);draw=s[a+len('    if (mode == 1 || mode == 2) {'):b].rsplit('    }',1)[0]
best=(170,s)
for placement,typ in itertools.product([0,1],[0,1]):
 v=s[:a]+s[b:]
 if placement==0:v=v.replace('case 1: transformed = 0; break;\n    case 2: transformed = 1; break;', 'case 1: transformed = 0; goto draw;\n    case 2: transformed = 1;\n    draw:'+draw+'\n        break;')
 else:v=v.replace('case 1: transformed = 0; break;', 'case 1: transformed = 0;'+draw+'break;').replace('case 2: transformed = 1; break;', 'case 2: transformed = 1;'+draw+'break;')
 if typ:v=v.replace('mode = part->flags & 15;', 'mode = (u32)(part->flags & 15);')
 r=probe(v,p.stem,'134-ref%d'%len(rows));rows.append(r);print('134',placement,typ,{k:v for k,v in r.items() if k!='offsets'})
 if r.get('words',999)<best[0]:best=(r['words'],v)
if best[0]<170:(ROOT/'1346C-best.c').write_text(best[1])
# 12B7C: change fallthrough/common cases and dispatch type without changing case bodies.
p=Path('tools/scratch/nonmatching/T-033/func_80012B7C.c');s=p.read_text();best=(387,s)
for typ in ['s32','u32','u8']:
 v=s.replace('switch (D_8004AC88)', 'switch (('+typ+')D_8004AC88)')
 r=probe(v,p.stem,'12-ref'+typ);rows.append(r);print('12',typ,r['bytes'],r['words'])
 if r['words']<best[0]:best=(r['words'],v)
if best[0]<387:(ROOT/'12B7C-best.c').write_text(best[1])
(ROOT/'switch_refine.json').write_text(json.dumps(rows,indent=2)+'\n')
