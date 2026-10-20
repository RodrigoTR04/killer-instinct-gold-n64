from sweep import *
def counters(s):
 start=s.index('    arg1 = D_801D309C;');end=s.index('    guTranslate',start)
 orig=s[start:end]
 for c,b,form,call,cmp in itertools.product(['counter','arg1','arg3','alpha'],['test','arg1','arg3','alpha'],range(6),range(3),range(3)):
  if c==b:continue
  decl=('    s32 counter;\n' if c=='counter' else '')+('    s32 test;\n' if b=='test' else '')
  p=[f'{b}',f'{b} != 0',f'{b} == 1'][cmp]
  callarg=['D_801D309C',c,c+' + 1'][call]
  core=f'position = func_801B19F0(-6.0f, -150.0f, {callarg}, 1);'
  if form==0:x=f'{c} = D_801D309C;\n{b} = {c} < 1;\n{c}++;\nif ({p}) {{\nD_801D309C = {c};\n{core}\n}} else {{\nD_801D309C = {c};\nposition = -150.0f;\n}}'
  elif form==1:x=f'{c} = D_801D309C;\n{b} = {c} < 1;\nD_801D309C = ++{c};\nif ({p}) {{\n{core}\n}} else {{\nposition = -150.0f;\n}}'
  elif form==2:x=f'{c} = D_801D309C++;\nif ({c} < 1) {{\n{core}\n}} else {{\nposition = -150.0f;\n}}'
  elif form==3:x=f'{c} = D_801D309C;\nif ({c}++ < 1) {{\nD_801D309C = {c};\n{core}\n}} else {{\nD_801D309C = {c};\nposition = -150.0f;\n}}'
  elif form==4:x=f'{c} = D_801D309C;\n{b} = {c} < 1;\n{c}++;\nif ({p}) {{\n{core}\n}} else {{\nposition = -150.0f;\n}}\nD_801D309C = {c};'
  else:x=f'if (D_801D309C++ < 1) {{\n{core}\n}} else {{\nposition = -150.0f;\n}}'
  # only behavior-equivalent call args
  if call==2 and form not in [2]:continue
  if call==1 and form in [2,5]:continue
  if call==2 and form==5:continue
  t=s[:start]+'    '+x.replace('\n','\n    ')+'\n'+s[end:]
  t=t.replace('    f32 position;',decl+'    f32 position;')
  yield str((c,b,form,call,cmp)),t
sweep('func_801B2010',counters)
