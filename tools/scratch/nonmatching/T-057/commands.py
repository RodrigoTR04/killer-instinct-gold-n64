from sweep import *
def commands(s):
 yield from gfx(s)
 # Declaration scope/lifetime and word order, command expressions.
 names=re.findall(r'\b(?:command\d+|p\d+) = \(\*arg0\)\+\+;',s)
 for i in range(11):
  for mode in range(5):
   t=s
   v='command'+str(i)
   if mode==0:t=t.replace(v+' = (*arg0)++;',v+' = *arg0;\n        *arg0 = '+v+' + 1;')
   elif mode==1:t=t.replace('arg2 << 9','arg2 * 512').replace('D_802C8D08[arg2] * 2','(D_802C8D08[arg2] << 1)')
   elif mode==2:t=t.replace('D_802C8808 + (arg2 << 9) + D_802C8D08[arg2] * 2','D_802C8808 + ((arg2 << 8) + D_802C8D08[arg2]) * 2')
   elif mode==3:t=t.replace('D_802C8808 + (arg2 << 9) + D_802C8D08[arg2] * 2','D_802C8808 + D_802C8D08[arg2] * 2 + (arg2 << 9)')
   else:t=t.replace('u32 w0, w1;','s32 w0, w1;')
   yield str((i,mode)),t
 for n in range(11):
  # reusable cursor groups, leaving other distinct pointers intact
  for k in range(n+1,11):
   yield str(('merge',n,k)),re.sub(r'\bcommand'+str(k)+r'\b','command'+str(n),s).replace('    T029Gfx801B6A68 *command'+str(n)+';\n','',1)
for n in ['func_801B2010','func_801B2EF4','func_801B6A68']:
 sweep(n,commands)
