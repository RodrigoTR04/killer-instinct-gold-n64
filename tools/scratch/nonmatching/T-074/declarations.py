import re,json,pathlib,random
import tu,probe
out=pathlib.Path(__file__).parent
# Token-preserving layout helpers, without importing the sweep's top-level driver.
exec((out/'layouts.py').read_text().split('results={}')[0])
rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);bs=s;vs=[]
 if fn.endswith('1210'):
  vs += [s.replace('s32, s32, s32, s32, f32);','u8, u8, u8, u8, f32);')]
  v=s.replace('    u32 alpha;','').replace('s32 arg3)', 'u32 arg3)');v=re.sub(r'\balpha\b','arg3',v);vs.append(v)
  vs += [s.replace('u32 alpha;',t+' alpha;') for t in ['s32','u16','u8']]
  vs += [s.replace('if (D_802C87C0 >= 9U) alpha = D_802C87C0 - 8;', 'alpha = D_802C87C0; if (alpha >= 9U) alpha -= 8;')]
 if fn.endswith('0610'):
  v=s.replace('extern u8 D_8029C4B0[], D_8029C8B0[], D_802C9F70[];', 'typedef struct { u8 pad[0xF8]; u8 *matrices; } Render0610;\nextern Render0610 D_802C9F70;\nextern u8 D_8029C4B0[], D_8029C8B0[];').replace('*(s32 *)(D_802C9F70 + 0xF8)','(s32)D_802C9F70.matrices');vs.append(v)
  vs += [v.replace('extern s32 D_802956F4, D_802CA068;','extern s32 D_802956F4;\nextern u8 *D_802CA068;').replace('+ D_802CA068','+ (s32)D_802CA068')]
 if fn.endswith('BB60'):
  vs += [s.replace('s16 i;',t+' i;') for t in ['s32','u32','u16']]
  vs += [re.sub(r'\bj\b','i',s.replace('s16 i;','s32 i;').replace('s32 j;',''))]
  vs += [v.replace('s16','u16') for v in vs[:]]
  vs += [v.replace('D_802C8D20[]','D_802C8D20[4096]').replace('D_802C9F20[]','D_802C9F20[64]').replace('D_802C9D20[]','D_802C9D20[256]') for v in vs[:]]
 if fn.endswith('6D40'):
  v=s.replace('func_8002F6F4();','func_8002F6F4(s32, s32, void *);').replace('func_801C4BD0();','func_801C4BD0(s32);').replace('&D_8004A258, var_a3','&D_8004A258').replace('func_801C4BD0(0x85, var_a3)','func_801C4BD0(0x85)');vs += [v]
  for base in [s,v]:
   vs += [base.replace('u8 temp_t3;','u32 temp_t3;').replace('u8 temp_t7;','u32 temp_t7;'),base.replace('u8 temp_t3;','s32 temp_t3;').replace('u8 temp_t7;','s32 temp_t7;')]
   vs += [base.replace('u8 temp_t3;','u32 temp_t3;').replace('u8 temp_t7;','u32 temp_t7;').replace('var_v1 = 1 & 0xFF;','var_v1 = (temp_t7 = 1) & 0xFF;')]
 if fn.endswith('49A8'):
  vs += [s.replace('u8 arg5, u8 arg6','u32 arg5, u32 arg6'),s.replace('s32 sp28;','').replace('sp28 = (s32) arg5;','')]
 if fn.endswith('3E40'):
  vs += [s.replace('s32 D_802D3900[16]','u64 D_802D3900[8]'),s.replace('u8 index, slot;','s32 index, slot;')]
 if fn.endswith('C3BC'):
  vs += [s.replace('s32 var_a2;','u32 var_a2;'),s.replace('s32 var_a2;','u8 var_a2;')]
  # Narrow masks are diagnostic only and must not be retained.
  vs=vs[:1]
 if fn.endswith('17D0'):
  vs += [s.replace('u8 D_80128300[];','T023PairB40 D_80128300;').replace('((s32 *)D_80128300)[player]','((s32 *)&D_80128300)[player]')]
 if fn.endswith('1DE4'):
  vs += [s.replace('extern u8 D_802BF8C0[];', 'typedef struct { s16 x,y,z; u16 flag; s16 s,t; u8 r,g,b,a; } Vertex1DE4;\nextern Vertex1DE4 D_802BF8C0[];').replace('extern u8 D_802BFE50[];','extern Vertex1DE4 D_802BFE50[];')]
 if fn.endswith(('2EF4','310C','3324','353C','3754','396C','3B84')):
  vs += [s.replace('u16 color;','u32 color;'),s.replace('u16 color;','s32 color;')]
  vs += [s.replace('u32 value;','').replace('s32 arg1,','u32 arg1,').replace('value','arg1'),s.replace('u32 value;','').replace('s32 arg3)','u32 arg3)').replace('value','arg3')]
 count=0
 for v in vs:
  head,body=parts(v,fn);cs=chunks(body)
  for k in range(5):
   cand=v if k==0 else head+render(cs,k-1,random.Random(74));count+=1;r=probe.probe(fn,pre+'\n'+cand)
   if r[0]<best[0]:best=r;bs=cand;print(fn,'decl',count,best,flush=True)
 row['declaration_probes']=count;row['new']=best;(out/(fn+'.best.c')).write_text(bs)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
