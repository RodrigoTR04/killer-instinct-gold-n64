from pathlib import Path
import sys,json,re,itertools
from concurrent.futures import ThreadPoolExecutor
sys.path.insert(0,str(Path(__file__).resolve().parents[1]/'T-096'))
from context import extent
from probe import source,compile,FUNCTIONS,ROOT
OUT=Path('/tmp/kig-t097'); OUT.mkdir(exist_ok=True)
def variants(fn,s):
 a,b,br=extent(s,fn); body=s[a:b]
 def emit(label,t): return label,s[:a]+t+s[b:]
 if fn.endswith('F6F4'):
  decls=['T024ChainVoice *voice;','T024ChainSound *sound;','s32 step;','T024ChainVoice *last = 0;','s16 repeat = 0;','s32 repeatTime;','T024ChainKey *key;','s32 delay = 0;','T024ChainEvent start;','T024ChainEvent event;']
  for d in decls:
   for anchor in decls:
    if d!=anchor: yield emit('move-'+str(decls.index(d))+'-before-'+str(decls.index(anchor)),body.replace('  '+d+'\n','').replace('  '+anchor,'  '+d+'\n  '+anchor))
  for typ in ['s16','u32','long','f32']:
   if typ!='f32': yield emit('step-'+typ,body.replace('s32 step;',typ+' step;'))
  yield emit('repeat-arg',body.replace('s16 repeat = 0;','s16 repeat = 0;').replace('repeatTime = step + 1;','repeatTime = step;').replace('&event, repeatTime);','&event, repeatTime + 1);'))
 if fn.endswith('B695C'):
  for name,expr in [('frame','(offset * 3 << 5) + arg0->frames'),('bank','&D_802C8D08[arg1]')]:
   t=body
   if name=='frame':
    t=t.replace('    u8 *frame;','').replace('        frame = '+expr+';','')
    t=re.sub(r'\bframe\b','('+expr+')',t)
   else:
    t=t.replace('    u8 *bank;','').replace('        bank = '+expr+';','').replace('*bank','D_802C8D08[arg1]')
   yield emit('inline-'+name,t)
  for typ in ['u32','u16','s16','u8']:
   yield emit('offset-'+typ,body.replace('s32 offset;',typ+' offset;'))
  yield emit('reuse-arg1',body.replace('offset = arg1 << 9;','arg1 <<= 9;').replace('*bank * 2 + offset','*bank * 2 + arg1'))
 if fn.endswith('C7998'):
  for typ in ['u32','s32','s16','s8','u8','u64']:
   yield emit('parameter-'+typ,body.replace('u16 buttons',typ+' buttons'))
  for typ in ['u64','s64']:
   yield emit('wide-local-'+typ,body.replace('u8 index = 0;',typ+' value = buttons;\n    u8 index = 0;').replace('(u64)(buttons & 0xFFFF)','value & 0xFFFF'))
  yield emit('assign-param',body.replace('switch ((u64)(buttons & 0xFFFF))','buttons &= 0xFFFF;\n    switch ((u64)buttons)'))
 if fn.endswith('C6A80'):
  for expr in ['D_802D3984++','D_802D3984 = (u8)(D_802D3984 + 1)','D_802D3984 = temp_v0 + 1','D_802D3984 = temp_t9 + 1']:
   t=body.replace('D_802D3984 += 1',expr)
   if 'temp_v0 + 1' in expr:t=t.replace('if (D_802D3984 == 0)','if ((temp_v0 = D_802D3984) == 0)')
   if 'temp_t9 + 1' in expr:t=t.replace('if (D_802D3984 == 0)','if ((temp_t9 = D_802D3984) == 0)')
   yield emit('flag-'+expr,t)
  yield emit('cached-flag',body.replace('u8 temp_t9;','u8 temp_t9;\n    u8 *flag = &D_802D3984;').replace('if (D_802D3984 == 0)','if (*flag == 0)').replace('D_802D3984 += 1;','*flag += 1;'))
  yield emit('store-order',body.replace('D_802D399D = 0xFF;\n            if (D_802D3984 == 0)', 'temp_t9 = D_802D3984;\n            D_802D399D = 0xFF;\n            if (temp_t9 == 0)'))
 if fn.endswith(('BF720','BF914')):
  for var in ['code','result']:
   t=body
   t=re.sub(r'case ([^:]+): return ([^;]+);',lambda m:'case '+m[1]+': '+var+' = '+m[2]+'; break;',t)
   if var=='code':t=t.replace("result = ' ';","code = ' ';") if False else t
   yield emit('break-'+var,t)
  yield emit('return-assignment',body.replace('return result;','return code = result;'))
  yield emit('result-volatile',body.replace('s32 result;','volatile s32 result;'))
 if fn.endswith('C4E38'):
  for typ in ['u8','u16','s32','u32']:
   for point in ['osViBlack(1);','switch (arg0) {']:
    t=body.replace('{','{\n '+typ+' selector;',1).replace(point,'selector = arg0;\n '+point).replace('switch (arg0)','switch (selector)').replace('if (arg0 == 5)','if (selector == 5)')
    yield emit('selector-'+typ+'-'+point,t)
 if fn.endswith('B6528'):
  for dest in ['arg2','arg3']:
   t=body.replace('guTranslate(arg2, 0.0f, y, 0.0f);','guTranslate(arg2, 0.0f, y, 0.0f);\n '+dest+' = '+('(s32)' if dest=='arg3' else '')+'arg1;')
   pos=t.index('command = *arg0;');t=t[:pos]+t[pos:].replace('(T029Card *)arg1','(T029Card *)'+dest)
   yield emit('reuse-'+dest,t)
 if fn.endswith('B2010'):
  start=body.index('    arg1 = D_801D309C;');end=body.index('    guTranslate',start)
  for var in ['arg1','arg3','count']:
   for pred in ['< 1','<= 0']:
    t=body[:start]+f'''    {var} = D_801D309C;
    if ({var}++ {pred}) {{
        D_801D309C = {var};
        position = func_801B19F0(-6.0f, -150.0f, {var}, 1);
    }} else {{
        D_801D309C = {var};
        position = -150.0f;
    }}
'''+body[end:]
    if var=='count':t=t.replace('s32 alpha;','s32 alpha;\n s32 count;')
    yield emit('postfix-'+var+pred,t)
 if fn.endswith('17378'):
  # Preserve tokens while testing scheduling-sensitive statement layout.
  yield emit('joined-lines',re.sub(r';\s*\n\s*','; ',body))
 # Token-preserving declaration/statement layout can alter IDO allocation.
 yield emit('compact-layout',re.sub(r'\n\s*',' ',body))
def main():
 results={}
 for n in [x for x in FUNCTIONS if x not in ['801C5064','8002AA98','8002AAEC']]:
  fn='func_'+n;s=source(fn);base=compile(fn,s,'baseline',True);print(fn,base,flush=True)
  rows=[base];jobs=list(variants(fn,s))
  def run(job):
   name,t=job;r=compile(fn,t,name,True)
   if 0<r.get('bytes',0) and r.get('words',999)<base.get('words',999):
    p=OUT/(fn+'-'+re.sub(r'[^\w-]','_',name)+'.c');p.write_text(t);r['candidate']=str(p)
   return r
  with ThreadPoolExecutor(max_workers=4) as pool:
   for r in pool.map(run,jobs):
    rows.append(r)
    if r.get('words',999)<base.get('words',999):print('BETTER',fn,r,flush=True)
  results[fn]=rows
  (OUT/'results.json').write_text(json.dumps(results,indent=2))
if __name__=='__main__':main()
