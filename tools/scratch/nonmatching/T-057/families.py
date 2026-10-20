from sweep import *
def familyA(s):
 old='''    arg1 = D_801D309C;
    arg3 = arg1 < 1;
    arg1++;
    D_801D309C = arg1;
    if (arg3 == 1) {'''
 for ct,bt,c,b,placement,cond in itertools.product(['s32','u32','s16','u16'],['s32','u32'],['counter','arg1','arg3'],['test','arg1','arg3'],range(4),range(4)):
  if c==b:continue
  decl=('    '+ct+' counter;\n' if c=='counter' else '')+('    '+bt+' test;\n' if b=='test' else '')
  x=f'    {c} = D_801D309C;\n    {b} = {c} < 1;\n    {c}++;\n'
  pred=[b,b+' != 0',b+' == 1','!('+b+' == 0)'][cond]
  if placement==0:x+=f'    D_801D309C = {c};\n    if ({pred}) {{'
  elif placement==1:x+=f'    if ({pred}) {{\n        D_801D309C = {c};'
  elif placement==2:x=f'    {c} = D_801D309C++;\n    if ({c} < 1) {{'
  else:x=f'    if (({c} = D_801D309C++) < 1) {{'
  t=s.replace('    f32 position;',decl+'    f32 position;').replace(old,x)
  if placement==1:t=t.replace('    } else {\n        position',f'    }} else {{\n        D_801D309C = {c};\n        position',1)
  yield str((ct,bt,c,b,placement,cond)),t

def familyB(s):
 for ty,ct,expr,cond in itertools.product(['u8','u16','u32','s32'],['u8','u16','u32','s32'],range(6),range(4)):
  t=s.replace('u8 alpha;',ty+' alpha;').replace('u16 color;',ct+' color;')
  forms=['D_801D30C0++ < 10','(counter = D_801D30C0++) < 10','(counter = D_801D30C0, D_801D30C0 = counter + 1, counter < 10)','(arg1 = D_801D30C0++) < 10','(arg3 = D_801D30C0++) < 10','(D_801D30C0 += 1) <= 10']
  t=t.replace('D_801D30C0++ < 10',forms[expr]).replace('    u8 alpha;', '    u8 alpha;')
  if expr in [1,2]:t=t.replace('    '+ty+' alpha;','    s32 counter;\n    '+ty+' alpha;')
  if cond==1:t=t.replace('color = value & 0xFF;','color = (u8)value;')
  if cond==2:t=t.replace('alpha = value & 0xFF;','alpha = color;')
  if cond==3:t=t.replace('value = (u32) func_801B19F0','value = (s32) func_801B19F0')
  yield str((ty,ct,expr,cond)),t

def phase(s):
 for ty,init,proto,inv in itertools.product(['u8','u32','s32','s16'],range(5),range(4),range(2)):
  t=s.replace('s32 temp_v0;',ty+' temp_v0;')
  old='D_802D399C += D_802D399D;\n        temp_v0 = D_802D399C;'
  forms=[old,'temp_v0 = (D_802D399C += D_802D399D);','temp_v0 = (u8)(D_802D399C + D_802D399D);\n        D_802D399C = temp_v0;','temp_v0 = D_802D399C;\n        temp_v0 += D_802D399D;\n        D_802D399C = temp_v0;','D_802D399C = D_802D399C + D_802D399D;\n        temp_v0 = D_802D399C;']
  t=t.replace(old,forms[init])
  if proto&1:t=t.replace('func_8002A8C4();','func_8002A8C4(void *);')
  if proto&2:t=t.replace('func_8002F6F4();','func_8002F6F4(s32, s32, void *);')
  if inv:t=t.replace('if (temp_v0 >= 0xB)', 'if (temp_v0 > 10)').replace('if (temp_v0 < 2)', 'if (temp_v0 <= 1)')
  yield str((ty,init,proto,inv)),t
for n,g in [('func_801B2010',familyA),('func_801B2EF4',familyB),('func_801C6A80',phase)]:
 sweep(n,g)
