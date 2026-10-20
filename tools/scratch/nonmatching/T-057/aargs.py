from sweep import *
def variants(s):
 old='    arg1 = D_801D309C;\n    arg3 = arg1 < 1;\n    arg1++;\n    D_801D309C = arg1;\n    if (arg3 == 1) {'
 for ty,form in itertools.product(['s32','u32','s16','u16'],range(8)):
  x=['if (D_801D309C++ < 1) {','if (++D_801D309C <= 1) {','counter = D_801D309C;\nif (counter++ < 1) {\nD_801D309C = counter;','counter = D_801D309C;\nif (counter < 1) {\nD_801D309C = counter + 1;','test = D_801D309C < 1;\ncounter = ++D_801D309C;\nif (test) {','counter = D_801D309C++;\nif (counter < 1) {','counter = D_801D309C;\ntest = counter++ < 1;\nif (test) {\nD_801D309C = counter;','test = D_801D309C++ < 1;\nif (test) {'][form]
  t=s.replace(old,'    '+x).replace('    f32 position;','    '+ty+' counter;\n    s32 test;\n    f32 position;')
  if form in [2,3,6]:t=t.replace('    } else {\n        position','    } else {\n        D_801D309C = '+('counter + 1' if form==3 else 'counter')+';\n        position',1)
  for proto in range(8):
   u=t
   if proto&1:u=u.replace('f32, f32, s32, s32);','f32, f32, u32, s32);')
   if proto&2:u=u.replace('f32, f32, s32, s32);','f32, f32, s32, u32);')
   if proto&4:u=u.replace('f32, f32, s32, s32);','f32, f32, s16, s16);')
   yield str((ty,form,proto)),u
sweep('func_801B2010',variants)
