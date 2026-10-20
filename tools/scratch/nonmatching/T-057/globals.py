from sweep import *
def variants(s):
 globals=re.findall(r'extern (?:u8|u32|s32) (D_\w+);',s)
 for bits in itertools.product(range(3),repeat=min(len(globals),7)):
  t=s
  for g,b in zip(globals,bits):
   if b==1:
    t=re.sub(r'extern (u8|u32|s32) '+g+';',r'extern \1 '+g+'[];',t)
    # replace uses excluding declaration and address-of
    t=re.sub(r'(?<!&)\b'+g+r'\b(?!\[\])',g+'[0]',t)
   if b==2:
    t=re.sub(r'extern (u8|u32|s32) '+g+';',r'extern volatile \1 '+g+';',t)
  yield str(bits),t
 for a,b in itertools.product(range(4),range(4)):
  t=s
  if a==1:t=t.replace('D_802D3984 += 1;','D_802D3984 = 1;')
  if a==2:t=t.replace('D_802D3984 += 1;','temp_t9 = D_802D3984; D_802D3984 = temp_t9 + 1;')
  if a==3:t=t.replace('D_802D3984 += 1;','++D_802D3984;')
  if b==1:t=t.replace('D_802921D4 = var_v0;','if (var_v0 == 0x930) D_802921D4 = var_v0; else D_802921D4 = var_v0;')
  if b==2:t=t.replace('if (var_v0 >= 0xA01U)', 'if (var_v0 > 0xA00U)')
  if b==3:t=t.replace('D_802921D4 = var_v0;','D_802921D4 = (u32)var_v0;')
  yield str((a,b)),t
sweep('func_801C6A80',variants)
