from probe import *
RESULTS=[]
def body(s,fn):
 m=re.search(r'\b(?:void|u32|s32|f32)\s+'+fn+r'\([^;{}]*\)\s*\{',s); start=m.start(); pos=m.end(); depth=1
 while depth:
  depth += (s[pos]=='{')-(s[pos]=='}'); pos+=1
 return start,pos
def run(fn,variants):
 original=(WORK/(fn+'.c')).read_text()
 baseline=compile(fn,original,'baseline')
 best=baseline
 existing=WORK/(fn+'-best.c')
 if existing.exists():
  previous=compile(fn,existing.read_text(),'previous')
  if previous.get('words',10**9)<best['words']:best=previous
 for label,transform in variants:
  try: s=transform(original)
  except Exception as e: print('transform error',label,e);continue
  r=compile(fn,s,label);r['function']=fn;RESULTS.append(r)
  if 'words' in r and r['bytes'] and r['words']<best['words']:
   best=r;(WORK/(fn+'-best.c')).write_text(s)
   print(fn,r,flush=True)
 (WORK/(Path(sys.argv[0]).stem+'-results.json')).write_text(json.dumps(RESULTS,indent=2))
 return best
if __name__=='__main__':
 fn='func_801C6D40'
 variants=[]
 for literal in [False,True]:
  for arg in [False,True]:
   for phase in [False,True]:
    for reuse in [False,True]:
     def t(s,literal=literal,arg=arg,phase=phase,reuse=reuse):
      if literal:s=s.replace('var_f6 * D_802948B8','var_f6 * 0.6')
      if arg:s=s.replace('&D_8004A258, var_a3','&D_8004A258').replace('func_801C4BD0(0x85, var_a3)','func_801C4BD0(0x85)')
      if phase:
       s=s.replace('s32 var_v1;', 'u8 var_v1;').replace('var_v1 = 1 & 0xFF;', 'var_v1 = D_802D399C = 1;').replace('D_802D399C = 1;\n', '')
      if reuse:
       a,b=body(s,fn);s=s[:a]+s[a:b].replace('var_a3 = arg1;', '').replace('var_a3','arg1')+s[b:]
      return s
     variants.append((f'literal{literal}-arity{arg}-phase{phase}-reuse{reuse}',t))
 run(fn,variants)
 fn='func_8001373C'
 variants=[]
 for kind in ['distance','arg1','arg2','arg3']:
  for layout in [False,True]:
   def t(s,kind=kind,layout=layout):
    a,b=body(s,fn);code=s[a:b];code=code.replace('dx = dx * dx + dy * dy + dz * dz;',kind+' = dx * dx + dy * dy + dz * dz;').replace('if (dx < D_800487F4) dx = D_800487F8;',f'if ({kind} < 50000.0f) {kind} = 50000.0f;').replace('/ dx','/ '+kind)
    if kind=='distance':code=code.replace('f32 dx;', 'f32 distance; f32 dx;')
    if layout:code=code.replace(';',';\n').replace('{','{\n').replace('}', '\n}')
    return s[:a]+code+s[b:]
   variants.append((kind+str(layout),t))
 run(fn,variants)
 fn='func_8002F5F0';variants=[]
 for ptr in [False,True]:
  for branch in [False,True]:
   for layout in [False,True]:
    def t(s,ptr=ptr,branch=branch,layout=layout):
     a,b=body(s,fn);code=s[a:b]
     if ptr:code=code.replace('T024ReleasedVoice *p =', 'T024ReleaseLists *lists = &D_80048270; T024ReleasedVoice *p =').replace('D_80048270.', 'lists->')
     if branch:
      obj='lists->' if ptr else 'D_80048270.'
      code=code.replace('->prev = p;', '->prev = p; '+obj+'free = p;').replace('p->next = 0;', 'p->next = 0; '+obj+'free = p;').replace('}\n    '+obj+'free = p;', '}')
     if layout:code=code.replace(';',';\n').replace('{','{\n').replace('}', '\n}')
     return s[:a]+code+s[b:]
    variants.append((f'ptr{ptr}-branch{branch}-layout{layout}',t))
 run(fn,variants)
