from probe import *
import itertools
s=Path('tools/scratch/nonmatching/T-032/func_800249DC.c').read_text();a=s.index('        i=0;');b=s.index('        *kind',a);rows=[];best=(10,s)
for style,swap in itertools.product(range(6),[0,1]):
 loops=[
 '''i=0; while(1) { i+=2; if(id==entry[0]) break; if(i>=14) {entry=start; break;} entry+=2; }''',
 '''i=0; do { i+=2; if(id==entry[0]) break; entry+=2; }while(i<14); if(i>=14 && id!=entry[0])entry=start;''',
 '''for(i=0;i<14;i+=2,entry+=2) {if(id==entry[0]) goto found;} entry=start; found:''',
 '''i=0; while(i<14) {i+=2; if(id==entry[0]) goto found; entry+=2;} entry=start; found:''',
 '''i=0; do {i+=2; if(id==entry[0]) goto found; entry+=2;}while(i<=13); entry=start; found:''',
 '''i=0; do {if(id==entry[0]) break; entry+=2; i+=2;}while(i<14); if(i>=14)entry=start;''']
 v=s[:a]+loops[style]+'\n'+s[b:]
 if swap:v=v.replace('start=D_80046010[D_8004EA9C[player]]; entry=start;', 'entry=D_80046010[D_8004EA9C[player]]; start=entry;')
 r=probe(v,'func_800249DC','search%d%d'%(style,swap));rows.append(r)
 print(style,swap,r['bytes'],r['words'])
 if r['words']<best[0]:best=(r['words'],v)
(ROOT/'249DC-best.c').write_text(best[1]);(ROOT/'searchloop.json').write_text(json.dumps(rows,indent=2)+'\n')
