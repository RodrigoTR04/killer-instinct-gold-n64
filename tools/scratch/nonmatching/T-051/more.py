from probe import *
import itertools
rows=[]
def run(fn,s,tag):
 r=probe(s,fn,tag);rows.append({'function':fn,'variant':tag,**r});return r
p=Path('tools/scratch/nonmatching/T-032/func_800249DC.c');s=Path('tools/scratch/nonmatching/T-032/func_800249DC.c').read_text();best=(10,s)
for typ,decl,cond,loop,inc in itertools.product(['s32','u32','s16'],[0,1,2],['i<14','i!=14','i<=12'],[0,1,2],[0,1]):
 v=s.replace('s32 i;',typ+' i;').replace('while(i<14)','while('+cond+')')
 if decl==1:v=v.replace('u8 *entry,*start;', 'u8 *start,*entry;')
 if decl==2:v=v.replace('start=D_80046010[D_8004EA9C[player]]; entry=start;', 'entry=D_80046010[D_8004EA9C[player]]; start=entry;')
 if loop==1:v=v.replace('            i+=2;\n            if(id==entry[0]) goto found;', '            if(id==entry[0]) goto found;\n            i+=2;')
 if loop==2:v=v.replace('        i=0;\n        do {','        for(i=0;i<14;i+=2) {').replace('            i+=2;\n','').replace('        } while('+cond+');','        }')
 if inc:v=v.replace('entry+=2;', 'entry++; entry++;')
 r=run(p.stem,v,'249more%d'%len(rows))
 if r.get('words',999)<best[0]:best=(r['words'],v);print('best249',best[0],r['bytes'],len(rows))
(ROOT/'249DC-best.c').write_text(best[1])
# remaining large switch drafts: reconcile standalone declarations, then probe signed dispatch forms.
for task,n in [('T-033','1178C'),('T-033','12B7C'),('T-033','1346C'),('T-032','21B6C'),('T-032','26B38'),('T-035','42198')]:
 p=Path('tools/scratch/nonmatching')/task/('func_800'+n+'.c');s=p.read_text()
 if n=='1178C':s='extern u8 D_8004EA9C[];\n'+s
 if n=='26B38':s='extern s32 D_800614C0;\nextern u8 D_800614C8;\n'+s
 if n=='21B6C':
  context=Path('src/main/main_2FF0.c').read_text();a=context.index('typedef struct {',context.index('void func_8001E0B4') if 'void func_8001E0B4' in context else context.index('} T022DmaEntry;'))
  # fetch exact sprite definition
  b=context.index('} T022Sprite;')+len('} T022Sprite;');a=context.rfind('typedef struct',0,b);s=context[a:b]+'\n'+s
 best=(999,None)
 import re
 for mode in [0,1,2]:
  v=s
  if mode==1:v=re.sub(r'switch \(([^\n]+)\) \{',r'switch ((u32)(\1)) {',v)
  if mode==2:v=re.sub(r'switch \(([^\n]+)\) \{',r'switch ((s32)(\1)) {',v)
  r=run(p.stem,v,n+'-switch%d'%mode)
  if r.get('words',999)<best[0]:best=(r['words'],v)
 print(n,{k:v for k,v in rows[-3].items() if k!='offsets'})
 if best[1]:(ROOT/(n+'-candidate.c')).write_text(best[1])
(ROOT/'more.json').write_text(json.dumps(rows,indent=2)+'\n')
