from attempts import *
rows=[]
def run(n,variants):
 p=next(p for p in paths if p.stem=='func_800'+n);fn=p.stem;s=(ROOT/(fn+'-base.c')).read_text();baseline=probe(s,fn);best=baseline;bs=s;bt='baseline';results=[]
 for tag,c in variants(s):
  r=probe(c,fn);results.append({'tag':tag,**r});
  if 'words' in r and ('words' not in best or r['words']<best['words']):best=r;bs=c;bt=tag
 (ROOT/(fn+'-best.c')).write_text(bs)
 rows.append({'function':fn,'baseline':baseline,'best':best,'best_tag':bt,'attempts':results})
 print(n,baseline.get('words',baseline.get('error')), '->',best.get('words'),bt,flush=True)
def stage(s):
 # 12-byte stage-part records, instead of pointer-element-scaled byte offsets.
 s='typedef struct { void *display; s16 flags,pad; s32 transform; } T054Part;\n'+s
 s=re.sub(r'\(\*\((s32|s16|u8 \*|void \*) \*\)\(\(u8 \*\)\(\(D_8004A4C0 \+ \((arg[01]) \* 0xC\)\)\) \+ (8|4)\)\)',lambda m:'((T054Part *)D_8004A4C0)['+m[2]+'].'+('transform' if m[3]=='8' else 'flags'),s)
 # Fixed offset accesses to the same records.
 def fixed(m):
  ty,off=m[1],int(m[2],0);field={0:'display',4:'flags',8:'transform'}.get(off%12)
  return '((T054Part *)D_8004A4C0)[%d].%s'%(off//12,field) if field else m[0]
 s=re.sub(r'\(\*\((s32|s16|u8 \*|void \*)\s*\*\)\(\(u8 \*\)\(D_8004A4C0\) \+ (0x[0-9A-Fa-f]+|\d+)\)\)',fixed,s)
 return s
# Real structure-copy rewrite: IDO recognizes aggregate assignment, unlike scalar stores.
def vertex(s):
 a=s.index('        D_80045060[0].words[0]');b=s.index('    }\n    var_v0_2',a)
 return s[:a]+'''        *D_80045060 = D_8004ADE8;
        *D_80045064 = D_8004ADF8;
        var_a0 = &D_8004AE08;
        var_a1 = &D_8004AE18;
        var_a2 = &D_8004AE28;
        var_v1 = &D_8004AE38;
        var_v0 = &D_80045068;
        do {
            *var_v0[0] = *var_a0;
            *var_v0[1] = *var_a1;
            *var_v0[2] = *var_a2;
            *var_v0[3] = *var_v1;
            var_a0 += 4; var_a1 += 4; var_a2 += 4; var_v1 += 4;
            var_v0 += 4;
        } while (var_v1 != &D_8004AEB8);
'''+s[b:]
run('170C4',lambda s:[('aggregate vertex copies',vertex(s)),('indexed vertex copy loop',vertex(s).replace('var_v1 != &D_8004AEB8','var_a0 != &D_8004AE88'))])
for n in ['18F20','1808C','193DC','18AE0','1AD04','1B134','1B620']:
 def variants(s,n=n):
  t=stage(s)
  if n=='1808C':t=re.sub(r'extern (s8|u8) D_8004A730;', 'extern u8 D_8004A730[8];',t)
  if n=='1AD04':t=t.replace('*(D_8004A920 + sp24)', 'D_8004A920[sp2C]')
  yield 'typed stage records',t
  # Replace redundant float pointer spills by using the original indexed arrays.
  if n in ['1AD04','1B134']:
   t=t.replace('D_8004A4C0 + (arg0 * 0xC)','(u8 *)D_8004A4C0 + (arg0 * 0xC)').replace('D_8004A4C0 + (arg1 * 0xC)','(u8 *)D_8004A4C0 + (arg1 * 0xC)')
   yield 'byte-correct stage indexing',t
  # Recast fixed transform floats as indexed loads/stores.
  for arr in ['D_8004A740','D_8004A800','D_8004A860','D_8004A8C0','D_8004A920']:
   t=re.sub(r'\(\*\(f32 \*\)\(\(u8 \*\)\('+arr+r'\) \+ (0x[0-9A-Fa-f]+|\d+)\)\)',lambda m:arr+'[%d]'%(int(m[1],0)//4),t)
  yield 'indexed transform arrays',t
 run(n,variants)
# Eliminate accidental signed-halfword truncation in color arithmetic: original uses full registers.
run('1BB64',lambda s:[('full-width color intermediates',re.sub(r'\bs16 (var_\w+|temp_\w+);',r's32 \1;',s)),('indexed color loop',s.replace('var_a3 += 1;','var_a3++;').replace('s16 colors[3];','s32 colors[3];').replace('s16 *var_a3;','s32 *var_a3;'))])
run('1E0B4',lambda s:[('full-width scale locals',s.replace('u16 var_t1;','u32 var_t1;').replace('u16 var_t2;','u32 var_t2;')),('unsigned half scale',s.replace('(u16) ((s32) var_t1 / 2)','var_t1 >> 1')),('boolean mirror flag',s.replace('''if ((s32) (*(u8 *)((u8 *)(temp_t3) + 0x21)) >= 0x80) {
                            var_t4 = 1;
                        } else {
                            var_t4 = 0;
                        }''','var_t4 = (*(u8 *)(temp_t3 + 0x21) & 0x80) != 0;'))])
run('1D080',lambda s:[('indexed sprite fields',re.sub(r'\(\*\(u8 \*\*\)\(\(u8 \*\)\(D_8004CED0\) \+ (0x[0-9A-F]+)\)\)',lambda m:('(u8 *)0' if False else 'D_8004CED0[%d].%s'%(int(m[1],0)//28,'unk0' if int(m[1],0)%28==0 else 'data')),s)),('full-width buffer selectors',s.replace('u8 temp_t9;','u32 temp_t9;').replace('u8 temp_t9_2;','u32 temp_t9_2;'))])
# Natural counted grayscale loop, instead of manually four-way unrolled m2c.
def gray(s):
 a=s.index('    if (D_8004EAB8 == 1)');return s[:a]+'''    if (D_8004EAB8 == 1) {
        s32 i;
        for (i = 0; i < 16; i++) {
            s32 pixel = var_v0[i];
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            ((u16 *)0)[i] = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[temp_t6] == 9 && D_8004EA78 < 2) {
        s32 i;
        for (i = 0; i < 16; i++) ((u16 *)0)[i] = 0;
    } else {
        s32 i;
        for (i = 0; i < 16; i++) ((u16 *)0)[i] = var_v0[i];
    }
}
'''
run('1D47C',lambda s:[('counted palette loops',gray(s)),('narrow selector ABI',gray(s).replace('s32 arg0','u8 arg0'))])
# Common graphics command cursor idiom, controlling alias/reload behavior.
def gfx(s):
 s=re.sub(r'(\w+) = \*(arg0|list);\s*\*\2 = \1 \+ 1;',r'\1 = (*\2)++;',s)
 return s
for n in ['131A4','253D0','27E1C','28230','29BE0']:
 def variants(s,n=n):
  t=gfx(s);yield 'postincrement command cursor',t
  # Original GBI writes first word then second; test that natural macro order.
  t=re.sub(r'(\w+)->(w1|value) = ([^;]+);\s*\1->(w0|command) = ([^;]+);',r'\1->\4 = \5; \1->\2 = \3;',t)
  yield 'GBI command order',t
  if n=='131A4':yield 'full-width part counters',t.replace('s16 part, i;','s32 part, i;')
  if n=='27E1C':yield 'full-width age arithmetic',t.replace('u8 var_t1;','s32 var_t1;')
  if n=='28230':yield 'background pointer cursor',t.replace('packed=D_801D7490[i*12]','packed=*(D_801D7490+i*12)')
  if n=='29BE0':yield 'signed halfword loop counters',t.replace('s32 i,j,alpha;','s16 i,j; s32 alpha;')
 run(n,variants)
# DMA's production signed ABI; integer subtraction on linker symbols.
for n in ['24714','241BC','216D4']:
 def variants(s):
  t=s.replace('boot_dma(void *,void *,s32)','boot_dma(s32,s32,s32)')
  t=re.sub(r'boot_dma\(([^,\n]+),([^,\n]+),([^;\n]+)\);',lambda m:'boot_dma((s32)('+m[1]+'), (s32)('+m[2]+'), '+re.sub(r'\b(D_[0-9A-F]+) - (D_[0-9A-F]+)\b',r'(s32)\1 - (s32)\2',m[3])+');',t)
  yield 'signed DMA address arithmetic',t
  yield 'integer resource dispatch',t.replace('u8 temp_v0;','s32 temp_v0;').replace('u16 id,i,alternate=0;','u16 id; s32 i,alternate=0;')
 run(n,variants)
# Struct and loop changes for audio constructors and decoding.
run('30440',lambda s:[('signed 16-bit decode counters',s.replace('s32 y;','s16 y;').replace('s32 x;','s16 x;')),('byte source cursor',s.replace('s32 source = 8;','u8 *source = image + 8;').replace('image[source++]','*source++')),('unsigned width height',s.replace('s32 width','u32 width').replace('s32 height','u32 height'))])
run('39C08',lambda s:[('unsigned command count',s.replace('s16 count = 0','s32 count = 0').replace('s16 *, s32','s32 *, s32')),('client time pointer cache',s.replace('synth->nextTime = earliest->samples;','synth->nextTime = earliest->samples;').replace('s32 distance =','s32 distance =')),('sample count short',s.replace('s32 n = samples','s16 n = samples'))])
run('3EF90',lambda s:[('native 16-bit loop index',s.replace('u32 i;','u16 i;').replace('i = (i+1)&0xFFFF','i++')),('signed parameter cursor',s.replace('u32 index = 2;','s32 index = 2;')),('sequential parameter pointer',s.replace('u32 index = 2;','s32 *cursor;').replace('    effect->count = params[0];','    cursor = params + 2;\n    effect->count = params[0];').replace('params[index++]','*cursor++').replace('params[index]','*cursor').replace('index++;','cursor++;'))])
run('327E8',lambda s:[('correct byte offsets in frequency tree',s.replace('temp_v0 + var_a1','(s32 *)((u8 *)var_a1 + temp_v0)').replace('var_a1 += 4','var_a1 += 1').replace('var_a0 += 4','var_a0 += 1').replace('*(var_a1 - 0x404)','*(var_a1 - 0x101)').replace('var_a0 -= 0x404','var_a0 -= 0x101').replace('var_t2 -= 4','var_t2 -= 1').replace('*(s32 *)(var_t2 + -4)','var_t2[-1]').replace('var_v1_2 + var_a0','(s32 *)((u8 *)var_a0 + var_v1_2)')),('word tree search cursor',s.replace('u8 *var_v0_2;','s32 *var_v0_2;').replace('var_v0_2 = (u8 *)var_a0 + 0x400','var_v0_2 = (s32 *)((u8 *)var_a0 + 0x400)'))])
run('297A4',lambda s:[('signed loop counters narrowed',s.replace('s32 i=0,j,angle=0','s16 i=0,j; s32 angle=0')),('indexed free burst search',s.replace('i++; p++;','i++; p=&D_80061D60[i];')),('signed random geometry',s.replace('(float)(u32)','(float)(s32)'))])
run('2A4F0',lambda s:[('narrow sequence length',s.replace('size,i,length;','size,i; u16 length;')),('signed DMA declarations', 'extern void boot_dma(s32,s32,s32);\n'+re.sub(r'boot_dma\(([^,]+),([^,]+),([^;]+)\);',r'boot_dma((s32)\1,(s32)\2,\3);',s)),('sequence count unsigned',s.replace('size,i,length;','size,length; u32 i;'))])
run('2AB90',lambda s:[('signed allocation loops',s.replace('u32 i;','s32 i;')),('parameter copy aligned words',s.replace('u32 words[66]','u64 words[33]')),('rounded frame expression',s.replace('D_80068168=++n','n++; D_80068168=n'))])
run('2E150',lambda s:[('unsigned exponent high word',s.replace('s32 exponent;','u32 exponent;')),('double square root',s.replace('extern float sqrtf(float);','extern double sqrt(double);').replace('sqrtf((float)z)','sqrt(z)')),('Horner operation order',s.replace('return z*p*x/q+x','return x+x*(z*p/q)').replace('return 0.5*(z*p*t/q+t)','return 0.5*(t+t*(z*p/q))'))])
run('16910',lambda s:[('cached angle vector',s.replace('    f32 x;','    f32 x; f32 *angles = D_8004A8C0;').replace('D_8004A8C0[','angles[')),('signed random return',s.replace('extern u32 func_800326F0','extern s32 func_800326F0')),('natural decrement guard',s.replace('if (D_8004A986 > 0) D_8004A986--;','if (D_8004A986 != 0) D_8004A986--;'))])
run('17A68',lambda s:[('typed stage pointer',s.replace('void func_80017A68(void) {','void func_80017A68(void) {\n    T03317A68StagePart *parts = (T03317A68StagePart *)D_8004A4C0;').replace('((T03317A68StagePart *)D_8004A4C0)[','parts[')),('indexed byte table',s.replace('(&D_8004A5E0)[35]','((s8 *)&D_8004A5E0)[35]').replace('(&D_8004A5E0)[42]','((s8 *)&D_8004A5E0)[42]'))])
run('17D6C',lambda s:[('typed stage indices',stage(s).replace('(s32)D_8004A4C0[2]','((T054Part *)D_8004A4C0)[0].transform').replace('(s32)D_8004A4C0[71]','((T054Part *)D_8004A4C0)[23].transform')),('indexed transforms across calls',s.replace('*pitch','D_8004A860[index]').replace('*roll','D_8004A920[index]'))])
# 25D58 IDO's original has a peeled odd iteration and a two-row unrolled loop.
run('25D58',lambda s:[('word-aligned local height arrays',s.replace('u8 value[13]','u32 align; u8 value[9]').replace('u8 value[14]','u32 align; u8 value[10]').replace('heights.value[x-6]','((u8 *)&heights)[x-6]').replace('otherHeights.value[x-111]','((u8 *)&otherHeights)[x-111]')),('narrow row index',s.replace('s32 y, end, pixelXor, alphaXor;','s16 y; s32 end, pixelXor, alphaXor;')),('countdown height loop',s.replace('for (y=10;y<end;y++)','for (y=10;y!=end;y++)'))])
(ROOT/'refine.json').write_text(json.dumps(rows,indent=2)+'\n')
