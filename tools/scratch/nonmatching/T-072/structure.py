import re,pathlib,json
import tu,probe
out=pathlib.Path(__file__).parent
rows=json.loads((out/'results.json').read_text())
for fn,row in rows.items():
 s=(out/(fn+'.best.c')).read_text();_,pre=tu.ctx(fn);best=tuple(row['new']);variants=[];count=0
 if fn.endswith('18F20'):
  v=s
  fields={0:'display',4:'flags',8:'transform'}
  # Reuse the TU's real 12-byte stage record, replacing raw stage stores.
  pattern=r'\(\*\((s16|s32|u8 \*)\s*\*\)\(\(u8 \*\)\(D_8004A4C0\) \+ (0x[0-9A-Fa-f]+|0)\)\)'
  def field(m):
   off=int(m[2],0);return '((T0331383CStagePart *)D_8004A4C0)['+str(off//12)+'].'+fields[off%12]
  v=re.sub(pattern,field,v);variants.append(v)
 if fn.endswith('191F0'):
  # Actor records are 0x100 bytes; their kind and signed velocity are at 0/+0x54.
  header='typedef struct { u8 kind; u8 pad[0x53]; s16 velocity; u8 tail[0xAA]; } T072Actor;\n'
  v=s
  for p in ['var_v1','temp_v0','temp_v0_2','temp_v0_3']:
   v=v.replace('(*(s16 *)((u8 *)('+p+') + 0x54))','((T072Actor *)'+p+')->velocity')
  variants.append(header+v)
 if fn.endswith('1AA90'):
  variants += [s.replace('u8 temp_t8;','u32 temp_t8;'),s.replace('u8 temp_t8;','s32 temp_t8;')]
 if fn.endswith('23EF0'):
  variants += [s.replace('s8 facing;','s32 facing;'),s.replace('u8 player, *count, old;','s32 player; u8 *count; u32 old;')]
 if fn.endswith('1E0B4'):
  # Two 0x30-byte render cache records; signed position is +0x1C, facing +0x21.
  header='typedef struct { u8 pad[0x1C]; s32 position; u8 pad20; u8 facing; u16 kind; u8 tail[12]; } T072RenderCache;\n'
  v=s.replace('(*(u16 *)((u8 *)(temp_t3) + 0x22))','((T072RenderCache *)temp_t3)->kind').replace('(*(u8 *)((u8 *)(temp_t3) + 0x21))','((T072RenderCache *)temp_t3)->facing').replace('(*(s32 *)((u8 *)(temp_t3) + 0x1C))','((T072RenderCache *)temp_t3)->position')
  variants.append(header+v)
 if fn.endswith('1D47C'):
  variants += [s.replace('s32 pixel =','u32 pixel ='),s.replace('u16 *var_v0;','u8 *palette;\nu16 *var_v0;').replace('var_v0 = (temp_t6 << 5) + (u8 *)D_8004CE90;','var_v0 = (u16 *)D_8004CE90[temp_t6];')]
 for v in variants:
  for k in range(4):
   c=v
   if k&1:c=re.sub(r';[^\S\n]+',';\n',c)
   if k&2:c=re.sub(r'\)\s*\{',')\n{',c)
   r=probe.probe(fn,pre+'\n'+c);count+=1
   if r[0]<best[0] and r[1]==row['new'][1]:best=r;s=c;print(fn,best,flush=True)
 row['structure_probes']=count;row['new']=best;(out/(fn+'.best.c')).write_text(s)
(out/'results.json').write_text(json.dumps(rows,indent=2)+'\n')
