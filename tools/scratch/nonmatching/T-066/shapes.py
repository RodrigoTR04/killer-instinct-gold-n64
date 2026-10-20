import sys,re,json,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
res={}
for addr in ['801B695C','801B446C','801C7CD0','801C35D8','801C4E38','801B6528','801C51F8']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);base=best;vs=[]
 def add(label,v,ctx=pre):vs.append((label,ctx,v))
 if addr=='801B695C':
  for typ,width in [('u8',1),('u16',2),('u32',4),('u64',8)]:
   for style in range(4):
    v=s.replace('extern u8 D_802C8808[];',f'extern {typ} D_802C8808[][{512//width}];')
    if style==0:
     v=v.replace('offset = arg1 << 9;','offset = arg1;').replace('D_802C8808 + *bank * 2 + offset + 0x100',f'&D_802C8808[offset][(*bank * 2 + 0x100) / {width}]').replace('D_802C8808 + *bank * 2 + offset',f'&D_802C8808[offset][*bank * 2 / {width}]')
    elif style==1:
     v=v.replace('D_802C8808 + *bank * 2 + offset + 0x100',f'&D_802C8808[arg1][(*bank * 2 + 0x100) / {width}]').replace('D_802C8808 + *bank * 2 + offset',f'&D_802C8808[arg1][*bank * 2 / {width}]').replace('offset = arg1 << 9;','')
    else:
     v=v.replace('D_802C8808 + *bank * 2 + offset + 0x100',f'(u8 *)D_802C8808 + *bank * 2 + offset + 0x100').replace('D_802C8808 + *bank * 2 + offset,',f'(u8 *)D_802C8808 + *bank * 2 + offset,')
     if style==3:v=v.replace('s32 offset;','u32 offset;')
    add('palette row '+typ+str(style),v)
  # source frame table: frame index is an index into 96-byte records.
  for typ,width in [('u8',1),('u16',2),('u32',4),('u64',8)]:
   v=s.replace('u8 *frames;',f'{typ} (*frames)[{96//width}];').replace('frame = (offset * 3 << 5) + arg0->frames;','frame = (u8 *)arg0->frames[offset];');add('source frame array '+typ,v)
 if addr=='801B446C':
  # A byte record makes the state explicitly addressable; no invented extra bytes.
  v=s.replace('extern u8 D_802C8CE0;','extern struct { u8 flags; } D_802C8CE0;').replace('&D_802C8CE0','&D_802C8CE0.flags')
  # prior matching definitions are isolated to this experiment.
  ctx=pre.replace('extern u8 D_802C8CE0;','extern struct { u8 flags; } D_802C8CE0;').replace('D_802C8CE0 |=','D_802C8CE0.flags |=')
  # avoid two different anonymous declarations.
  v=v.replace('extern struct { u8 flags; } D_802C8CE0;','')
  add('flag record',v,ctx)
  for stride in [11]:
   for typ in ['u8','s8']:
    v=s.replace('extern u8 D_802C8CF0[][11];',f'extern struct {{ {typ} values[11]; }} D_802C8CF0[];').replace('D_802C8CF0[arg0][choice]','D_802C8CF0[arg0].values[choice]');add('history records '+typ,v)
 if addr=='801C7CD0':
  for narrow in [True,False]:
   for replay in ['u8','s32','u32']:
    for masks in range(8):
     v=s.replace('u8 replay;',replay+' replay;')
     if not narrow:v=v.replace('u8 arg0','s32 arg0').replace('if (arg0 == 5)','if ((u8)arg0 == 5)').replace('arg0 != 4','(u8)arg0 != 4')
     # use addressable real global state while retaining scalar declarations.
     k=v.index('void '+fn);a=v[:k];b=v[k:];decl=[]
     for i,sym in enumerate(['D_802D3E15','D_802D3A06','D_802D3A00']):
      if masks>>i&1:
       ptr='state'+str(i);b=re.sub(r'\b'+sym+r'\b','(*'+ptr+')',b);decl.append('u8 *'+ptr+' = &'+sym+';')
     b=b.replace('    '+replay+' replay;','    '+replay+' replay;\n'+'\n'.join(decl));add('state '+str((narrow,replay,masks)),a+b)
 if addr=='801C35D8':
  for typ in ['u8','u16','u32','u64']:
   v=s.replace('extern u32 D_80290F90[];',f'extern {typ} D_80290F90[1];');add('display list '+typ,v)
  for a,b in itertools.product(['s8','s16','s32','u32'],repeat=2):
   add('params '+a+b,s.replace('s32 arg2, s32 arg3',a+' arg2, '+b+' arg3').replace('T030Cloud *, s32);','T030Cloud *, s8);'))
 if addr=='801C4E38':
  # Actual SDK prototype is OSBool = s32; global dispatcher is a table of function pointers.
  for typ in ['s32','u32','u8']:
   for ret in ['void','s32']:
    for cb in ['void','s32']:
     v=s.replace('osViBlack(u8)','osViBlack('+typ+')').replace('extern void func_8002F6F4', 'extern '+ret+' func_8002F6F4').replace('extern void (*D_800451EC','extern '+cb+' (*D_800451EC');add('SDK '+typ+ret+cb,v)
 if addr=='801B6528':
  for typ in ['u8','u32','u64']:
   v=s.replace('extern u8 D_801F2EB4[];',f'extern struct {{ u32 texture; {typ} rest[{136//({"u8":1,"u32":4,"u64":8}[typ])}]; }} D_801F2EB4[];').replace('*(u32 *)(D_801F2EB4 + D_80128340[((T029Card *)arg1)->index] * 140)','D_801F2EB4[D_80128340[((T029Card *)arg1)->index]].texture');add('texture record '+typ,v)
 if addr=='801C51F8':
  for typ in ['u8','u32','u64']:
   for length in [8,16,64]:add('matrix array '+typ+str(length),s.replace('extern u8 D_4AC40;',f'extern {typ} D_4AC40[{length}];'))
 seen=set()
 for label,ctx,v in vs:
  if ctx+v in seen:continue
  seen.add(ctx+v);r=probe.probe(fn,ctx+v)
  if r<best:best=r;(p.parent/(fn+'.t066-best')).write_text(v);print(fn,label,r,flush=True)
 res[fn]={'baseline':base,'best':best,'tested':len(seen)};print(fn,res[fn],flush=True)
(probe.ROOT/'tools/scratch/nonmatching/T-066/shapes-results.json').write_text(json.dumps(res,indent=2))
