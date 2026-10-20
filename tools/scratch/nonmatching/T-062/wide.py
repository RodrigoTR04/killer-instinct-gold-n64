import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
for fn in ['func_801B446C','func_801B6528','func_801C7CD0']:
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 if fn=='func_801B446C':
  for ft,bt,ct in itertools.product(['s32','u32','u64','s64'],repeat=3):
   vs.append((ft+bt+ct,s.replace('s32 flags;',ft+' flags;').replace('s32 bit;',bt+' bit;').replace('s32 choice;',ct+' choice;')))
 if fn=='func_801B6528':
  for typ in ['u64','s64']:
   v=s.replace('s32 index;',typ+' index;');vs.append(('local'+typ,v))
  for ty in ['u32','s32','u64','s64']:
   for place in ['before','after']:
    v=s.replace('s32 index;', 's32 index;\n    '+ty+' address;')
    point='    guTranslate(arg2, 0.0f, y, 0.0f);' if place=='before' else '    command = *arg0;'
    v=v.replace(point,'    address = ('+ty+')arg1;\n'+point,1)
    a,b=v.split('address = ('+ty+')arg1;',1);b=b.replace('((T029Card *)arg1)','((T029Card *)(u32)address)');vs.append(('address'+ty+place,a+'address = ('+ty+')arg1;'+b))
 if fn=='func_801C7CD0':
  for rt in ['s32','u32','s64','u64','u8']:
   for pt in ['u8','u32','s32','u64','s64']:
    v=s.replace('u8 replay;',rt+' replay;').replace('func_801C7CD0(u8 arg0)', 'func_801C7CD0('+pt+' arg0)');vs.append(('mode/replay'+pt+rt,v))
 for name,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;p.write_text(v);print(fn,name,r,flush=True)
 print(fn,'final',len(vs),best,flush=True)
