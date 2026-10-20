from attempts import *
import importlib.util
# Load helpers without executing the earlier rounds.
src=(ROOT/'refine.py').read_text();exec(src[src.index('def stage'):src.index("run('170C4'")])
rows=[]
def go(n,candidates):
 fn='func_800'+n;s=(ROOT/(fn+'-base.c')).read_text();r=[]
 for tag,c in candidates(s):
  x=probe(c,fn);r.append({'tag':tag,**x});(ROOT/(fn+'-'+tag.replace(' ','_')+'.c')).write_text(c)
  print(n,tag,x.get('words',x.get('error','')[:100]),x.get('bytes'),flush=True)
 rows.append({'function':fn,'attempts':r})
go('170C4',lambda s:[('struct vertex assignment',vertex(s).replace('typedef union { s32 words[4]; u8 bytes[16]; }','typedef struct { s32 words[4]; }')),('indexed vertex assignment',vertex(s).replace('typedef union { s32 words[4]; u8 bytes[16]; }','typedef struct { s32 words[4]; }').replace('var_a0 += 4; var_a1 += 4; var_a2 += 4; var_v1 += 4;','var_a0 += 4; var_a1 += 4; var_a2 += 4; var_v1 += 4;'))])
for n in ['24714','241BC']:
 def dma(s):
  t=s.replace('boot_dma(void *,void *,s32)','boot_dma(s32,s32,s32)')
  t=re.sub(r'(?m)^(\s+)boot_dma\(([^,\n]+),([^,\n]+),([^;\n]+)\);',lambda m:m[1]+'boot_dma((s32)('+m[2]+'), (s32)('+m[3]+'), '+re.sub(r'\b(D_[0-9A-F]+) - (D_[0-9A-F]+)\b',r'(s32)\1 - (s32)\2',m[4])+');',t)
  yield 'signed DMA ABI',t
  yield 'full width dispatch',t.replace('u8 temp_v0;','s32 temp_v0;')
  # resource slots are table rows of three pointer pairs, 24-byte stride
  yield 'table row resource base',t.replace('D_8004D278 + arg0 * 8','D_8004D278 + arg0 * 8')
 go(n,dma)
# Types in the framebuffer row loop make otherwise legal pointers look independent to IDO.
go('25D58',lambda s:[('unsigned row counter',s.replace('s32 y, end, pixelXor, alphaXor;','u32 y, end; s32 pixelXor, alphaXor;')),('equality loop bound',s.replace('y<end','y!=end')),('unsigned width fields',s.replace('s16 halfW,halfH,w,h,w2,h2','u16 halfW,halfH,w,h,w2,h2'))])
# 8001E0B4 stack and original offsets are already close; vary scale lifetimes.
go('1E0B4',lambda s:[('scale t1 full width',s.replace('u16 var_t1;','u32 var_t1;')),('scale t2 full width',s.replace('u16 var_t2;','u32 var_t2;')),('signed scales',s.replace('u16 var_t1;','s32 var_t1;').replace('u16 var_t2;','s32 var_t2;')),('unsigned actor index',s.replace('s32 var_s0;','u32 var_s0;'))])
# Signed-short components in the packed primitive color are not truncated in the original.
def colors(s):
 t=re.sub(r'\bs16 (var_\w+|temp_\w+);',r's32 \1;',s)
 yield 'integer colors and buffer',t.replace('s16 colors[3];','s32 colors[3];').replace('s16 *var_a3;','s32 *var_a3;')
 yield 'unsigned color intermediates',t.replace('s32 var_a3_2','u32 var_a3_2').replace('s32 var_v0_2','u32 var_v0_2')
 yield 'short color array int temp',t.replace('*var_a3 = temp_t8 + var_v1;','var_v1_2 = temp_t8 + var_v1;\n        *var_a3 = var_v1_2;').replace('if (*var_a3 >= 0x80)','if (var_v1_2 >= 0x80)')
go('1BB64',colors)
# Constructor field order is checked separately against disassembly.
go('3EF90',lambda s:[('effect byte fields',s.replace('u32 index = 2;','u16 index = 2;').replace('u32 i;','u16 i;')),('signed delay offsets',s.replace('u32 input, output;','s32 input, output;').replace('(f64)(u32)(section->output-section->input)','(f64)(section->output-section->input)'))])
# Repair 1808C's stale scalar A730 before measuring its baseline.
go('1808C',lambda s:[('array A730 declaration',re.sub(r'extern (s8|u8) D_8004A730;', 'extern u8 D_8004A730[8];',s))])
(ROOT/'focused.json').write_text(json.dumps(rows,indent=2)+'\n')
