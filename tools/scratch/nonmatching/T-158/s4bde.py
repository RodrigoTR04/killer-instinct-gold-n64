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
def gen(reg, thrmode, scmode, bimode):
    R=lambda n: 'register ' if n in reg else ''
    decl=f"u8 *var_s1; f32 temp_f0; f32 temp_f0_2; s32 var_s0; u8 *temp_v1; {R('t')}f32 threshold; {R('s')}f32 scale; {R('b')}f32 bias;"
    T='threshold' if thrmode else 'arg2'
    top="threshold = arg2; " if thrmode else ""
    S='scale' if scmode else {'':'1500.0f'}['']
    B='bias' if bimode else '590.0f'
    ass=''
    if bimode: ass+="bias = 590.0f; "
    if scmode: ass+="scale = 1500.0f; "
    return pre+f"""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {{ {decl}
    {top}if (D_8004AA28 != 1) {{ temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {ass}
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
cands=[]
for n in range(8):
    reg=''.join(c for i,c in enumerate('tsb') if n>>i&1)
    for tm in (0,1):
        for sm in (0,1):
            for bm in (0,1):
                if 't' in reg and not tm: continue
                if 's' in reg and not sm: continue
                if 'b' in reg and not bm: continue
                cands.append(((reg,tm,sm,bm),gen(reg,tm,sm,bm)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,s) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])[:10]: print(r,k)
