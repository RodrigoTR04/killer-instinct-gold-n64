import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
exec(open('tools/scratch/nonmatching/T-158/s1bde.py').read().split("def gen")[0].split("import lib")[1])
def gen(order, pos, valkinds, decls_order):
    # order: permutation of 'tsb'; pos: where assignments placed ('pre','mid','late')
    sc,bi=valkinds
    ex={'t':"threshold = arg2;",'s':"scale = D_800489F4;" if sc=='ext' else "scale = 1500.0f;",'b':"bias = D_800489F0;" if bi=='ext' else "bias = 590.0f;"}
    stm=' '.join(ex[c] for c in order)
    decl=' '.join(decls_order)
    pre_=stm if pos=='pre' else ''
    mid=stm if pos=='mid' else ''
    late=stm if pos=='late' else ''
    return pre+f"""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {{ u8 *var_s1; f32 temp_f0; f32 temp_f0_2; s32 var_s0; u8 *temp_v1; {decl}
    {pre_} if (D_8004AA28 != 1) {{ temp_v1 = *arg0; {mid}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {late}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * scale) - bias;
        if (temp_f0 <= threshold) {{ func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {{
                goto loop_2; }} }}
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * scale) - bias;
        if (threshold < temp_f0_2) {{
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {{
                goto loop_5;
            }}
        }}
    }}
}}
"""
cands=[]
for order in itertools.permutations('tsb'):
  for pos in ('pre','mid','late'):
    for vk in (('ext','ext'),('lit','lit')):
      for dord in (('f32 threshold;','f32 scale;','f32 bias;'),('f32 bias;','f32 scale;','f32 threshold;')):
        cands.append(((''.join(order),pos,vk,dord[0]),gen(order,pos,vk,dord)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,s) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])[:15]: print(r,k)
