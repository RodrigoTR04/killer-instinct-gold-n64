import sys,pathlib,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=pathlib.Path('/tmp/t077-branch-best.c').read_text();_,pre=tu.ctx(fn);best=14;res=[]
for form,layout in itertools.product(range(12),range(32)):
 src=s
 call=re.search(r'func_801B19F0\( -6\.0f, -150\.0f,\s*D_801D309C = \+\+arg1,\s*1\)',src).group()
 repl=['func_801B19F0(-6.0f, -150.0f, D_801D309C = ++arg1, 1)','func_801B19F0((f64)-6.0, (f64)-150.0, D_801D309C = ++arg1, 1)','(D_801D309C = ++arg1, func_801B19F0(-6.0f,-150.0f,arg1,1))','func_801B19F0(-6.0f,-150.0f,++D_801D309C,1)','(((-150.0f - -6.0f) * ((f32)(D_801D309C = ++arg1) / 1.0f)) + -6.0f)','(((-150.0 - -6.0) * ((f64)(D_801D309C = ++arg1) / 1.0)) + -6.0)','func_801AFA80(-6.0f,-150.0f,D_801D309C = ++arg1,1)','func_801B19F0(-6.0f,-150.0f,(D_801D309C = arg1 + 1),1)','func_801B19F0(-6.0f,-150.0f,(D_801D309C = arg1 += 1),1)','func_801B19F0(-6.0f,-150.0f,(D_801D309C = 1 + arg1),1)','func_801B19F0(-6.0f,-150.0f,(D_801D309C = ++arg1),arg3 = 1)','func_801B19F0(-6.0f,-150.0f,(D_801D309C = ++arg1),arg3)'][form]
 src=src.replace(call,repl)
 if form==6:src='extern f32 func_801AFA80(f32,f32,s32,s32);\n'+src
 if form==11:src=src.replace('arg1\n= D_801D309C;','arg3=1; arg1 = D_801D309C;')
 if layout:
  a=src.index('arg1\n=') if 'arg1\n=' in src else src.index('arg3=1; arg1 =');b=src.index('    guTranslate',a);block=src[a:b];rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.35 else ' ',block);src=src[:a]+block+'\n'+src[b:]
 score,size=probe.probe(fn,pre+src);res.append([form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-lerp-best.c').write_text(src);print('BEST',best,size,form,layout,flush=True)
pathlib.Path('/tmp/t077-lerp.json').write_text(json.dumps(res))
