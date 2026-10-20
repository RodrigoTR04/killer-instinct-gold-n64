from context import *
from itertools import product

def variants2(fn,s):
 a,b,brace=extent(s,fn); body=s[a:b]
 if fn.endswith(('AA98','AAEC')):
  for typ,expr in product(['s32','u32','s64','u64'], ['D_80048140[D_80127CC9] * volume','volume * D_80048140[D_80127CC9]']):
   yield 'product-'+typ+'-'+str(expr.startswith('volume')),s.replace('s32 scaled = D_80048140[D_80127CC9] * volume;',typ+' scaled = '+expr+';')
  for typ in ['s32','u32','s16','u16','void *']:
   yield 'extra-param-'+typ,s[:a]+s[a:].replace('(s32 volume)','(s32 volume, '+typ+' unused)',1)
  for ret in ['s32','s16','u16','void','void *']:
   t=re.sub(r'extern void alCSPSetVol\(void \*,s32\);','extern '+ret+' alCSPSetVol(void *,s16);',s)
   yield 'sdk-return-'+ret,t
  yield 'sdk-implicit',re.sub(r'extern void alCSPSetVol\(void \*,s32\);','',s)
  # Product as unused incoming argument, no binding keywords.
  for name in ['product','volume']:
   t=s.replace('(s32 volume)','(s32 volume, s32 unused, s32 product)')
   t=t.replace('s32 scaled =','product =').replace('scaled','product')
   yield 'product-argument-'+name,t
 if fn.endswith('B695C'):
  for typ in ['s32','u32','s16','u8','f32','f64','void *','s64']:
   yield 'unused-third-'+typ,s.replace('T029Asset *arg0, s32 arg1)', 'T029Asset *arg0, s32 arg1, '+typ+' unused)')
  for ret,args in product(['void','s32','void *','u64'],['void *, const void *, u32','void *, const void *, s16','void *, const void *, s32','']):
   yield 'copy-'+ret+'-'+args,s.replace('void *memcpy(void *, const void *, u32)',ret+'memcpy('+args+')' if ret.endswith('*') else ret+' memcpy('+args+')')
  yield 'copy-implicit',s.replace('extern void *memcpy(void *, const void *, u32);','')
  yield 'copy-pointer',s.replace('extern void *memcpy(void *, const void *, u32);','extern void *memcpy(void *, const void *, u32);\n#define COPY memcpy').replace('memcpy((u8 *)','COPY((u8 *)')
  for qual in ['const','volatile']:
   yield 'asset-'+qual,s.replace('u8 *frames;', 'u8 *'+qual+' frames;')
 if fn.endswith(('BF720','BF914')):
  for ret,typ in product(['s32','u32','s16','u16','s8','u8'],['s32','u32','s16','u16']):
   t=s[:a]+s[a:].replace('s32 '+fn,' '+ret+' '+fn,1).replace('s32 result;',typ+' result;',1)
   # Adapt only own forward declaration if present.
   t=t.replace('extern s32 '+fn+'(u32);','extern '+ret+' '+fn+'(u32);')
   yield 'result-'+ret+'-'+typ,t
  for mode in ['goto','assign','switch-default']:
   t=body
   if mode=='goto':
    t=re.sub(r"case ([^:]+): return ([^;]+);",r'case \1: result = \2; goto finish;',t)
    t=t.replace('return result;','finish: return result;')
   if mode=='assign': t=re.sub(r'case ([^:]+): return ([^;]+);',r'case \1: result = \2; break;',t)
   if mode=='switch-default':
    t=t.replace("result = ' ';",'').replace('result = 27;','')
    t=t.replace('switch (code) {','switch (code) {\n default: result = '+("' '" if fn.endswith('720') else '27')+'; break;')
   yield mode,s[:a]+t+s[b:]
 if fn.endswith('C7998'):
  # Force unsigned widening before the 64-bit switch; retained flags remain 16-bit.
  for expr in ['(u64)(u32)buttons','(u64)(u16)buttons','(u64)(buttons & 0xFFFFU)','(u64)(buttons & 0xFFFFUL)','(u64)(u32)(buttons & 0xFFFF)','(u64)(buttons | 0U)','(u64)(buttons + 0U)']:
   yield 'widen-'+expr,s.replace('(u64)(buttons & 0xFFFF)',expr)
  for typ in ['u16','u32','s32','u64']:
   yield 'mask-'+typ,s.replace('u8 index = 0;',typ+' mask = buttons;\n u8 index = 0;').replace('(u64)(buttons & 0xFFFF)','(u64)(mask & 0xFFFFU)')
 if fn.endswith('C5064'):
  for style in ['zero-local','zero-before-depth','zero-before-scale','depth-const','depth-volatile','reverse-declarations']:
   t=s
   if style.startswith('zero-'):
    t=t[:a]+t[a:].replace('f32 depth;','f32 depth;\n f32 zero;',1)
    loc={'zero-local':'depth = D_80294890;','zero-before-depth':'depth = D_80294890;','zero-before-scale':'scale = D_8029488C;'}[style]
    t=t.replace(loc,('zero = 0.0f; '+loc) if style!='zero-local' else (loc+' zero = 0.0f;'))
    t=t.replace('), 0.0f,', '), zero,')
   elif style=='depth-const': t=t.replace('depth = D_80294890;', 'depth = -1950.0f;')
   elif style=='depth-volatile': t=t.replace('extern f32 D_8029488C, D_80294890;','extern f32 D_8029488C; extern volatile f32 D_80294890;')
   else: t=t.replace('f32 scale;\n    f32 origin;\n    f32 depth;', 'f32 depth;\n f32 origin;\n f32 scale;')
   yield style,t
 if fn.endswith('C6A80'):
  for typ in ['u8','s8','u16','u32']:
   for form in ['assign','increment','conditional']:
    t=s.replace('D_802D3984 += 1;',{'assign':'D_802D3984 = 1;','increment':'++D_802D3984;','conditional':'D_802D3984 = D_802D3984 ? D_802D3984 : 1;'}[form])
    t=t.replace('extern u8 D_802D3984;', 'extern '+typ+' D_802D3984;')
    yield 'flag-'+typ+'-'+form,t
  # A constant typed scalar in own TU uses different symbol handling than extern.
  yield 'flag-defined',s.replace('extern u8 D_802D3984;', 'u8 D_802D3984;')
 if fn.endswith('C4E38'):
  for typ in ['s32','u32','s16','u16','u8','s8','s64','u64']:
   t=s.replace('switch (arg0)', 'switch (selector)')
   t=t.replace('void func_801C4E38(u8 arg0, u8 arg1) {','void func_801C4E38(u8 arg0, u8 arg1) {\n '+typ+' selector = arg0;')
   yield 'selector-'+typ,t
  for typ in ['s32','u32','void *','u64']:
   yield 'unused-third-'+typ,s.replace('u8 arg0, u8 arg1)', 'u8 arg0, u8 arg1, '+typ+' unused)')

def main():
 rows={}
 for n in FUNCTIONS[:8]+FUNCTIONS[15:18]:
  fn='func_'+n; s=(WORK/(fn+'.c')).read_text(); baseline=compile(fn,s); rows[fn]=[baseline]
  jobs=list(variants2(fn,s))
  def run(job):
   name,src=job; r=compile(fn,src,name)
   if r.get('words',999)<baseline.get('words',999): (WORK/(fn+'-focused-'+re.sub(r'[^\w-]','_',name)+'.c')).write_text(src)
   return r
  with ThreadPoolExecutor(max_workers=4) as pool:
   for r in pool.map(run,jobs):
    rows[fn].append(r); print(fn,r,flush=True)
 (WORK/'focused.json').write_text(json.dumps(rows,indent=2))
if __name__=='__main__': main()
