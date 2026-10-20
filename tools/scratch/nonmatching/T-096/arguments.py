from context import *
from itertools import product
rows={}
for fn in ['func_801B6528','func_8002AA98','func_8002AAEC','func_8002F6F4']:
 s=(WORK/(fn+'.c')).read_text(); base=compile(fn,s); jobs=[]
 if fn=='func_801B6528':
  a,b,brace=extent(s,fn); body=s[a:b]; pos=body.index('    command = *arg0;',body.index('    guTranslate('))
  for name in ['arg2','arg3','card']:
   for typ in ['void *','T029Card *','s32']:
    t=body
    if name=='card': t=t.replace('    s32 index;', '    s32 index;\n '+typ+' card;')
    elif name=='arg3': t=t.replace('s32 arg3)',typ+' arg3)')
    cast='(s32)' if typ=='s32' else '('+typ+')'
    p=t.index('    command = *arg0;',t.index('    guTranslate('))
    t=t[:p]+name+' = '+cast+'arg1;\n'+t[p:].replace('arg1',name)
    jobs.append((name+'-'+typ,s[:a]+t+s[b:]))
 elif fn.endswith(('AA98','AAEC')):
  s=s.replace('extern void '+fn+'(s32);','extern void '+fn+'();')
  for count,name,typ in product([2,3,4],['scaled','volume'],['s32','u32']):
   params=['s32 volume']+[typ+' extra'+str(i) for i in range(1,count)]
   t=s.replace('(s32 volume)\n','('+', '.join(params)+')\n')
   dest='extra'+str(count-1)
   if name=='scaled':
    t=t.replace('  s32 scaled = D_80048140[D_80127CC9] * volume;', '  '+dest+' = D_80048140[D_80127CC9] * volume;').replace('scaled',dest)
   else:
    t=t.replace('  s32 scaled = D_80048140[D_80127CC9] * volume;', '  '+dest+' = volume;\n  s32 scaled = D_80048140[D_80127CC9] * '+dest+';')
   jobs.append((str((count,name,typ)),t))
 else:
  for typ in ['s32','u32','s64','u64','s16','u16']:
   jobs.append(('step-'+typ,s.replace('s32 step;',typ+' step;')))
  for expr in ['0','1']:
   jobs.append(('initialized-step-'+expr,s.replace('s32 step;','s32 step = '+expr+';')))
 for name,t in jobs:
  r=compile(fn,t,name); rows.setdefault(fn,[]).append(r); print(fn,r,flush=True)
  if r.get('words',999)<base.get('words',999): (WORK/(fn+'-argument-'+re.sub(r'[^\w-]','_',name)+'.c')).write_text(t)
(WORK/'arguments.json').write_text(json.dumps(rows,indent=2))
