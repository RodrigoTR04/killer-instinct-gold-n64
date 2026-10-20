import sys,pathlib,itertools,json,random,re
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=14;res=[]
for limit,counter,form,layout in itertools.product(['arg3','arg1','limit'],['counter','arg1','arg3'],range(8),range(12)):
 if limit==counter:continue
 decl=('    s32 limit;\n' if limit=='limit' else '')+('    s32 counter;\n' if counter=='counter' else '')
 call=f'func_801B19F0(-6.0f, -150.0f, D_801D309C, {limit})'
 setup=f'{limit} = 1; '
 if form==0:block=setup+f'if (D_801D309C++ < {limit}) {{ position = {call}; }} else {{position = -150.0f;}}'
 elif form==1:block=setup+f'{counter} = D_801D309C; if ({counter}++ < {limit}) {{D_801D309C = {counter}; position = {call};}} else {{D_801D309C = {counter}; position = -150.0f;}}'
 elif form==2:block=setup+f'{counter} = D_801D309C; if ({counter} < {limit}) {{position = {call.replace("D_801D309C,",f"D_801D309C = ++{counter},")};}} else {{D_801D309C = ++{counter}; position = -150.0f;}}'
 elif form==3:block=setup+f'position = D_801D309C++ < {limit} ? {call} : -150.0f;'
 else:
  cond=['','', '', '',f'({counter} < {limit}) == 1',f'({counter} < {limit}) & 1',f'({counter} < {limit}) != 0',f'({counter} < {limit}) ? 1 : 0'][form]
  block=setup+f'{counter} = D_801D309C; if ({cond}) {{D_801D309C = ++{counter}; position = {call};}} else {{D_801D309C = ++{counter}; position = -150.0f;}}'
 if layout:
  rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.3 else ' ',block)
 src=s[:a]+block+'\n'+s[b:];src=src.replace('    f32 position;',decl+'    f32 position;')
 score,size=probe.probe(fn,pre+src);res.append([limit,counter,form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-limit-best.c').write_text(src);print('BEST',best,size,limit,counter,form,layout,flush=True)
pathlib.Path('/tmp/t077-limit.json').write_text(json.dumps(res))
