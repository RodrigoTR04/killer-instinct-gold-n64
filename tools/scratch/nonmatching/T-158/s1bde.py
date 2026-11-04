import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern u8 D_8004AA28;
extern u8 D_8004AC88;
void func_8001BF1C(u8 **, s32, s32, f32);
extern f32 D_800489F0;
extern f32 D_800489F4;
extern u8 D_8004A4C8;
extern u8 D_801D7E00;
extern u8 D_801D8550;
"""
def gen(thr, sc, bi, order, scalereuse):
    # thr: 'param','top','inif'; sc/bi: 'lit','ext','loc','litloc'
    decl="u8 *var_s1; f32 temp_f0; f32 temp_f0_2; s32 var_s0; u8 *temp_v1; f32 threshold; f32 scale; f32 bias;"
    top=""; inif=""
    T='arg2' if thr=='param' else 'threshold'
    if thr=='top': top+="threshold = arg2; "
    if thr=='inif': inif+="threshold = arg2; "
    def val(kind,name,g,lit):
        if kind=='lit': return None,lit
        if kind=='ext': return None,g
        if kind=='loc': return f"{name} = {g};",name
        if kind=='litloc': return f"{name} = {lit};",name
    s_stmt,S=val(sc,'scale','D_800489F4','1500.0f')
    b_stmt,B=val(bi,'bias','D_800489F0','590.0f')
    stm=[x for x in ((b_stmt,s_stmt) if order else (s_stmt,b_stmt)) if x]
    inif+=' '.join(stm)
    body=f"""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {{ {decl}
    {top}if (D_8004AA28 != 1) {{ temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {inif}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {S}) - {B};
        if (temp_f0 <= {T}) {{ func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {{
                goto loop_2; }} }}
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {S}) - {B};
        if ({T} < temp_f0_2) {{
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {{
                goto loop_5;
            }}
        }}
    }}
}}
"""
    return pre+body
cands=[]
for thr in ('param','top','inif'):
    for sc in ('lit','ext','loc','litloc'):
        for bi in ('lit','ext','loc','litloc'):
            for order in (0,1):
                cands.append(((thr,sc,bi,order),gen(thr,sc,bi,order,0)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,s) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1]): print(r,k)
