import sys,pathlib,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);best=14;res=[]
for storage,form,layout in itertools.product(range(8),range(5),range(24)):
 src=s
 declarations=['extern struct {signed int value:32;} count;','extern union {s32 value;} count;','extern struct {s32 value;} count;','extern struct {signed int value:32;} D_801D309C;','extern volatile struct {signed int value:32;} count;','static s32 D_801D309C;','s32 D_801D309C;','extern s32 D_801D309C[1];']
 expr=['count.value','count.value','count.value','D_801D309C.value','count.value','D_801D309C','D_801D309C','D_801D309C[0]'][storage]
 src=src.replace('extern s32 D_801D309C;',declarations[storage]);start=src.index('    arg1 = D_');end=src.index('    guTranslate',start)
 call='func_801B19F0(-6.0f,-150.0f,D_801D309C,1)'
 blocks=[f'if (D_801D309C++ < 1) {{position = {call};}} else {{position = -150.0f;}}',src[start:end],f'arg1 = D_801D309C; arg3 = arg1 < 1; arg1++; if(arg3 == 1) {{ D_801D309C = arg1; position = {call.replace("D_801D309C,","arg1,")}; }} else {{ D_801D309C = arg1; position = -150.0f; }}',f'arg1 = D_801D309C; if(arg1 < 1) {{ position = {call.replace("D_801D309C,","D_801D309C = ++arg1,")}; }} else {{ D_801D309C = ++arg1; position = -150.0f; }}',f'position = D_801D309C++ < 1 ? {call} : -150.0f;']
 block=blocks[form].replace('D_801D309C',expr)
 if layout:
  rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.3 else ' ',block)
 src=src[:start]+block+'\n'+src[end:];score,size=probe.probe(fn,pre+src);res.append([storage,form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-field-best.c').write_text(src);print('BEST',best,size,storage,form,layout,flush=True)
pathlib.Path('/tmp/t077-field.json').write_text(json.dumps(res))
