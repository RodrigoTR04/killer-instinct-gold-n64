from context import *
from itertools import product
rows={}
for fn in ['func_8002AA98','func_8002AAEC']:
 s=(WORK/(fn+'.c')).read_text(); a,b,brace=extent(s,fn); body=s[a:b]
 for mode,typ in product(range(7),['s32','u32','s16']):
  pre=body[:body.index('  s16 narrowed;')]
  ptr='D_800669C0' if fn.endswith('AA98') else 'D_800669C4'
  code=[
   f's16 narrowed; volume = D_80048140[D_80127CC9] * volume; volume >>= 16; narrowed = volume; alCSPSetVol({ptr}, narrowed);',
   f's16 narrowed; volume = D_80048140[D_80127CC9] * volume; narrowed = volume >> 16; alCSPSetVol({ptr}, narrowed);',
   f'{typ} scaled; s16 narrowed; scaled = volume; scaled = D_80048140[D_80127CC9] * scaled; scaled >>= 16; narrowed = scaled; alCSPSetVol({ptr}, narrowed);',
   f'{typ} scaled; s16 narrowed; scaled = D_80048140[D_80127CC9] * volume; volume = scaled >> 16; narrowed = volume; alCSPSetVol({ptr}, narrowed);',
   f'{typ} scaled; s16 narrowed; scaled = D_80048140[D_80127CC9] * volume; volume = scaled; narrowed = volume >> 16; alCSPSetVol({ptr}, narrowed);',
   f's16 narrowed; {{ {typ} scaled = D_80048140[D_80127CC9] * volume; narrowed = scaled >> 16; }} alCSPSetVol({ptr}, narrowed);',
   f'{typ} scaled; scaled = D_80048140[D_80127CC9] * volume; {{ s16 narrowed = scaled >> 16; alCSPSetVol({ptr}, narrowed); }}'
  ][mode]
  for layout in [0,1]:
   t=s[:a]+pre+code.replace(';',';\n' if layout else ';')+'\n}'+s[b:]
   name=str((mode,typ,layout)); r=compile(fn,t,name); rows.setdefault(fn,[]).append(r); print(fn,r,flush=True)
   if r.get('words',999)<2: (WORK/(fn+'-volume-'+str(mode)+'-'+typ+'-'+str(layout)+'.c')).write_text(t)
(WORK/'volume.json').write_text(json.dumps(rows,indent=2))
