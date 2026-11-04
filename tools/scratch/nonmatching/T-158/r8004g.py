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
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
void func_801C8004(void) {
"""
roles=['i','v','c1','c2','m','s','b']
def gen(part):
    nm={}
    for k,g in enumerate(part):
        for r in g: nm[r]=f'n{k}'
    N=lambda r: nm[r]
    decl=''.join(f"    s32 n{k};\n" for k in range(len(part)))+"    s32 conflict; u8 used;\n"
    body=f"""    conflict = 0;
    {N('c1')} = (s32)D_80292710[0]; {N('i')} = 0;
    for (;;) {{
        {N('v')} = *(u8 *){N('c1')};
        if ({N('v')} != 0 && {N('v')} >= D_802926F8[0][{N('i')}]) {{ conflict = 1; }}
        {N('i')}++; {N('c1')}++;
        if ({N('i')} < 34) continue;
        break;
    }}
    {N('m')} = (s32)D_80127C68;
    do {{
        used = 0; {N('s')} = 0; {N('c2')} = {N('m')};
      next:
        {N('b')} = *(u8 *){N('c2')}; {N('s')}++; {N('c2')}++;
        if ({N('b')} >= 8 || ((1 << {N('b')}) & used)) {{ conflict = 2; }}
        used |= 1 << {N('b')};
        if ({N('s')} != 6) goto next;
        {N('m')} += 6;
    }} while ({N('m')} != (s32)&D_80127C74);
    if (conflict != 0) {{ func_801C7F90(); }}
}}
"""
    return pre+decl+body
parts=list(partitions(roles))
srcs=[gen(p) for p in parts]
out=lib.run('func_801C8004',srcs,prefix=False)
res=sorted(zip(out,parts,srcs),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,p,s in res[:10]: print(r,p)
open('/tmp/w/r8004g_best.c','w').write(res[0][2])
