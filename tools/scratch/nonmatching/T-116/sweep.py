"""Structural and token-preserving layout probes for the selected functions."""
from probe import *
import concurrent.futures,itertools
OUT=ROOT/'tools/scratch/nonmatching/T-116'
def variants(fn,s):
 a,b=bodybounds(s,fn); body=s[a:b]
 def replace(label,x):return (label,s[:a]+x+s[b:])
 v=[]
 if fn=='func_801C48E4':
  for typ in ['u16','s16','u32']:
   t=s.replace('s32 arg1, s32 arg2','%s arg1, %s arg2'%(typ,typ)).replace('    arg1 = (u16)arg1; arg2 = (u16)arg2;','')
   v.append(('parameters-'+typ,t))
 elif fn=='func_801C8004':
  v.append(replace('counted-loop',body.replace('for (;;) {','for (; var_a0 < 34;) {').replace('        if (var_a0 >= 34) {\n            break;\n        }','')))
  v.append(replace('uncached-shift',body.replace('        bit = 1 << temp_v0;','').replace('var_v1 = bit,','var_v1 = 1 << temp_v0,')))
  v.append(replace('separate-or-input',body.replace('    s32 bit;','    s32 bit;\n    s32 old;').replace('        var_a1 = (var_a1 | var_v1) & 0xFF;','        old = var_a1;\n        var_a1 = (old | var_v1) & 0xFF;')))
 elif fn=='func_801ADA04':
  v.append(replace('uncached-next',body.replace('      arg0->mode = next;\n      mode = next;','      arg0->mode = mode + 14;\n      mode = arg0->mode;')))
  v.append(replace('reload-pending',body.replace('    D_801CD4BC = pending;\n    osViSetMode(&D_800066D0[pending]);','    *pendingp = pending;\n    osViSetMode(&D_800066D0[*pendingp]);')))
  v.append(replace('shared-minus-one',body.replace('    D_801CD4BC = -1;','    pending = -1;\n    D_801CD4BC = pending;')))
 elif fn=='func_800268C0':
  v.append(replace('direct-field-stores',re.sub(r'    hw = p->halfW;.*?    size->h = h;', '    size->halfW = p->halfW;\n    size->halfH = p->halfH;\n    size->w = p->w2;\n    size->h = p->h;',body,flags=re.S)))
  v.append(replace('base-first-offset',body.replace('base + (index * 4)','(index * 4) + base').replace('base + ((((offsetHigh << 24) + (entry[9] << 8)) + entry[8]) + (entry[10] << 16))','(u8 *)((((((entry[11] << 24) + (u32)base) + entry[8]) + (entry[9] << 8))) + (entry[10] << 16))')))
 elif fn=='func_801B43A8':
  v.append(replace('independent-group-step',body.replace('group = entry;','group += 3;')))
  v.append(replace('base-first-random',body.replace('group + (u8)(random % 3U)','(u8)(random % 3U) + group')))
  v.append(('copy-prototype',s.replace('extern void memcpy(void *, void *, s32);','extern void *memcpy(void *, const void *, u32);')))
 elif fn=='func_801BEEA4':
  v.append(replace('retain-next-slot',body.replace('next = slot + 1;\n    entry = &entries[slot];','entry = &entries[slot];\n    next = ++slot;')))
  v.append(replace('cache-destination',body.replace('    entry->score = score;','    entry = &entries[index + 1];\n    entry->score = score;')))
 elif fn=='func_801C7F90':
  v.append(replace('separate-zero-stores',body.replace('D_80127CC0.fields.first=D_80127CC1=0;','D_80127CC0.fields.first=0; D_80127CC1=0;')))
  v.append(replace('indexed-clear',body.replace('for(i=0;i<32;) D_80127CC2[i++]=0;','for(i=0;i<32;i++) D_80127CC2[i]=0;')))
 elif fn=='func_801C0800':
  v.append(replace('color-add',body.replace('(((r << 24) | (g << 16)) | (b << 8)) | a','(((r << 24) + (g << 16)) + (b << 8)) + a')))
  v.append(replace('reuse-command',body.replace('FrontendGfxWords *command = (*list)++;','p = (*list)++;').replace('command->','p->')))
 elif fn=='func_801B0520':
  v.append(replace('direct-frame-reload',body.replace('(*frameState)','D_801D2EBC').replace('*frameState','D_801D2EBC')))
  v.append(replace('frame-in-input',re.sub(r'\bframe\b','arg3',body).replace('    s32 arg3;','')))
 elif fn=='func_801BE660':
  v.append(replace('pointer-in-input',body.replace('u8 *p = text;','u8 *p = text;\n    u8 *originalText = text;').replace('index = *p','index = *text').replace('p++;','text++;').replace('while (*p)','while (*text)').replace('list, matrix, text,','list, matrix, originalText,')))
  v.append(replace('force-fp-division',body.replace('width / 2.0f','(f32)((f64)width / 2.0)')))
  v.append(replace('local-double-constant',body.replace('    f32 width = 0.0f;','    f64 space = D_80292B88;\n    f32 width = 0.0f;').replace('+ D_80292B88 *','+ space *')))
 elif fn=='func_80024028':
  v.append(replace('ordered-bitwise-packing',body.replace('(alpha & 255) + (color[0] << 24) | (color[1] << 16) + (color[2] << 8)','(((alpha & 255) | (color[0] << 24)) | (color[1] << 16)) | (color[2] << 8)').replace('(color[5] << 8) | (color[3] << 24) | (color[4] << 16)','((color[5] << 8) | (color[3] << 24)) | (color[4] << 16)').replace('(color[8] >> 5)','((u32)color[8] >> 5)')))
 elif fn=='func_801C8C24':
  v.append(replace('advance-nibble-pointer',body.replace('arg0[i]','*arg0').replace('        D_80127D30[i * 2 + 1] = *arg0 >> 4;','        D_80127D30[i * 2 + 1] = *arg0++ >> 4;')))
  v.append(replace('explicit-nibble-unpack',body[:body.index('    for (i = 0; i < 4; i++)')]+''.join(f'    D_80127D30[{i*2}] = *arg0 & 15;\n    D_80127D30[{i*2+1}] = *arg0++ >> 4;\n' for i in range(4))+'}'))
 elif fn=='func_801C47E0':
  v.append(replace('left-offset-sum',body.replace('offset + func_800216D4(0, bank, arg2 + offset, arg3)','func_800216D4(0, bank, arg2 + offset, arg3) + offset')))
  v.append(replace('pointer-distance',body.replace('(0x1000 - (u32)arg2)','((u32)(-(s32)arg2))')))
 elif fn=='func_801BD200':
  v.append(replace('cached-limit',body.replace('{','{\n    s32 limit = D_800684A0;',1).replace('D_80282A60 = D_800684A0','D_80282A60 = limit').replace('arg0 < D_800684A0','arg0 < limit')))
  v.append(replace('cached-output',body.replace('{','{\n    s32 *output = &D_80282A60;',1).replace('D_80282A60 =','*output =')))
 elif fn=='func_801C8AE0':
  v.append(replace('wide-packed-character',body.replace('u16 c;','s32 c;')))
  v.append(replace('ordered-nibble-or',re.sub(r'\(D_80127D30\[(\d)\] << 4\) \| D_80127D30\[(\d)\]',r'D_80127D30[\2] | (D_80127D30[\1] << 4)',body)))
 return v

