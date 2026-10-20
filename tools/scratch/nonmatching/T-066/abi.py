import sys,re,json,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
res={}
for addr in ['801C4E38','801B6528','801C35D8','801BF720','801BF914','801C51F8','801B695C','801B6A68','801B446C','801C7CD0']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 def add(label,v,ctx=pre):vs.append((label,ctx,v))
 m=re.search(r'\b(void|s32) '+fn+r'\(([^)]*)\)\s*{',s)
 params=m[2].split(',');defs=[];args=[]
 for param in params:
  x=re.match(r'(.*?)(\w+)\s*$',param.strip());defs.append(param.strip()+';');args.append(x[2])
 v=s[:m.start()]+m[1]+' '+fn+'('+', '.join(args)+')\n'+'\n'.join(defs)+'\n{'+s[m.end():]
 add('K&R',v)
 # Callee unspecified prototypes preserve ABI but may change IDO call classification.
 for ext in re.finditer(r'extern ([^;\n]+?) (\w+)\(([^;{}]*)\);',s):
  if not ext[3] or ext[3]=='void':continue
  add('unprototyped '+ext[2],s[:ext.start()]+f'extern {ext[1]} {ext[2]}();'+s[ext.end():])
 if addr=='801B695C':
  # All live values as a genuine copy context, or overlapping union for index-to-byte-offset lifetime.
  for order in itertools.permutations(['offset','bank','frame']):
   v=s.replace('s32 offset;','').replace('u8 *bank;','').replace('u8 *frame;','')
   fields={'offset':'s32 offset;','bank':'u8 *bank;','frame':'u8 *frame;'}
   v=v.replace('{\n    ', '{\n    struct { '+' '.join(fields[x] for x in order)+' } copy;\n    ',1)
   k=v.index('if (arg0')
   v=v[:k]+re.sub(r'\b(offset|bank|frame)\b',r'copy.\1',v[k:]);add('copy context '+str(order),v)
  # Destination is naturally a 16-bit palette, not raw bytes.
  for width,typ in [(2,'u16'),(4,'u32'),(8,'u64')]:
   v=s.replace('extern u8 D_802C8808[];',f'extern {typ} D_802C8808[];')
   v=v.replace('D_802C8808 + *bank * 2 + offset + 0x100',f'D_802C8808 + (*bank * 2 + offset + 0x100) / {width}').replace('D_802C8808 + *bank * 2 + offset,',f'D_802C8808 + (*bank * 2 + offset) / {width},');add('palette '+typ,v)
 if addr=='801B6528':
  # Matrix type aligns to eight bytes in the real SDK; pointer qualifiers describe ownership.
  for qualifier in ['const','volatile','const volatile']:
   add('card '+qualifier,s.replace('void *arg1',qualifier+' void *arg1').replace('(T029Card *)arg1','('+qualifier+' T029Card *)arg1'))
  for typ in ['u32','s32','u64','f64']:
   add('matrix '+typ,s.replace('void *arg2',typ+' *arg2'))
 if addr=='801C7CD0':
  for mask in range(1,8):
   syms=['D_802D3E15','D_802D3A06','D_802D3A00'];v=s
   pairs=[(sym,'state'+str(i)) for i,sym in enumerate(syms) if mask>>i&1]
   k=v.index('void '+fn);prefix=v[:k];body=v[k:]
   decl='\n'.join('u8 *'+ptr+' = &'+sym+';' for sym,ptr in pairs)
   body=body.replace('    u8 replay;','    u8 replay;\n'+decl)
   for sym,ptr in pairs:
    j=body.index('    if (');body=body[:j]+re.sub(r'\b'+sym+r'\b','(*'+ptr+')',body[j:])
   add('state pointers '+str(mask),prefix+body)
 if addr=='801B6A68':
  for stride in [1,2,4,8,16]:
   v=s.replace('extern u8 D_802C8808[];',f'extern u8 D_802C8808[][512];').replace('D_802C8808 + (arg2 << 9) + D_802C8D08[arg2] * 2','&D_802C8808[arg2][D_802C8D08[arg2] * 2]');add('palette rows',v)
 for label,ctx,v in vs:
  r=probe.probe(fn,ctx+v)
  if r<best:best=r;(p.parent/(fn+'.t066-best')).write_text(v);print(fn,label,r,flush=True)
 res[fn]={'best':best,'tested':len(vs)};print(fn,res[fn],flush=True)
(probe.ROOT/'tools/scratch/nonmatching/T-066/abi-results.json').write_text(json.dumps(res,indent=2))
