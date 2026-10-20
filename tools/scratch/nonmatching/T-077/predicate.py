import sys,pathlib,itertools,json,random,re
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a);best=14;res=[]
for var,pred,typ,store,cond,layout in itertools.product(['arg1','counter','arg3'],['pred','arg1','arg3'],['s32','u32','u8','s16'],range(3),['== 1','!= 0','== 0'],range(4)):
 if var==pred:continue
 decl=('    s32 counter;\n' if var=='counter' else '')+('    '+typ+' pred;\n' if pred=='pred' else '')
 setup=f'{var} = D_801D309C; {pred} = {var} < 1; {var}++; '
 c=f'func_801B19F0(-6.0f, -150.0f, {var}, 1)'
 if store==0:block=setup+f'if ({pred} {cond}) {{ D_801D309C = {var}; position = {c}; }} else {{ D_801D309C = {var}; position = -150.0f; }}'
 elif store==1:block=setup+f'D_801D309C = {var}; if ({pred} {cond}) {{ position = {c}; }} else {{ position = -150.0f; }}'
 else:block=f'{pred} = D_801D309C++ < 1; if ({pred} {cond}) {{ position = {c.replace(var+", 1","D_801D309C, 1")}; }} else {{ position = -150.0f; }}'
 if cond=='== 0':block=block.replace(f'position = {c};','position = -150.0f;',1).replace('position = -150.0f; }}',f'position = {c}; }}') if False else block # diagnostic inverted excluded below
 if cond=='== 0':continue
 if layout&1:block=block.replace(';',';\n')
 if layout&2:block=block.replace('{','{\n').replace('}','\n}\n')
 src=s[:a]+block+'\n'+s[b:];src=src.replace('    f32 position;',decl+'    f32 position;')
 score,size=probe.probe(fn,pre+src);res.append([var,pred,typ,store,cond,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-pred-best.c').write_text(src);print('BEST',best,size,var,pred,typ,store,cond,layout,flush=True)
pathlib.Path('/tmp/t077-predicate.json').write_text(json.dumps(res))
