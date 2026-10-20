from sweep import *
def near(s):
 for decl,addr in [('extern u8 D_4AC40[];','D_4AC40'),('extern u32 D_4AC40;','&D_4AC40'),('extern u32 D_4AC40[];','D_4AC40'),('extern void D_4AC40(void);','D_4AC40'),('extern u8 D_4AC40;','&D_4AC40')]:
  t=s.replace('extern u8 D_4AC40;',decl).replace('&D_4AC40',addr)
  for order in range(6):
   for ty in ['u32','s32','void *','u8 *']:
    a='    p0->w0 = 0x01030040;\n    p0->w1 = (u32) '+addr+';'
    val='(u32)'+addr if ty in ['u32','s32'] else addr
    decl2='    '+ty+' address;\n'
    exprs=[a,'    p0->w1 = (u32) '+addr+';\n    p0->w0 = 0x01030040;',f'    address = {val};\n    p0->w0 = 0x01030040;\n    p0->w1 = (u32)address;',f'    address = {val};\n    p0->w1 = (u32)address;\n    p0->w0 = 0x01030040;',f'    p0->w0 = 0x01030040;\n    address = {val};\n    p0->w1 = (u32)address;',f'    address = {val};\n    p0->w0 = 0x01030040;\n    p0->w1 = (u32)address;']
    u=t.replace(a,exprs[order]).replace('    T021Gfx *p0',decl2+'    T021Gfx *p0')
    if order==5:u=u.replace('    p0 = (*arg0)++;\n    address = '+val+';', '    address = '+val+';\n    p0 = (*arg0)++;')
    yield str((decl,order,ty)),u
 for field in ['u32','s32','volatile u32']:
  yield field,s.replace('u32 w0, w1;',field+' w0, w1;')
 # N64 command macros use field assignments through a cached packet pointer.
 for ty in ['u64','long long','double']:
  yield ty,s.replace('typedef struct { u32 w0, w1; }','typedef struct { u32 w0, w1; }')
sweep('func_801C51F8',near)
