from sweep import *
def variants(s):
 old='    p0 = (*arg0)++;\n    p0->w0 = 0x01030040;\n    p0->w1 = (u32) &D_4AC40;'
 for ty,expr,order,ptr in itertools.product(['u32','s32','u64'],range(8),range(4),range(3)):
  t=s.replace('    T021Gfx *p0','    '+ty+' cmd;\n    u32 addr;\n    T021Gfx *p0')
  ex=['0x01030040','0x01030000 | 0x40','0x01030000 + 0x40','(u32)0x01030040','(s32)0x01030040','0x01030040UL','0x01030040LL','(u32)(u64)0x01030040'][expr]
  alloc=['p0 = (*arg0)++;','p0 = *arg0; *arg0 += 1;','p0 = *arg0; *arg0 = (T021Gfx *)((u8 *)p0 + 8);'][ptr]
  assigns=['cmd = '+ex+';','addr = (u32)&D_4AC40;',alloc]
  for perm in itertools.permutations(assigns):
   stores=['p0->w0 = cmd;','p0->w1 = addr;']
   if order&1:stores.reverse()
   if order&2:stores=['((u32 *)p0)[0] = cmd;','((u32 *)p0)[1] = addr;']
   yield str((ty,expr,order,ptr,perm)),t.replace(old,'    '+'\n    '.join(list(perm)+stores))
sweep('func_801C51F8',variants)
