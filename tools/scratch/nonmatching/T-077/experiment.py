import pathlib,sys,itertools,json
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn)
a=s.index('    arg1 = D_');b=s.index('    guTranslate',a)
best=17; results=[]
for var,typ,form,cond,layout in itertools.product(['arg1','arg3','counter'],['s32','u32'],range(6),['pred','pred == 1','pred != 0'],range(4)):
 decl=('    '+typ+' counter;\n' if var=='counter' else '')+'    s32 pred;\n'
 old='D_801D309C'
 setups=[f'{var} = {old}; pred = {var} < 1; {var}++;',f'{var} = {old}++; pred = {var} < 1; {var}++;',f'{var} = {old}; pred = {var}++ < 1;',f'{var} = {old}; pred = {var} < 1; ++{var};',f'pred = {old} < 1; {var} = {old} + 1;',f'{var} = {old}; pred = {var} < 1;']
 inc=f'{var} + 1' if form==5 else var
 block=decl+setups[form]+f' if ({cond}) {{ {old} = {inc}; position = func_801B19F0(-6.0f, -150.0f, {inc}, 1); }} else {{ {old} = {inc}; position = -150.0f; }}\n'
 if layout==1:block=block.replace(';',';\n')
 if layout==2:block=block.replace('{','{\n').replace('}','\n}\n')
 if layout==3:block=block.replace(';',';\n').replace('{','{\n').replace('}','\n}\n')
 # declarations must precede first statement
 block=block.replace(decl,'');src=s[:a]+block+s[b:];src=src.replace('    f32 position;',decl+'    f32 position;')
 score,size=probe.probe(fn,pre+src)
 if score<best:
  best=score;pathlib.Path('/tmp/t077-best.c').write_text(src);print('BEST',best,size,var,typ,form,cond,layout,flush=True)
 results.append([var,typ,form,cond,layout,score,size])
pathlib.Path('/tmp/t077-results.json').write_text(json.dumps(results))
