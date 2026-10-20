import sys,pathlib,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=14;res=[]
for pred,var,form,layout in itertools.product(['arg3','pred','alpha'],['arg1','counter'],range(8),range(24)):
 decl=('    s32 pred;\n' if pred=='pred' else '')+('    s32 counter;\n' if var=='counter' else '')
 setup=f'{var} = D_801D309C; {pred} = {var}++ < 1; '
 call=f'func_801B19F0(-6.0f,-150.0f,{var},{pred})'
 cond=[pred,pred+' == 1',pred+' != 0',pred,pred+' == 1',pred,pred+' == 1',pred][form]
 if form in [0,1,2]:block=setup+f'if ({cond}) {{D_801D309C = {var}; position = {call};}} else {{D_801D309C = {var};position = -150.0f;}}'
 elif form in [3,4]:block=setup+f'D_801D309C = {var}; if ({cond}) {{position = {call};}} else {{position = -150.0f;}}'
 elif form in [5,6]:block=f'{pred} = D_801D309C++ < 1; if({cond}) {{position = {call.replace(var+",","D_801D309C,")};}} else {{position=-150.0f;}}'
 else:block=setup+f'position = {pred} ? (D_801D309C = {var}, {call}) : (D_801D309C = {var}, -150.0f);'
 if layout:
  rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.3 else ' ',block)
 src=s[:a]+block+'\n'+s[b:];src=src.replace('    f32 position;',decl+'    f32 position;');score,size=probe.probe(fn,pre+src);res.append([pred,var,form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-reuse-best.c').write_text(src);print('BEST',best,size,pred,var,form,layout,flush=True)
pathlib.Path('/tmp/t077-reuse.json').write_text(json.dumps(res))
