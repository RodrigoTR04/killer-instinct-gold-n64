import sys,itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-062');import tu,probe
fn='func_801C7CD0';p=tu.draft(fn);s=p.read_text();_,pre=tu.ctx(fn);best=probe.probe(fn,pre+s);n=0
old='''    u8 mode;
    u8 replay;
    mode = arg0;
    if (D_802D3E15) mode = 5;
    arg0 = mode;
    func_801C7A98(mode);
    mode = arg0;'''
starts=[old,'''    u8 replay;
    if (D_802D3E15) arg0 = 5;
    func_801C7A98();''', '''    u8 replay;
    if (D_802D3E15) arg0 = 5;
    func_801C7A98(arg0);''']
for st,arity,wide,chain in itertools.product(starts,[0,1,2],['s32','s64','u64'],[False,True]):
 v=s.replace(old,st)
 if st!=old:v=v.replace('mode','arg0')
 if arity==1:v=v.replace('func_801ADAD4(s32, s32 *, s32 *, u8 *)','func_801ADAD4(s32)').replace('func_801ADAD4(40, &D_80295700, &D_802956FC, &D_802D3A00)','func_801ADAD4(40)')
 if arity==2:v=v.replace('func_801CD038(void *, s32, s32 *, u8 *)','func_801CD038(void *, s32)').replace('func_801CD038(D_800F4070, replay - 1, &D_802956FC, &D_802D3A00)','func_801CD038(D_800F4070, replay - 1)')
 if wide!='s32':v=v.replace('s32 D_802D3678[4]',wide+' D_802D3678[2]').replace('D_802D3678[1] = 0x1000;\n        D_802D3678[0] = 0;\n        D_802D3678[3] = 0x1000;\n        D_802D3678[2] = 0;','D_802D3678[0] = 0x1000;\n        D_802D3678[1] = 0x1000;')
 if chain:v=v.replace('D_802956F8 = D_802956FC = D_80295700 = 0;','D_80295700 = D_802956FC = D_802956F8 = 0;')
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,r,starts.index(st),arity,wide,chain,flush=True)
print('phase1',n,best,flush=True)
s=p.read_text()
for rt,init,cache,post in itertools.product(['u8','s32','u32'],[0,1,2],[0,1],[0,1]):
 v=s.replace('u8 replay;',rt+' replay;')
 if init==1:v=v.replace('if (D_802D3E15 == 0) D_802D3E15 = 1;\n        replay = D_802D3E15;','replay = D_802D3E15;\n        if (!replay) replay = D_802D3E15 = 1;')
 if init==2:v=v.replace('if (D_802D3E15 == 0) D_802D3E15 = 1;\n        replay = D_802D3E15;','if (!(replay = D_802D3E15)) { D_802D3E15 = 1; replay = 1; }')
 if cache:v=v.replace('u8 replay;', 'u8 replay;').replace('    D_802D39F8 = 0.0f;','    u8 flag;\n    flag = D_802D3A06;\n    D_802D39F8 = 0.0f;').replace('if (D_802D3A06)','if (flag)').replace('D_802D3A06 == 0','flag == 0')
 if post:v=v.replace('u64 D_802D3678[2]','s64 D_802D3678[2]')
 r=probe.probe(fn,pre+v);n+=1
 if r<best:best=r;p.write_text(v);print(n,r,rt,init,cache,post,flush=True)
print('final',n,best)
