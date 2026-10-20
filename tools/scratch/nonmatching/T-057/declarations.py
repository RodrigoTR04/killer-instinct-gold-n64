from sweep import *
def variants(s):
 # Permute local declarations, using reproducible random order for large sets.
 body=s.index(' {',s.index('\ns32 func_'))+2 if '\ns32 func_' in s else s.index(' {',s.index('\nu32 func_'))+2
 end=s.index('\n    if ',body)
 declarations=s[body:end]
 lines=[x for x in declarations.splitlines() if x.strip()]
 rng=random.Random(57)
 for i in range(450):
  rng.shuffle(lines)
  yield 'decl'+str(i),s[:body]+'\n'+'\n'.join(lines)+'\n'+s[end:]
 for ty in ['f32','f64']:
  for at in ['s32','u32','u8','u16','s16']:
   yield str((ty,at)),s.replace('f32 position;',ty+' position;').replace('s32 alpha;',at+' alpha;')
 for p in ['s32','u32','s16','u16']:
  for q in ['s32','u32','s16','u16']:
   yield str((p,q)),s.replace('s32 arg1,',p+' arg1,').replace('s32 arg3)',q+' arg3)')
for n in ['func_801B2010','func_801B2EF4','func_801C6A80','func_801B6A68']:
 sweep(n,variants)
