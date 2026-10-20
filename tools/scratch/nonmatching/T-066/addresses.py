import sys,re,json
sys.path.insert(0,'tools/scratch/nonmatching/T-066');import tu,probe
results={}
for addr in ['801B6528','801B695C','801C51F8','801C35D8']:
 fn='func_'+addr;p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);vs=[]
 if addr=='801B6528':
  for typ in ['s32','u32','s64','u64']:
   v=s.replace('void *arg1',typ+' arg1');vs.append(('integer card '+typ,v))
  for typ in ['s32','u32']:
   v=s.replace('void *arg2',typ+' arg2').replace('guTranslate(arg2,','guTranslate((void *)arg2,');vs.append(('integer matrix '+typ,v))
 if addr=='801B695C':
  for typ in ['s32','u32']:
   v=s.replace('T029Asset *arg0',typ+' arg0').replace('arg0->frames','((T029Asset *)arg0)->frames');vs.append(('integer asset '+typ,v))
  for typ in ['const T029Asset *','volatile T029Asset *']:
   vs.append((typ,s.replace('T029Asset *arg0',typ+'arg0')))
 if addr=='801C51F8':
  for typ in ['s32','u32']:
   v=s.replace('T021Gfx **arg0',typ+' arg0').replace('(*arg0)','(*(T021Gfx **)arg0)');vs.append(('integer dl '+typ,v))
 if addr=='801C35D8':
  for typ in ['s32','u32']:
   v=s.replace('T030Cloud *arg1',typ+' arg1').replace('cloud = arg1','cloud = (T030Cloud *)arg1');vs.append(('integer cloud '+typ,v))
 for label,v in vs:
  r=probe.probe(fn,pre+v)
  if r<best:best=r;p.with_suffix('.t066-best').write_text(v);print(fn,label,r)
 results[fn]={'best':best,'tested':len(vs)};print(fn,results[fn])
(probe.ROOT/'tools/scratch/nonmatching/T-066/addresses-results.json').write_text(json.dumps(results,indent=2))
