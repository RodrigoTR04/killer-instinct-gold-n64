import re,json,pathlib,random
import tu,probe
out=pathlib.Path(__file__).parent
exec((out/'layouts.py').read_text().split('results={}')[0])
rows=json.loads((out/'results.json').read_text())
for fn in ['func_801B446C','func_801B1210','func_801BBB60','func_801C6D40','func_801C17D0','func_801B2EF4']:
 row=rows[fn];s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);bs=s;best=tuple(row['new']);vs=[]
 if fn.endswith('446C'):
  for t in ['u8','u32','s16']:
   vs += [s.replace('s32 flags;',t+' flags;'),s.replace('s32 bit;',t+' bit;'),s.replace('s32 choice;',t+' choice;')]
  vs += [s.replace('u8 pos;','s32 pos;'),s.replace('s32 flags;','u8 flags;').replace('s32 bit;','u32 bit;')]
 if fn.endswith('1210'):
  for t in ['u32','s32']:
   v=s.replace('u32 alpha;','').replace('s32 arg3)',t+' arg3)');v=re.sub(r'\balpha\b','arg3',v);vs.append(v)
  # Keep alpha in the loaded argument's ordinary local lifetime.
  vs += [s.replace('if (func_801AF67C(8)', 'alpha = arg3; if (func_801AF67C(8)').replace('else alpha = arg3 * 16;', 'else alpha *= 16;')]
 if fn.endswith('BB60'):
  for decl in ['u8 *p;', 's8 *p;', 'void *p;']:
   v=s.replace('u8 *p;',decl)
   if decl=='void *p;':continue
   vs.append(v)
  for base in [s,tu.draft(fn).read_text().replace('s16 i;','s32 i;')]:
   vs += [base.replace('palette = D_802C9D20;','').replace('i = 0;', 'palette = D_802C9D20; i = 0;',1)]
   vs += [base.replace('while ((u32)p < (u32)D_802C9D20);','while (p < (u8 *)D_802C9D20);').replace('while ((u32)p < (u32)D_802C9F60);','while (p < D_802C9F60);')]
   vs += [base.replace('i++;\n*palette = 0;\npalette++;','*palette++ = 0;\ni++;')]
 if fn.endswith('6D40'):
  v=s.replace('&D_8004A258, var_a3','&D_8004A258').replace('func_801C4BD0(0x85, var_a3)','func_801C4BD0(0x85)')
  for base in [s,v]:
   for t in ['s32','u32']:
    c=base.replace('u8 temp_t3;',t+' temp_t3;').replace('u8 temp_t7;',t+' temp_t7;')
    vs.append(c.replace('var_v1 = 1 & 0xFF;','temp_t7 = 1; var_v1 = temp_t7 & 0xFF;'))
 if fn.endswith('17D0'):
  for t in ['0','0ULL','0LL']:
   vs += [s.replace('return *out != 0;', 'if (*out == '+t+') return 0; return 1;')]
  m=re.search(r'b = &D_80128328\[player\]\[character\];\s*a = &D_80128310\[player\]\[character\];',s)
  if m:
   init=m[0];v=s[:m.start()]+s[m.end():];v=v.replace('if (player == 0) {','if (player == 0) { '+init).replace('} else {','} else { '+init);vs.append(v)
   vs += [v.replace('return *out != 0;', 'if (*out == 0ULL) return 0; return 1;')]
 if fn.endswith('2EF4'):
  counter='D_801D30C0'
  for param in ['arg1','arg3']:
   v=s.replace('if ('+counter+'++ < 10)',param+' = '+counter+'; '+counter+' = '+param+' + 1; if ('+param+' < 10)')
   vs.append(v)
   vs.append(v.replace(counter+' = '+param+' + 1;',param+'++; '+counter+' = '+param+';').replace('if ('+param+' < 10)','if ('+param+' <= 10)'))
 count=0
 for v in vs:
  head,body=parts(v,fn);cs=chunks(body);rng=random.Random(274)
  for k in range(20):
   cand=v if k==0 else head+render(cs,k-1 if k<5 else 4+k%3,rng);count+=1;r=probe.probe(fn,pre+'\n'+cand)
   if r[0]<best[0]:best=r;bs=cand;print(fn,count,best,flush=True)
 row['targeted_probes']=count;row['new']=best;(out/(fn+'.best.c')).write_text(bs)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
