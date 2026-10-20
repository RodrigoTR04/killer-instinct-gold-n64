from probe import *
import itertools,json
rows=[]
def run(fn,s,tag):
 r=probe(s,fn,tag);rows.append({'function':fn,'variant':tag,**r});return r
s=Path('tools/scratch/nonmatching/T-022/func_8001CBCC.c').read_text()
for decl in ['f32 D_80045C00 = 0.017453292f;', 'const f32 D_80045C00 = 0.017453292f;', 'extern f32 D_80045C00[1];']:
 v=s.replace('extern f32 D_80045C00;',decl)
 if '[1]' in decl:v=v.replace('*= D_80045C00;', '*= D_80045C00[0];')
 print('cb',decl,run('func_8001CBCC',v,'cbdefined%d'%len(rows)))
s=Path('tools/scratch/nonmatching/T-035/func_80042198.c').read_text();best=(130,s)
for expr,typ,casereorder in itertools.product(['p & 7','(u32)p % 8','p % 8','(u8)(p & 7)','p - ((p >> 3) << 3)'],['s32','u32'],[0,1]):
 v=s.replace('switch (p & 7)', 'switch ('+expr+')').replace('s32 p =',typ+' p =')
 if casereorder:
  a=v.index('        case 2:');b=v.index('        case 4:');parts=v[a:b].split('        case 3:');v=v[:a]+'        case 3:'+parts[1]+parts[0]+v[b:]
 r=run('func_80042198',v,'421-%d'%len(rows))
 if r.get('words',999)<best[0]:best=(r['words'],v);print('421best',r['words'],r['bytes'])
(ROOT/'42198-best.c').write_text(best[1])
# search loop with independent exit counter preserves signed bounds check
s=Path('tools/scratch/nonmatching/T-032/func_800249DC.c').read_text();best=(10,s)
for init,step,cond,swap in itertools.product(['0','-2','14'],['i+=2','i++','i-=2'],['i<14','i<=12','i>0'],[0,1]):
 v=s.replace('i=0;', 'i='+init+';').replace('i+=2;',step+';').replace('i<14',cond)
 if swap:v=v.replace('u8 *entry,*start;', 'u8 *start,*entry;').replace('start=D_80046010[D_8004EA9C[player]]; entry=start;', 'entry=D_80046010[D_8004EA9C[player]]; start=entry;')
 # Only retain behavior-equivalent forms
 if (init,step,cond) not in [('0','i+=2','i<14'),('0','i+=2','i<=12'),('14','i-=2','i>0')]:continue
 r=run('func_800249DC',v,'249target-%d'%len(rows))
 if r.get('words',999)<best[0]:best=(r['words'],v);print('249best',r)
(ROOT/'targeted.json').write_text(json.dumps(rows,indent=2)+'\n')
