import re,json,pathlib
import tu,probe
out=pathlib.Path(__file__).parent;rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);bs=s;vs=[]
 if fn in ['func_801BF720','func_801BF914']:
  vs.append(re.sub(r"case ([^:]+): return ([^;]+);",r'case \1: result = \2; break;',s))
  vs.append(re.sub(r"case ([^:]+): return ([^;]+);",r'case \1:\nresult = \2;\nbreak;',s))
  vs += [v.replace("    result = 27;\n",'') for v in vs[:]] if fn.endswith('F914') else []
 if fn.endswith('7998'):
  vs=[s.replace('(u64)(buttons & 0xFFFF)',x) for x in ['(u64)(u32)(buttons & 0xFFFF)','(u64)(u32)buttons','(u64)(buttons & 0xFFFFU)','(u64)(u32)(buttons & 0xFFFFU)']]
 if fn.endswith('2010'):
  a='arg1 = D_801D309C;\n    arg3 = arg1 < 1;\n    arg1++;\n    D_801D309C = arg1;'
  vs=[s.replace(a,x) for x in ['arg3 = D_801D309C++ < 1;','arg1 = D_801D309C++;\narg3 = arg1 < 1;','arg1 = D_801D309C;\narg3 = arg1 < 1;\nD_801D309C = arg1 + 1;']]
 if fn.endswith('35D8'):
  vs=[s.replace('i = 0;','').replace('offset = 0;','offset = 0;\ni = 0;'),s.replace('cloud = arg1;\n        offset = 0;','offset = 0;\ncloud = arg1;')]
 if fn.endswith('5064'):
  vs=[s.replace('f32 depth;','f32 depth;\nf32 zero;').replace('depth = D_80294890;','zero = 0.0f;\ndepth = D_80294890;').replace('offset), 0.0f,','offset), zero,'),s.replace('f32 depth;','f32 depth;\nf32 zero;').replace('depth = D_80294890;','depth = D_80294890;\nzero = 0.0f;').replace('offset), 0.0f,','offset), zero,')]
 count=0
 for v in vs:
  for style in range(4):
   cand=v
   if style&1:cand=re.sub(r';[^\S\n]+', ';\n',cand)
   if style&2:cand=re.sub(r';\s*\n\s*','; ',cand)
   count+=1;r=probe.probe(fn,pre+'\n'+cand)
   if r[0]<best[0]:best=r;bs=cand;print(fn,count,best,flush=True)
 row['token_probes']=count;row['new']=best;(out/(fn+'.best.c')).write_text(bs)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
