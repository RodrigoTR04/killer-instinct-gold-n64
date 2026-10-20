import sys,pathlib,itertools,json,re,random
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=14;res=[]
for form,cond,layout in itertools.product(range(6),['D_801D309C++ < 1','(D_801D309C++ < 1) == 1','arg1++ < 1','arg3','D_801D309C++ <= 0'],range(32)):
 setup='arg1 = D_801D309C; ' if 'arg1' in cond else ('arg3 = D_801D309C++ < 1; ' if cond=='arg3' else '')
 store='D_801D309C = arg1; ' if 'arg1' in cond else ''
 call='position = func_801B19F0(-6.0f,-150.0f,D_801D309C,1);'
 if form==0:block=setup+f'switch ({cond}) {{case 1: {store}{call} break; default: {store}position = -150.0f; break;}}'
 elif form==1:block=setup+f'switch ({cond}) {{case 0: {store}position = -150.0f; break; default: {store}{call} break;}}'
 elif form==2:block=setup+f'switch ({cond}) {{case 1: {store}{call} break; case 0: {store}position = -150.0f; break;}}'
 elif form==3:block=setup+f'arg3 = {cond}; switch(arg3) {{case 1: {store}{call} break; default: {store}position = -150.0f; break;}}'
 elif form==4:block=setup+f'arg3 = {cond}; if (arg3) {{ {store}{call} }} else {{ {store}position = -150.0f; }}'
 else:block=setup+f'position = {cond}; if (position) {{ {store}{call} }} else {{ {store}position = -150.0f; }}'
 if layout:
  rng=random.Random(layout);block=re.sub(r'(\s+|(?<=[?:,;{}()]))',lambda m:'\n' if rng.random()<.3 else ' ',block)
 src=s[:a]+block+'\n'+s[b:];score,size=probe.probe(fn,pre+src);res.append([form,cond,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-switch-best.c').write_text(src);print('BEST',best,size,form,cond,layout,flush=True)
pathlib.Path('/tmp/t077-switch.json').write_text(json.dumps(res))
