import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
def partitions(items):
    if not items: yield []; return
    first,rest=items[0],items[1:]
    for p in partitions(rest):
        yield [[first]]+p
        for i in range(len(p)):
            yield p[:i]+[[first]+p[i]]+p[i+1:]
def names(parts, prefix):
    m={}
    for k,g in enumerate(parts):
        for r in g: m[r]=f'{prefix}{k}'
    return m
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
void func_801C8004(void) {
"""
def gen(mi, mp, usedvar_sep=True):
    I=lambda r: mi[r]; P=lambda r: mp[r]
    decl=''.join(f"    s32 {n};\n" for n in sorted(set(mi.values())))+''.join(f"    u8 *{n};\n" for n in sorted(set(mp.values())))+"    s32 conflict; u8 used;\n"
    body=f"""    conflict = 0;
    {P('c1')} = D_80292710[0]; {I('i')} = 0;
    for (;;) {{
        {I('v')} = *{P('c1')};
        if ({I('v')} != 0 && {I('v')} >= D_802926F8[0][{I('i')}]) {{ conflict = 1; }}
        {I('i')}++; {P('c1')}++;
        if ({I('i')} < 34) continue;
        break;
    }}
    {P('m')} = (u8 *)D_80127C68;
    do {{
        used = 0; {I('s')} = 0; {P('c2')} = {P('m')};
      next:
        {I('b')} = *{P('c2')}; {I('s')}++; {P('c2')}++;
        if ({I('b')} >= 8 || ((1 << {I('b')}) & used)) {{ conflict = 2; }}
        used |= 1 << {I('b')};
        if ({I('s')} != 6) goto next;
        {P('m')} += 6;
    }} while ({P('m')} != &D_80127C74);
    if (conflict != 0) {{ func_801C7F90(); }}
}}
"""
    return pre+decl+body
cands=[]
for pi in partitions(['i','v','s','b']):
    for pp in partitions(['c1','c2','m']):
        cands.append((pi,pp))
srcs=[gen(names(a,'n'),names(b,'p')) for a,b in cands]
out=lib.run('func_801C8004',srcs,prefix=False)
res=sorted(zip(out,cands,srcs),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,k,s in res[:10]: print(r,k)
open('/tmp/w/r8004d_best.c','w').write(res[0][2])
