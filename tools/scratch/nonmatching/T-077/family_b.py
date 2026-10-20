import sys,pathlib,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2EF4';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);best=65;res=[]
for form,vartype,layout in itertools.product(range(10),['u32','u8','u16'],range(16)):
 src=s.replace('    u32 value;',f'    {vartype} value;\n    s32 counter, pred;')
 old='if (D_801D30C0++ < 10)'
 cond=['counter = D_801D30C0; pred = counter < 10; counter++; D_801D30C0 = counter; if (pred == 1)','counter = D_801D30C0; pred = counter < 10; counter++; if (pred == 1)','counter = D_801D30C0; if (counter++ < 10)','counter = D_801D30C0; if (counter < 10)','if (D_801D30C0++ < 10)','counter = D_801D30C0; if (counter++ < 10)','counter = D_801D30C0; pred = counter++ < 10; if (pred)','counter = D_801D30C0; pred = counter++ < 10; if (pred == 1)','counter = D_801D30C0; if (counter < 10)','counter = D_801D30C0; if (counter < 10)'][form]
 src=src.replace(old,cond)
 if form in [1,2,5,6,7]:src=src.replace('        value =','        D_801D30C0 = counter;\n        value =').replace('        p1 =','        D_801D30C0 = counter;\n        p1 =')
 if form in [3,8,9]:
  src=src.replace('D_801D30C0, 10)', 'D_801D30C0 = ++counter, 10)').replace('        p1 =','        D_801D30C0 = ++counter;\n        p1 =')
 if form==5:src=src.replace('D_801D30C0, 10)','counter, 10)')
 if form==8:src=src.replace('    s32 color2;','    u16 color2;')
 if form==9:src=src.replace('    u8 alpha;','    u8 alpha;\n    u8 old_alpha;').replace('| alpha);','| old_alpha);')
 if layout:
  a=src.index('s32 func_801B2EF4');head=src[:a];body=src[a:];rng=random.Random(layout);body=re.sub(r'(\s+|(?<=[;{}]))',lambda m:'\n' if rng.random()<.35 else ' ',body);src=head+body
 score,size=probe.probe(fn,pre+src);res.append([form,vartype,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-b-best.c').write_text(src);print('BEST',best,size,form,vartype,layout,flush=True)
pathlib.Path('/tmp/t077-b.json').write_text(json.dumps(res))
