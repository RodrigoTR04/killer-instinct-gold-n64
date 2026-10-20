import sys,re,itertools,json
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
out={}
for addr in ['801C7CD0','801B446C','801B695C','801BF720','801BF914']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 def add(label,v):vs.append((label,v))
 if addr=='801C7CD0':
  for typ in ['u8','u32','s32']:
   for mode in range(4):
    for replay in range(3):
     v=s.replace('u8 replay;',typ+' replay;')
     if mode==0:v=v.replace('D_802D3A00 = arg0;\n    if (arg0 == 5)', 'if ((D_802D3A00 = arg0) == 5)')
     if mode==1:v=v.replace('if (arg0 == 5)','if (D_802D3A00 == 5)').replace('arg0 != 4','D_802D3A00 != 4')
     if mode==2:v=v.replace('if (arg0 == 5)','switch (D_802D3A00 = arg0) { case 5:').replace('} else if (arg0 != 4 && D_802D3A06 == 0) {','break; default: if (arg0 != 4 && D_802D3A06 == 0) {').replace('    D_802D3A01 = 0;','    }\n    D_802D3A01 = 0;')
     if mode==3:v=v.replace('D_802D3A00 = arg0;','arg0 = D_802D3A00 = arg0;')
     if replay==1:v=v.replace('if (D_802D3E15 == 0) D_802D3E15 = 1;\n        replay = D_802D3E15;','replay = D_802D3E15;\n        if (replay == 0) replay = D_802D3E15 = 1;')
     if replay==2:v=v.replace('if (D_802D3E15 == 0) D_802D3E15 = 1;\n        replay = D_802D3E15;','if ((replay = D_802D3E15) == 0) replay = D_802D3E15 = 1;')
     add(str((typ,mode,replay)),v)
 if addr=='801B446C':
  for typ in ['u8','u32','s32']:
   for style in range(3):
    v=s.replace('s32 flags;',typ+' flags;')
    if style==0:v=v.replace('flags = *flagsp;','').replace('if (!(flags & bit))','if (!((flags = *flagsp) & bit))')
    if style==1:v=v.replace('flags = *flagsp;','').replace('if (!(flags & bit))','if (!((flags = D_802C8CE0) & bit))')
    if style==2:v=v.replace('*flagsp = flags | bit;','*flagsp |= bit;')
    add(typ+str(style),v)
 if addr=='801B695C':
  # Pointer-to-frame rather than pointer-to-byte local can change IDO stack allocation.
  for typ in ['u8','u16','u32','u64']:
   width={'u8':1,'u16':2,'u32':4,'u64':8}[typ]
   v=s.replace('u8 *frame;',f'{typ} (*frame)[{96//width}];').replace('frame = (offset * 3 << 5) + arg0->frames;',f'frame = ({typ} (*)[{96//width}])((offset * 3 << 5) + arg0->frames);');add('frame pointer '+typ,v)
 if addr in ['801BF720','801BF914']:
  # An enum's full domain and bitfield signedness are type information too.
  for typ in ['unsigned int','signed int']:
   for width in [6,8,16,32]:
    v=s.replace('s32 result;',f'struct {{ {typ} value:{width}; }} result;');k=v.index('    if (');v=v[:k]+re.sub(r'\bresult\b','result.value',v[k:]);add('bitfield '+typ+str(width),v)
 for label,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;(p.parent/(fn+'.t066-best')).write_text(v);print(fn,label,r,flush=True)
 out[fn]={'best':best,'tested':len(vs)};print(fn,out[fn],flush=True)
(probe.ROOT/'tools/scratch/nonmatching/T-066/expressions-results.json').write_text(json.dumps(out,indent=2))
