import pathlib,sys,itertools,json
sys.path.insert(0,str(pathlib.Path(__file__).parent));import probe,tu
fn='func_801B2010';s=tu.draft(fn).read_text();_,pre=tu.ctx(fn);a=s.index('    arg1 = D_');b=s.index('    guTranslate',a)
best=17;res=[]
for storage,form,layout in itertools.product(range(8),range(6),range(8)):
 decl=['extern s32 D_801D309C;','s32 D_801D309C;','static s32 D_801D309C;','extern volatile s32 D_801D309C;','extern s32 D_801D309C[1];','extern struct {s32 count;} D_801D309C;','extern struct {s32 pad[3];s32 count;} counter_state;','extern volatile struct {s32 count;} D_801D309C;'][storage]
 expr=['D_801D309C']*4+['D_801D309C[0]','D_801D309C.count','counter_state.count','D_801D309C.count']
 setups=['counter = D_801D309C; pred = counter < 1; counter++;','counter = D_801D309C; pred = counter++ < 1;','counter = D_801D309C; pred = counter < 1;','counter = D_801D309C; pred = counter <= 0; counter++;','counter = D_801D309C; pred = counter < 1; counter++;','counter = D_801D309C; pred = counter++ < 1;']
 inc='counter + 1' if form==2 else 'counter';pred='pred == 1' if form==4 else 'pred'
 block=setups[form]+f' if ({pred}) {{ D_801D309C = {inc}; position = func_801B19F0(-6.0f, -150.0f, {inc}, 1); }} else {{ D_801D309C = {inc}; position = -150.0f; }}\n'
 if layout&1:block=block.replace(';',';\n')
 if layout&2:block=block.replace('{','{\n').replace('}','\n}\n')
 if layout&4:block=block.replace(' if','\nif').replace(' else','\nelse')
 src=s[:a]+block+s[b:];src=src.replace('    f32 position;','    s32 counter, pred;\n    f32 position;').replace('extern s32 D_801D309C;',decl)
 if storage>=4:src=src.replace('D_801D309C =',expr[storage]+' =').replace('= D_801D309C;','= '+expr[storage]+';')
 score,size=probe.probe(fn,pre+src);res.append([storage,form,layout,score,size])
 if score<best:best=score;pathlib.Path('/tmp/t077-storage-best.c').write_text(src);print('BEST',best,size,storage,form,layout,flush=True)
pathlib.Path('/tmp/t077-storage.json').write_text(json.dumps(res))