def layouts(s,fn):
 a,b=bodybounds(s,fn);t=s[a:b]
 # Only insert/remove whitespace: preserve tokens and for-loop semicolons.
 t=re.sub(r'/\*.*?\*/','',t,flags=re.S)
 for label,body in [('one-line',' '.join(t.split())),('braces',re.sub(r'([{}])',r'\n\1\n',t)),('statements',re.sub(r'([;{}])',r'\1\n',t)),('expanded',re.sub(r'([;{},])',r'\1\n',t))]:
  yield label,s[:a]+body+s[b:]

def run(r):
 fn=r['function'];s=source(r);base=compile(fn,s,'baseline');results=[base];best=base;bs=s
 candidates=variants(fn,s)
 # Probe individual structural hypotheses, then line forms on each valid candidate.
 for label,c in candidates:
  res=compile(fn,c,label);results.append(res)
  if 'words' in res and res['words']<best['words']:best=res;bs=c
 for parent,c in [('baseline',s),*candidates]:
  for label,l in layouts(c,fn):
   res=compile(fn,l,parent+'/'+label);results.append(res)
   if 'words' in res and res['words']<best['words']:best=res;bs=l
 (WORK/(fn+'.best.c')).write_text(bs)
 (OUT/(fn+'.probes.json')).write_text(json.dumps(results,indent=2)+'\n')
 print(fn,base.get('words'),'->',best,flush=True)
 return fn,best
if __name__=='__main__':
 with concurrent.futures.ThreadPoolExecutor(max_workers=5) as p:out=dict(p.map(run,ROWS))
 (OUT/'sweep.json').write_text(json.dumps(out,indent=2)+'\n')
