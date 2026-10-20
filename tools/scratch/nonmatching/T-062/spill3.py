import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C4E38';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
vs=[]
for typ in ['s32','u32','s64','u64','s16','u16','s8','u8']:
 for style in range(5):
  v=s
  expr='('+typ+')arg0'
  if style==0:v=v.replace('switch (arg0)','switch ('+expr+')')
  if style==1:v=v.replace('if (arg0 >= 11)','if ('+expr+' >= 11)').replace('switch (arg0)','switch ('+expr+')').replace('if (arg0 == 5)','if ('+expr+' == 5)')
  if style>=2:
   point=['','','    D_8004AC88 = D_802D3985;','    switch (arg0)','    if (arg0 >= 11)'][style]
   v=v.replace('        D_802D3985 = arg0;',typ+' mode;\n        D_802D3985 = arg0;').replace(point,'    mode = arg0;\n'+point)
   v=v.replace('switch (arg0)','switch (mode)').replace('if (arg0 == 5)','if (mode == 5)')
   if style==4:v=v.replace('if (arg0 >= 11)','if (mode >= 11)')
  vs.append((typ+str(style),v))
# Local zero used to reset globals, with types that can retain an eight-byte expression.
for typ in ['u64','s64','f64','u32','s32']:
 for pos in ['        D_802D3985 = arg0;','    D_8004AC88 = D_802D3985;']:
  v=s.replace('        D_802D3985 = arg0;',typ+' zero;\n        D_802D3985 = arg0;').replace(pos,'    zero = 0;\n'+pos).replace('D_80295700 = D_802956FC = D_802956F8 = 0;','D_80295700 = D_802956FC = D_802956F8 = zero;');vs.append(('zero'+typ+pos,v))
for name,v in vs:
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,name,r,flush=True)
print('final',n,best)
