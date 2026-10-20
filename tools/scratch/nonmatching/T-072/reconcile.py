import re

def reconcile(fn,s):
 if fn.endswith('2F45C'):
  s=s.replace('extern T024AllocationLists D_80048270;','').replace('D_80048270.', '((T024AllocationLists *)&D_80048270)->')
 if fn.endswith('15F6C'):
  s=s.replace('extern u8 D_80044E4C[], D_8004ACD0[];','').replace('extern s32 func_800326F0(void);','').replace('D_80044E4C[','(&D_80044E4C)[')
 if fn.endswith('18F20'):
  for name in ['D_8004A5E0','D_8004A738','D_8004AC89','D_8004AC8A','D_800614D8','D_80061CB8']:
   s=re.sub(r'extern (?:s8|u8) '+name+r';','',s)
  s=s.replace('D_8004A738 =','D_8004A738[0] =')
 if fn.endswith('191F0'):s=s.replace('extern u8 D_801D3430;','').replace('&D_801D3430','(u8 *)D_801D3430')
 if fn.endswith('1BB64'):
  s=s.replace('D_801D7DF8,D_8004AC92,D_8004AC8E;','D_801D7DF8;').replace('&D_8004AC92','D_8004AC92').replace('(&D_8004AC8E)','D_8004AC8E')
 if fn.endswith('1D47C'):
  s=s.replace('extern u8 D_8004CE90[];','').replace('+ D_8004CE90','+ (u8 *)D_8004CE90')
 return s
