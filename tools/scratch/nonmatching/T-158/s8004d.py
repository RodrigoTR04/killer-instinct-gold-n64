import sys, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();

extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];

void func_801C8004(void)
    {
"""
D={'temp_v1':'u8 temp_v1;','var_t1':'s32 var_t1;','var_a2':'s32 var_a2;','var_a1':'u8 var_a1;','var_t2':'u8 *var_t2;','temp_v0':'s32 temp_v0;','var_v0':'u8 *var_v0;','var_a0':'s32 var_a0;','var_v1':'u8 *var_v1;'}
def body(sep):
    c2='var_v1' if sep else 'var_v0'
    return f""" var_t1 = 0;
    var_v0 = D_80292710[0]; var_a0 = 0; for (;;) {{
    temp_v1 = *var_v0;
    if ((temp_v1 != 0) && (((s32) temp_v1) >= ((s32) D_802926F8[0][var_a0]))) {{ var_t1 = 1; }} var_a0 += 1; var_v0 += 1; if (var_a0 < 34) {{ continue;
    }} break; }} var_t2 = (u8 *) D_80127C68; do {{ var_a1 = 0; var_a2 = 0;
    {c2} = var_t2;
    nextButton:
    temp_v0 = *{c2}; var_a2 += 1; {c2} += 1; if ((((s32) temp_v0) >= 8) || ((1 << temp_v0) & var_a1)) {{ var_t1 = 2;
    }} var_a1 |= 1 << temp_v0; if (var_a2 != 6) {{
    goto nextButton; }}
    var_t2 += 6; }} while (var_t2 != (&D_80127C74)); if (var_t1 != 0) {{ func_801C7F90(); }} }}
"""
random.seed(int(sys.argv[1]))
cands=[]
for sep in (0,1):
    for _ in range(250):
        names=[n for n in D if sep or n!='var_v1']
        random.shuffle(names)
        src=pre+'\n'.join(D[n] for n in names)+'\n'+body(sep)
        cands.append(((sep,names),src))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
res=sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])
for r,(k,s) in res[:6]: print(r,k)
best={}
for r,(k,s) in res:
    if r and k[0] not in best: best[k[0]]=(r,s)
for k,(r,s) in best.items(): print(k,r); open(f'tools/scratch/nonmatching/T-158/c/d_best{k}.c','w').write(s)
