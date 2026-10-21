import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-116')
from probe import *
from sweep import layouts
import concurrent.futures,itertools

def run(r):
 fn=r['function'];s=source(r);a,b=bodybounds(s,fn);body=s[a:b];v=[]
 def add(l,t):v.append((l,s[:a]+t+s[b:]))
 if fn=='func_801C48E4':
  for typ in ['u16','s16']:
   v.append(('keep-casts-'+typ,s.replace('s32 arg1, s32 arg2',typ+' arg1, '+typ+' arg2')))
  for typ in ['u16','s16','s32']:
   v.append(('call-prototype-'+typ,s.replace('extern s32 func_8001D7E4();','extern s32 func_8001D7E4(s32, '+typ+', '+typ+', s32, s32);')))
 if fn=='func_801C8004':
  for form in ['do','for','goto']:
   t=body
   if form=='do':t=t.replace('for (;;) {','do {').replace('        if (var_a0 >= 34) {\n            break;\n        }\n    }','    } while (var_a0 < 34);')
   if form=='for':t=t.replace('for (;;) {','for (; var_a0 < 34; var_a0++, var_v0++) {').replace('        var_a0 += 1;\n        var_v0 += 1;\n        if (var_a0 >= 34) {\n            break;\n        }','')
   if form=='goto':t=t.replace('for (;;) {','first:\n    {').replace('        if (var_a0 >= 34) {\n            break;\n        }','        if (var_a0 < 34) goto first;')
   add(form,t)
  add('shift-on-branch',body.replace('    s32 bit;','    s32 bit;\n    s32 old;').replace('        bit = 1 << temp_v0;','').replace('var_v1 = bit,','var_v1 = 1 << temp_v0,').replace('        var_a1 = (var_a1 | var_v1) & 0xFF;','        old = var_a1;\n        var_a1 = (old | var_v1) & 0xFF;'))
 if fn=='func_801C7F90':
  add('raw-first-byte',body.replace('D_80127CC0.fields.first','(*(u8 *)&D_80127CC0)'))
  for order in itertools.permutations(range(4)):
   add('clear-order-'+''.join(map(str,order)),body.replace('for(i=0;i<32;) D_80127CC2[i++]=0;','for(i=0;i<32;i+=4) { '+''.join('D_80127CC2[i+%d]=0;'%j for j in order)+' }'))
 if fn=='func_801BD200':
  for o in itertools.permutations(range(3)):
   lines=['D_80282A60 = D_800684A0;','D_802D369C[0] = 0;','D_802D369C[1] = 1;']
   add('store-order-'+''.join(map(str,o)),body.replace('\n    '.join(lines),'\n    '.join(lines[j] for j in o)))
  add('explicit-byte-pointer',body.replace('{','{\n u8 *bytes = D_802D369C;',1).replace('D_802D369C[','bytes['))
 if fn=='func_801C8AE0':
  for typ in ['s32','u32','u16']:
   t=body.replace('    u16 c;','    u16 c;\n    '+typ+' packed;').replace('c |= func_801BF914((D_80127D00[i] >> 8) & 0xFF);','packed = c | func_801BF914((D_80127D00[i] >> 8) & 0xFF);').replace('*arg0++ = c >> 8;','*arg0++ = packed >> 8;').replace('*arg0++ = c;','*arg0++ = packed;')
   add('packed-'+typ,t)
 if fn=='func_801B43A8':
  add('indexed-inner',body.replace('other = group +','other = (u8)(random % 3U) + group; /*').replace('(u8)(random % 3U);','(u8)(random % 3U); */',1)) if False else None
  for step in ['group += 3;','group = group + 3;']:
   for num in ['s32','u32','u8']:
    add('group-step-'+num+step,body.replace('group = entry;',step).replace('    s32 i;','    '+num+' i;'))
 if fn=='func_801BE660':
  for div in ['2','2.0','2.0f']:
   for p in ['p','text']:
    t=body.replace('width / 2.0f','width / '+div).replace('    f32 width = 0.0f;','    f64 spacing = D_80292B88;\n    f32 width = 0.0f;').replace('+ D_80292B88 *','+ spacing *')
    if p=='text':t=t.replace('u8 *p = text;','u8 *p = text;\n    u8 *originalText = text;').replace('index = *p','index = *text').replace('p++;','text++;').replace('while (*p)','while (*text)').replace('list, matrix, text,','list, matrix, originalText,')
    add('cached-spacing-'+div+p,t)
 res=[];best=json.loads((ROOT/'tools/scratch/nonmatching/T-116/baseline.json').read_text())[fn];bs=s
 for label,t in v:
  x=compile(fn,t,label);res.append(x)
  if 'words' in x and x['words']<best['words']:best=x;bs=t
 # Layout only the best structural result.
 for label,t in layouts(bs,fn):
  x=compile(fn,t,'best/'+label);res.append(x)
  if 'words' in x and x['words']<best['words']:best=x;bs=t
 (WORK/(fn+'.more.c')).write_text(bs)
 (ROOT/'tools/scratch/nonmatching/T-116'/ (fn+'.more.json')).write_text(json.dumps(res,indent=2)+'\n')
 print(fn,best,flush=True)
with concurrent.futures.ThreadPoolExecutor(max_workers=3) as pool:list(pool.map(run,[r for r in ROWS if r['function'] in ['func_801C48E4','func_801C8004','func_801C7F90','func_801BD200','func_801C8AE0','func_801B43A8','func_801BE660']]))
