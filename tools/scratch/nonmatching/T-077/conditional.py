import sys,pathlib,itertools,json,random,re
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=17;res=[]
for form,layout in itertools.product(range(12),range(32)):
 call='func_801B19F0(-6.0f, -150.0f, D_801D309C, 1)'
 blocks=[f'position = D_801D309C++ < 1 ? {call} : -150.0f;',f'position = (D_801D309C++ < 1) ? {call} : -150.0f;',f'position = D_801D309C++ >= 1 ? -150.0f : {call};',f'position = (arg1 = D_801D309C++, arg1 < 1) ? {call} : -150.0f;',f'position = (arg1 = D_801D309C, arg3 = arg1++ < 1, D_801D309C = arg1, arg3) ? {call} : -150.0f;',f'position = (++D_801D309C <= 1) ? {call} : -150.0f;',f'position = (D_801D309C++ < 1) ? {call} : -150.0;',f'if (D_801D309C++ < 1) position = {call}; else position = -150.0f;',f'arg1 = D_801D309C; position = (arg1++ < 1) ? (D_801D309C = arg1, {call}) : (D_801D309C = arg1, -150.0f);',f'arg1 = D_801D309C; if (arg1++ < 1) {{D_801D309C = arg1; position = {call};}} else {{D_801D309C = arg1; position = -150.0f;}}',f'position = (D_801D309C++ < 1) ? {call.replace("D_801D309C, 1","D_801D309C, (arg3 = 1)")} : -150.0f;',f'arg1 = D_801D309C++; arg3 = arg1 < 1; position = arg3 ? {call} : -150.0f;']
 block=blocks[form];rng=random.Random(layout)
 # source line boundary among all expression tokens
 if layout: block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.25 else ' ',block)
 src=s[:a]+block+'\n'+s[b:];score,size=probe.probe(fn,pre+src);res.append([form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-cond-best.c').write_text(src);print('BEST',best,size,form,layout,flush=True)
pathlib.Path('/tmp/t077-conditional.json').write_text(json.dumps(res))
