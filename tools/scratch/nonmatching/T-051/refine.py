from probe import *
import itertools,re
rows=[]
def run(fn,s,tag):
 r=probe(s,fn,tag);rows.append({'function':fn,'variant':tag,**r});return r
p=Path('tools/scratch/nonmatching/T-032/func_800249DC.c');s=original(p)
start=s.index('        for (');end=s.index('        *kind=entry[1];',start)
loops=[s[start:end],'''        i=0;
        do {
            if (id==entry[0]) break;
            i+=2;
            entry+=2;
        } while(i<14);
        if(i==14) entry=start;
''','''        for(i=0;i<14;i+=2) {
            if(id==entry[0]) break;
            entry+=2;
        }
        if(i==14) entry=start;
''','''        i=0;
        do {
            i+=2;
            if(id==entry[0]) goto found;
            entry+=2;
        } while(i<14);
        entry=start;
found:
''']
best=(999,None)
for j,loop in enumerate(loops):
 for ty in ['s32','u32','u8']:
  v=(s[:start]+loop+s[end:]).replace('s32 i;',ty+' i;')
  r=run(p.stem,v,'249-%d-%s'%(j,ty))
  if r.get('words',999)<best[0]:best=(r['words'],v)
if best[0]<63:(ROOT/'249DC-best.c').write_text(best[1])
p=Path('tools/scratch/nonmatching/T-033/func_80015450.c');s=original(p);best=(999,None)
for local,compound,kind,active in itertools.product([0,1],[0,1],[0,1],[0,1]):
 v=s
 if local:
  v=v.replace('    T033RotatingObject *obj;','    T033RotatingObject *obj;\n    T033Rotation *rotation;').replace('        if (obj->kind == 0x3B) {','        if (obj->kind == 0x3B) {\n            rotation = &((T033Rotation *)&D_8004A9D8)[obj->index];')
  # keep first store/index separate, subsequent uses cached
  first=v.index('            while (');v=v[:first]+v[first:].replace('((T033Rotation *)&D_8004A9D8)[obj->index].','rotation->')
 if compound:v=v.replace('((T033Rotation *)&D_8004A9D8)[obj->index].yaw = ((T033Rotation *)&D_8004A9D8)[obj->index].yaw +','((T033Rotation *)&D_8004A9D8)[obj->index].yaw +=')
 if kind:v=v.replace('if (obj->kind == 0x3B) {','if (obj->kind != 0x3B) { obj++; continue; } {')
 if active:v=v.replace('if (obj->active != 0 &&','if (obj->active &&')
 r=run(p.stem,v,'154-%d%d%d%d'%(local,compound,kind,active))
 if r.get('words',999)<best[0]:best=(r['words'],v)
if best[0]<68:(ROOT/'15450-best.c').write_text(best[1])
p=Path('tools/scratch/nonmatching/T-020/func_80016760.c');s=original(p);
for size in [7,8,16]:
 v=s.replace('extern u8 D_8004A730[];', 'u8 D_8004A730[%d];'%size)
 run(p.stem,v,'167-defined%d'%size)
p=Path('tools/scratch/nonmatching/T-022/func_8001CBCC.c');s=original(p)
for ty in ['const f32','volatile f32','const volatile f32','f32 DUMMY[1];\nextern f32']:
 run(p.stem,s.replace('extern f32 D_80045C00;', 'extern '+ty+' D_80045C00;'),'cb-'+str(len(rows)))
(ROOT/'refine.json').write_text(json.dumps(rows,indent=2)+'\n')
for fn in sorted(set(x['function'] for x in rows)):
 print(fn,sorted((x.get('words',999),x['variant'],x.get('bytes')) for x in rows if x['function']==fn)[:6])
