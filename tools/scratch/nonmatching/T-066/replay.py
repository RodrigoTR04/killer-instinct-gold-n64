import sys,re,itertools,json
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
fn='func_801C7CD0';p=tu.draft(fn);s=p.with_suffix('.t066-best').read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
def add(label,v):vs.append((label,v))
# Correct the verified music helper signature before probing.
s=s.replace('extern void func_801CD038(void *, s32);','extern u8 func_801CD038(s32, s32);').replace('func_801CD038(D_800F4070, replay - 1)','func_801CD038((s32)D_800F4070, replay - 1)').replace('extern void func_801C7A98();','extern void func_801C7A98(void);')
add('verified prototypes',s)
for typ in ['u64','s64']:
 for shape in ['array','struct','union','rows']:
  v=s.replace('extern u64 D_802D3678[2];','extern '+typ+' D_802D3678[2];')
  if shape=='struct':v=v.replace('extern '+typ+' D_802D3678[2];','extern struct { '+typ+' first, second; } D_802D3678;').replace('D_802D3678[0]','D_802D3678.first').replace('D_802D3678[1]','D_802D3678.second')
  if shape=='union':v=v.replace('extern '+typ+' D_802D3678[2];','extern union { '+typ+' pad[2]; u32 words[4]; } D_802D3678;').replace('D_802D3678[0]','D_802D3678.pad[0]').replace('D_802D3678[1]','D_802D3678.pad[1]')
  if shape=='rows':v=v.replace('extern '+typ+' D_802D3678[2];','extern '+typ+' D_802D3678[][1];').replace('D_802D3678[0]','D_802D3678[0][0]').replace('D_802D3678[1]','D_802D3678[1][0]')
  add(typ+shape,v)
 for point in ['    if (D_802D3E15)','    if (D_802D3A00 == 5)','        if (D_802D3E15 == 0)','        replay = D_802D3E15;','        D_802D3678[0]']:
  for expr in ['D_802D3678','&D_802D3678[0]']:
   v=s.replace('u32 replay;','u32 replay;\n '+typ+' *pads;').replace(point,'pads = '+expr+';\n'+point,1)
   k=v.index('void '+fn);v=v[:k]+v[k:].replace('        D_802D3678[','        pads[');add('pointer '+typ+point+expr,v)
for typ in ['s32','u32','unsigned long','signed long']:
 for const in ['0x1000','(u64)0x1000','0x1000ULL']:
  v=s.replace('u32 replay;',typ+' replay;').replace('= 0x1000;','= '+const+';');add(typ+const,v)
for label,v in vs:
 r=probe.probe(fn,pre+v)
 if r<best:best=r;p.with_suffix('.t066-best').write_text(v);print(label,r,flush=True)
print('final',len(vs),best)
(probe.ROOT/'tools/scratch/nonmatching/T-066/replay-results.json').write_text(json.dumps({'best':best,'tested':len(vs)}))
