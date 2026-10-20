from context import *
from itertools import product

def variants3(fn,s):
 a,b,brace=extent(s,fn); body=s[a:b]
 # Keep static code live without modifying function behavior (diagnostic data only).
 static=s[:a]+'static '+s[a:]
 static=re.sub(r'extern ([\w *]+) '+fn+r'\(([^;]*)\);',r'static \1 '+fn+r'(\2);',static)
 yield 'static-live',static+'\nvoid *t096_keep = (void *)&'+fn+';\n'
 if fn.endswith('B2010'):
  for storage,form in product(['extern s32','s32','static s32','extern volatile s32','static volatile s32'],range(5)):
   t=s.replace('extern s32 D_801D309C;',storage+' D_801D309C;')
   start=t.index('    arg1 = D_801D309C;',t.index('s32 '+fn)); end=t.index('    guTranslate(',start)
   pre=[
    'arg1 = D_801D309C; arg3 = arg1 < 1; ++arg1; if (arg3) { D_801D309C = arg1; position = func_801B19F0(-6.0f,-150.0f,arg1,1); } else { D_801D309C = arg1; position = -150.0f; }',
    'arg1 = D_801D309C++; if (arg1 < 1) position = func_801B19F0(-6.0f,-150.0f,arg1+1,1); else position = -150.0f;',
    'arg3 = D_801D309C++ < 1; arg1 = D_801D309C; if (arg3) position = func_801B19F0(-6.0f,-150.0f,arg1,1); else position = -150.0f;',
    'arg1 = D_801D309C; if (arg1++ < 1) { D_801D309C = arg1; position = func_801B19F0(-6.0f,-150.0f,arg1,1); } else { D_801D309C = arg1; position = -150.0f; }',
    'arg1 = D_801D309C; if (arg1 < 1) { position = func_801B19F0(-6.0f,-150.0f,D_801D309C = ++arg1,1); } else { D_801D309C = ++arg1; position = -150.0f; }'
   ][form]
   t=t[:start]+pre+'\n'+t[end:]
   yield 'counter-'+storage+'-'+str(form),t
  # Block-static declaration rather than file-static.
  t=s.replace('extern s32 D_801D309C;','')
  t=t[:brace+1]+'\n static s32 D_801D309C;\n'+t[brace+1:] if False else t.replace('    f32 position;','    static s32 D_801D309C;\n    f32 position;',1)
  yield 'counter-static-local',t
  # A K&R float function passes doubles unless a prototype is available.
  t=s.replace('extern f32 func_801B19F0(f32, f32, s32, s32);','')
  # Existing helper definition precedes us, so rename the call for a pure prototype probe.
  t=t[:a]+t[a:].replace('func_801B19F0(', 't096_lerp(')
  for proto in ['extern f32 t096_lerp();','extern f32 t096_lerp(f32,f32,s32,s32);','extern f32 t096_lerp(f32,f32,u32,u32);','extern f32 t096_lerp(f32,f32,s16,s16);']:
   yield 'lerp-'+proto,'#include "common.h"\n'+proto+'\n'+t
 if fn.endswith('80017378'):
  for symbol,typ in [('D_8004AA14','u8'),('D_8004A998','u8'),('D_8004A9D8','u8')]:
   for n in ['1','64','256']:
    t=re.sub(r'extern (?:u8|s8|s32|f32) '+symbol+r';','extern '+typ+' '+symbol+'['+n+'];',s)
    if t!=s: yield symbol+'-array-'+n,t
  start=body.index('    model = (void **)&D_8004A998;'); end=body.index('    func_8001C0E4(',start)
  old=body[start:end]
  for grouped,rotfirst,incfirst in product([False,True],[False,True],[False,True]):
   model='model += 4;\n model[-4] = &D_801A2080; model[-3] = 0; model[-2] = 0; model[-1] = 0;'
   rot='rot += 1;\n rot[-1].pitch = rot[-1].yaw = rot[-1].roll = rot[-1].speed = 0.0f;' if grouped else 'rot += 1;\n rot[-1].pitch = 0.0f; rot[-1].yaw = 0.0f; rot[-1].roll = 0.0f; rot[-1].speed = 0.0f;'
   if incfirst:
    model=model.replace('model += 4;',''); rot=rot.replace('rot += 1;',''); prefix='rot += 1; model += 4;'
   else: prefix=''
   init='model = (void **)&D_8004A998; rot = (T0331383CStageRotation *)&D_8004A9D8;'
   loop=init+'\n while (1) { '+prefix+(rot+model if rotfirst else model+rot)+'\n if ((u8 *)rot == &D_8004AA14) break; }\n'
   yield 'loop-'+str((grouped,rotfirst,incfirst)),s.replace(old,loop)
 if fn.endswith('2F6F4'):
  # Real event payload union alignment and unused payload size diagnostics.
  for extra in ['u64 align;','f64 align;','u8 bytes[20];','u8 bytes[24];','u8 bytes[12];']:
   t=s.replace('T024ChainEvent start;', 'union { T024ChainEvent event; '+extra+' } start;').replace('start.type','start.event.type').replace('start.voice','start.event.voice')
   yield 'event-union-'+extra,t
  for members in ['s32 step; s32 repeatTime; s16 repeat;','s16 repeat; s32 repeatTime; s32 step;','s32 repeatTime; s32 step; s16 repeat;']:
   t=s.replace('  s32 step;','').replace('  s32 repeatTime;','').replace('  s16 repeat = 0;','')
   t=t.replace('  T024ChainEvent start;', '  struct { '+members+' } timing;\n T024ChainEvent start;')
   a2,b2,br=extent(t,fn); t=t[:a2]+re.sub(r'\b(step|repeatTime|repeat)\b',r'timing.\1',t[a2:]).replace('timing.timing.','timing.')
   # Don't change member declarations; move type to file scope.
   t=t.replace('struct { '+re.sub(r'\b(step|repeatTime|repeat)\b',r'timing.\1',members)+' } timing;', 'struct { '+members+' } timing;')
   t=t.replace('  if (id == 0)', '  timing.repeat = 0;\n  if (id == 0)')
   yield 'timing-struct-'+members,t

def main():
 rows={}
 for n in FUNCTIONS[:8]+['801B2010','80017378','8002AA98','8002AAEC','8002F6F4']:
  fn='func_'+n; s=(WORK/(fn+'.c')).read_text(); base=compile(fn,s); rows[fn]=[base]
  def run(job):
   name,src=job; r=compile(fn,src,name)
   if r.get('words',999)<base.get('words',999): (WORK/(fn+'-storage-'+re.sub(r'[^\w-]','_',name)+'.c')).write_text(src)
   return r
  with ThreadPoolExecutor(max_workers=4) as pool:
   for r in pool.map(run,list(variants3(fn,s))): rows[fn].append(r); print(fn,r,flush=True)
 (WORK/'storage.json').write_text(json.dumps(rows,indent=2))
if __name__=='__main__': main()
