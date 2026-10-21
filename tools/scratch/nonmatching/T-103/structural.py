exec(open('tools/scratch/nonmatching/T-103/sweep.py').read().split('out=[]; best=19')[0])
import random
out=[];best=19
variants=[]
# Reuse dead incoming scalars for palette/packed results and completion count.
for old in ['alpha','(u8)alpha','(alpha & 255)']:
 for palette in ['color2','arg1','arg3','packed','value']:
  for flag in ['D_801D308C += 1','++D_801D308C','D_801D308C++','D_801D308C = D_801D308C + 1']:
   for early in ['packed','arg1','arg3','color2']:
    t=base.replace('color2 = D_802C87D0','PALETTE = D_802C87D0').replace('(color2 <<','(PALETTE <<').replace('packed = (','EARLY = (').replace('(s32) packed','(s32) EARLY').replace('PALETTE',palette).replace('EARLY',early).replace('| alpha);','| '+old+');').replace('D_801D308C += 1',flag)
    variants.append((f'reuse-{old}-{palette}-{flag}-{early}',t))
# Move command constant stores around the allocation, packing, alpha and flag work.
for earlypos in range(6):
 for latepos in range(7):
  for flagpos in range(4):
   t=base
   e=['value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);','color = (u16)value;','packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);','alpha = color;','p0 = (*arg0)++;','p0->w1 = (s32) packed;']
   e.insert(max(5,earlypos),'p0->w0 = 0xFA000000;')
   l=['*counter = arg1;','p1 = (*arg0)++;','color2 = D_802C87D0 & 0xFF;','p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | alpha);','alpha = 0xFF;']
   l.insert(max(2,latepos),'p1->w0 = 0xFA000000;')
   # Delay explicit completion pointer initialization until the late path.
   if flagpos:
    l.insert(min(len(l),flagpos+1),'flag = &D_801D308C;')
    t=t.replace('    u8 alpha;','    u8 alpha;\n    u8 *flag;').replace('(s32) D_801D308C','(s32) *flag').replace('D_801D308C += 1','*flag += 1')
   start=t.index('        value =');end=t.index('    guTranslate')
   tail=t[t.index('        if ((s32)',start):end]
   t=t[:start]+'\n'.join('        '+x for x in e)+'\n    }\n    else\n    {\n'+'\n'.join('        '+x for x in l)+'\n'+tail+t[end:]
   variants.append((f'order-{earlypos}-{latepos}-{flagpos}',t))
# Random line grouping with no token changes, reproducible seed.
rng=random.Random(103)
for n in range(1500):
 lines=base.splitlines(); grouped=[]
 for line in lines:
  if grouped and rng.random()<0.45 and not line.lstrip().startswith('/*') and not grouped[-1].rstrip().endswith('*/'):grouped[-1]+=' '+line.strip()
  else:grouped.append(line)
 variants.append((f'layout-{n}','\n'.join(grouped)))
seen=set()
for label,t in variants:
 if t in seen:continue
 seen.add(t);r=compile('func_801B2EF4',s[:a]+t+s[b:],label);out.append(r)
 if r.get('words',999)<best:
  best=r['words'];Path('/tmp/kig-t103-struct-best.c').write_text(s[:a]+t+s[b:]);Path('/tmp/kig-t103-struct-body.c').write_text(t);print(label,best,flush=True)
 if len(out)%100==0:print('completed',len(out),'best',best,flush=True)
Path('tools/scratch/nonmatching/T-103/structural.json').write_text(json.dumps(out,indent=2)+'\n');print('done',len(out),best,flush=True)
