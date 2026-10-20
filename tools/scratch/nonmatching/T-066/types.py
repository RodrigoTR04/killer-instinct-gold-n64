import sys,re,json,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
names=['801C4E38','801B6528','801C35D8','801BF720','801BF914','801C51F8','801B695C','801B6A68','801B446C','801C7CD0']
results={}
for addr in names:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);base=probe.probe(fn,pre+s);best=base;vs=[]
 def add(label,v,context=pre):vs.append((label,context,v))
 # Width-preserving aggregate locals: models real conceptual records without padding.
 for local in re.findall(r'\b(?:s32|u32|u8|s16|s32|u8 \*|u8\*)\s+(\w+)\s*;',s):
  if local.startswith('D_'):continue
  m=re.search(r'\b(s32|u32|u8|s16)\s+'+local+r'\s*;',s)
  if not m:continue
  for kind in ['struct','union']:
   v=s[:m.start()]+kind+' { '+m[1]+' value; } '+local+';'+s[m.end():]
   start=v.find('void '+fn) if 'void '+fn in v else v.find('s32 '+fn)
   head=v[:start];body=v[start:];enddecl=body.find('} '+local+';')+len('} '+local+';')
   body=body[:enddecl]+re.sub(r'\b'+local+r'\b',local+'.value',body[enddecl:])
   add('aggregate '+local+' '+kind,head+body)
 # Replace command layout with a union with independently typed halves (no layout change).
 for word in ['s32','u32','unsigned long','signed long']:
  add('command '+word,s.replace('u32 w0, w1;',word+' w0, w1;').replace('u32 w0,w1;',word+' w0,w1;'))
 # Narrow callee argument as demonstrated by callee entry sign extension.
 if addr=='801C35D8':
  add('callee s8',s.replace('T030Cloud *, s32);','T030Cloud *, s8);'))
  for field in ['x','y','z','angle','width']:
   v=s.replace('s16 x, y, z, angle, width;','; '.join(('u16' if f==field else 's16')+' '+f for f in ['x','y','z','angle','width'])+';')
   add('field '+field,v)
 if addr=='801B695C':
  for loc in ['offset','frame','bank']:
   if loc=='offset':
    v=s.replace('s32 offset;','').replace('offset','arg1') # parameter reuse only when initial index preserved separately
    v=v.replace('u8 *bank;','u8 *bank;\n s32 player = arg1;').replace('D_802C8D08[arg1]','D_802C8D08[player]').replace('arg1 = arg1 << 9','arg1 = player << 9')
    add('reuse offset parameter',v)
  for t in ['void','s32','u32','u64','void *']:
   add('memcpy return '+t,s.replace('void *memcpy',t+' memcpy'))
  for t in ['u16','s16','s8','u8','u32']:
   add('index '+t,s.replace('s32 arg1',t+' arg1'))
 if addr=='801C4E38':
  for t in ['s32','u32','u64','s64']:
   for func in ['func_8002F9FC','func_8002A8C4','func_801C4D28','func_801C4D6C','func_80016078']:
    add('return '+func+t,s.replace('void '+func+'(',t+' '+func+'('))
  for t in ['s32','u32','u64','s64']:
   add('callback '+t,s.replace('void (*D_800451EC',t+' (*D_800451EC'))
 if addr in ['801BF720','801BF914']:
  for t in ['s8','u8','s16','u16','s32','u32','s64','u64']:
   # Addressable real scalar wrapped in a local array or struct.
   for shape in ['array','struct']:
    v=s.replace('s32 result;',t+' result[1];' if shape=='array' else 'struct { '+t+' value; } result;')
    decl=v.index(' result')
    tail=v.index(';',decl)+1
    v=v[:tail]+re.sub(r'\bresult\b','result[0]' if shape=='array' else 'result.value',v[tail:])
    add(t+shape,v)
 if addr=='801C51F8':
  for typ in ['u64','f64','u32','s32','u16','s16']:
   add('address object '+typ,s.replace('extern u8 D_4AC40;', 'extern '+typ+' D_4AC40;'))
 if addr=='801B6528':
  for typ in ['s32','u32','s16','u16','s8','u8']:
   # field located at offset 12, narrow values require explicit padding and are diagnostic only.
   add('card index '+typ,s.replace('s32 index; } T029Card',typ+' index; } T029Card'))
  for typ in ['u64','s64','f64']:
   add('arg3 '+typ,s.replace('s32 arg3',typ+' arg3'))
 if addr=='801B446C':
  for typ in ['u8','s8','u16','s16','u32','s32']:
   add('cached flags '+typ,s.replace('s32 flags;',typ+' flags;'))
  add('flag array',s.replace('extern u8 D_802C8CE0;','extern u8 D_802C8CE0[1];').replace('&D_802C8CE0','D_802C8CE0'))
 if addr=='801C7CD0':
  for typ in ['s32','u32','s16','u16','s8','u8']:
   add('replay '+typ,s.replace('u8 replay;',typ+' replay;'))
  for sym in ['D_802D3E15','D_802D3A06','D_802D3A00']:
   for shape in ['array','record']:
    # split combined declaration before replacing uses.
    v=s.replace('extern u8 D_802D3A00, D_802D3A06, D_802D3E15;','extern u8 D_802D3A00; extern u8 D_802D3A06; extern u8 D_802D3E15;')
    pat='extern u8 '+sym+';';replacement=('extern u8 '+sym+'[1];') if shape=='array' else ('extern struct { u8 value; } '+sym+';')
    v=v.replace(pat,replacement);k=v.index('void '+fn);v=v[:k]+re.sub(r'\b'+sym+r'\b',sym+('[0]' if shape=='array' else '.value'),v[k:]);add(sym+shape,v)
 if addr=='801B6A68':
  for typ in ['s8','u8','s16','u16','u32']:
   add('texture index '+typ,s.replace('s32 arg2',typ+' arg2'))
 seen=set(); tested=0; wins=[]
 for label,context,v in vs:
  if context+v in seen:continue
  seen.add(context+v);r=probe.probe(fn,context+v);tested+=1
  if r<best:
   best=r;wins.append((label,r));(p.parent/(fn+'.t066-best')).write_text(v);print(fn,label,r,flush=True)
 results[fn]={'baseline':base,'best':best,'tested':tested,'wins':wins}
 print(fn,results[fn],flush=True)
path=probe.ROOT/'tools/scratch/nonmatching/T-066/results.json';path.write_text(json.dumps(results,indent=2))
