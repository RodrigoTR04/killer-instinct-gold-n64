import sys,itertools,re
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
for fn in ['func_801B446C','func_801C7CD0','func_801C4E38','func_801B6528']:
 p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 if fn=='func_801B446C':
  for symbol in ['D_802C8CE0','D_802C8D06','D_802C8D0F','D_802C8D0C']:
   for size in ['','1']:
    v=s.replace(symbol,symbol+'[0]').replace('extern u8 '+symbol+'[0];','extern u8 '+symbol+'['+size+'];')
    vs.append((symbol+size,v))
 if fn=='func_801C7CD0':
  for mask,arity,wide in itertools.product(range(8),range(4),[False,True]):
   v=s
   for j,symbol in enumerate(['D_802D3E15','D_802D3A00','D_802D3A06']):
    if mask>>j&1:
     # split comma declaration then replace uses
     v=v.replace('extern u8 D_802D3A00, D_802D3A06, D_802D3E15;','extern u8 D_802D3A00; extern u8 D_802D3A06; extern u8 D_802D3E15;')
     v=v.replace(symbol,symbol+'[0]').replace('extern u8 '+symbol+'[0];','extern u8 '+symbol+'[];')
   if arity&1:v=v.replace('func_801ADAD4(s32, s32 *, s32 *, u8 *)','func_801ADAD4(s32)').replace('func_801ADAD4(40, &D_80295700, &D_802956FC, &D_802D3A00'+('[0]' if mask&2 else '')+')','func_801ADAD4(40)')
   if arity&2:v=v.replace('func_801CD038(void *, s32, s32 *, u8 *)','func_801CD038(void *, s32)').replace('func_801CD038(D_800F4070, replay - 1, &D_802956FC, &D_802D3A00'+('[0]' if mask&2 else '')+')','func_801CD038(D_800F4070, replay - 1)')
   if wide:v=v.replace('s32 D_802D3678[4]','u64 D_802D3678[2]').replace('D_802D3678[1] = 0x1000;\n        D_802D3678[0] = 0;\n        D_802D3678[3] = 0x1000;\n        D_802D3678[2] = 0;','D_802D3678[0] = 0x1000;\n        D_802D3678[1] = 0x1000;')
   vs.append((str((mask,arity,wide)),v))
 for name,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;p.write_text(v);print(fn,name,r,flush=True)
 print(fn,'final',len(vs),best,flush=True)
