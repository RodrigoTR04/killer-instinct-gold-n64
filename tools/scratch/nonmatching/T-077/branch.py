import sys,pathlib,itertools,json,random,re
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=17;res=[]
for form,var,layout in itertools.product(range(8),['D_801D309C','arg1','arg3','counter'],range(16)):
 prefix='' if var=='D_801D309C' else var+' = D_801D309C; '
 inc='++'+var;update='' if var=='D_801D309C' else 'D_801D309C = '+var+';'
 call=f'func_801B19F0(-6.0f, -150.0f, {var}, 1)'
 early=f'{inc}; {update} position = {call};';late=f'{inc}; {update} position = -150.0f;'
 if form==0:block=prefix+f'if ({var} < 1) {{ {early} }} else {{ {late} }}'
 elif form==1:block=prefix+f'position = {var} < 1 ? ({inc}, {update.replace(";",",")} {call}) : ({inc}, {update.replace(";",",")} -150.0f);'
 elif form==2:block=prefix+f'if ({var} < 1) {{ position = {call.replace(var+", 1", "++"+var+", 1")}; {update} }} else {{ {late} }}'
 elif form==3:block=prefix+f'if ({var} < 1) {{ position = {call.replace(var+", 1", "D_801D309C = ++"+var+", 1")}; }} else {{ {late} }}'
 elif form==4:block=prefix+f'if ({var} < 1) {{ D_801D309C = {var} + 1; position = {call.replace(var+", 1", "D_801D309C, 1")}; }} else {{ D_801D309C = {var} + 1; position = -150.0f; }}'
 elif form==5:block=prefix+f'arg3 = {var} < 1; if (arg3) {{ {early} }} else {{ {late} }}'
 elif form==6:block=prefix+f'if ({var} >= 1) {{ {late} }} else {{ {early} }}'
 else:block=prefix+f'position = {var} < 1 ? func_801B19F0(-6.0f, -150.0f, ++D_801D309C, 1) : (D_801D309C++, -150.0f);'
 if layout: 
  rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.3 else ' ',block)
 src=s[:a]+block+'\n'+s[b:]
 if var=='counter':src=src.replace('    f32 position;','    s32 counter;\n    f32 position;')
 score,size=probe.probe(fn,pre+src);res.append([form,var,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-branch-best.c').write_text(src);print('BEST',best,size,form,var,layout,flush=True)
pathlib.Path('/tmp/t077-branch.json').write_text(json.dumps(res))
