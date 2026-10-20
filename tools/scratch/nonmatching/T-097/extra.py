import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-097')
from sweep import *
# Focused lifetimes and loop addressing, beyond the first sweep.
rows={}
for fn in ['func_801B695C','func_80017378','func_801C7998','func_801C4E38']:
 s=source(fn); a,b,br=extent(s,fn);body=s[a:b];jobs=[]
 if fn.endswith('B695C'):
  for name in ['offset','frame','bank']:
   pattern={'offset':'s32 offset;','frame':'u8 *frame;','bank':'u8 *bank;'}[name]
   t=body.replace(pattern,'').replace('if (arg0 != 0 && arg0->frames != 0) {','if (arg0 != 0 && arg0->frames != 0) {\n '+pattern)
   jobs.append(('scope-'+name,t))
  jobs.append(('index-local',body.replace('s32 offset;','s32 offset;\n s32 index = arg1;').replace('D_802C8CC8[arg1]','D_802C8CC8[index]').replace('D_802C8D08[arg1]','D_802C8D08[index]').replace('arg1 << 9','index << 9')))
  for var in ['bank','frame','offset']:
   decl={'bank':'u8 *bank;','frame':'u8 *frame;','offset':'s32 offset;'}[var]
   for anchor in ['s32 offset;','u8 *bank;','u8 *frame;']:
    if decl!=anchor:jobs.append(('decl-'+var+'-'+anchor,body.replace(decl,'').replace(anchor,decl+'\n'+anchor)))
 if fn.endswith('17378'):
  start=body.index('    model = (void **)&D_8004A998;');end=body.index('    func_8001C0E4',start)
  old=body[start:end]
  for order in [0,1]:
   for joined in [0,1]:
    t=old.replace('        rot += 1;\n','').replace('        model += 4;','        rot += 1;\n        model += 4;').replace('rot[0].','rot[-1].')
    if order:t=t.replace('    model = (void **)&D_8004A998;\n    rot = (T0331383CStageRotation *)&D_8004A9D8;','    rot = (T0331383CStageRotation *)&D_8004A9D8;\n    model = (void **)&D_8004A998;')
    if joined:t=re.sub(r';\s*\n\s*','; ',t)
    jobs.append((f'preincrement-{order}-{joined}',body[:start]+t+body[end:]))
 if fn.endswith('C7998'):
  for cast in ['(u64)(u16)buttons','(u64)(u32)buttons','(u64)(buttons & 0xFFFFU)']:
   for sig in ['u32','u16']:
    jobs.append(('homing-'+sig+cast,body.replace('u16 buttons',sig+' buttons').replace('(u64)(buttons & 0xFFFF)',cast)))
 if fn.endswith('C4E38'):
  for point in ['func_8002F9FC();','D_800451EC[D_802D3985]();']:
   for typ in ['s32','u32']:
    t=body.replace('{','{\n '+typ+' selector;',1).replace(point,point+'\n selector = arg0;').replace('switch (arg0)','switch (selector)').replace('if (arg0 == 5)','if (selector == 5)')
    jobs.append(('spill-'+typ+point,t))
 base=compile(fn,s,'baseline');out=[base]
 def run(job):
  label,t=job;full=s[:a]+t+s[b:];r=compile(fn,full,label,True)
  if r.get('words',999)<base['words']:
   p=OUT/(fn+'-extra-'+re.sub(r'[^\w-]','_',label)+'.c');p.write_text(full);r['candidate']=str(p);print(fn,r,flush=True)
  return r
 with ThreadPoolExecutor(max_workers=3) as pool:out+=list(pool.map(run,jobs))
 rows[fn]=out
 (OUT/'extra.json').write_text(json.dumps(rows,indent=2))
