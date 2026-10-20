from sweep import *
def layouts(s):
 for decl,access in [('typedef union { struct { u32 w0, w1; } words; u64 force; } T021Gfx;','words.'),('typedef struct { u32 words[2]; } T021Gfx;','array'),('typedef union { struct { u32 w0, w1; } words; f64 force; } T021Gfx;','words.')]:
  t=s.replace('typedef struct { u32 w0, w1; } T021Gfx;',decl)
  t=re.sub(r'->w([01])',lambda m:'->words['+m[1]+']' if access=='array' else '->'+access+'w'+m[1],t)
  yield decl,t
 for delta in [-65536,-32768,-16,-8,-4,-1,1,4,8,16,32768,65536]:
  # Equivalent linker symbol plus canceling byte offset; normally folds away.
  yield str(delta),s.replace('(u32) &D_4AC40',f'(u32)(&D_4AC40 + ({delta})) - ({delta})')
 for a,b in itertools.product(['u32','s32','void *','u8 *'],range(5)):
  t=s.replace('    T021Gfx *p0',f'    {a} address;\n    u32 opcode;\n    T021Gfx *p0')
  val='(u32)&D_4AC40' if a in ['u32','s32'] else '&D_4AC40'
  assignments=[f'address = {val};','opcode = 0x01030040;','p0 = (*arg0)++;','p0->w0 = opcode;','p0->w1 = (u32)address;']
  for perm in itertools.permutations(assignments[:3]):
   body='    '+'\n    '.join(list(perm)+assignments[3:])
   u=t.replace('    p0 = (*arg0)++;\n    p0->w0 = 0x01030040;\n    p0->w1 = (u32) &D_4AC40;',body)
   yield str((a,b,perm)),u
sweep('func_801C51F8',layouts)
