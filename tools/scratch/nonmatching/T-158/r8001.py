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
def gen(c1, c2, thr_top, scale_arg2, tmp2):
    scale='arg2' if scale_arg2 else 'scale'
    th='threshold' if thr_top else 'arg2'
    pre_t="threshold = arg2; " if thr_top else ""
    t2='temp_f0' if tmp2==0 else 'temp_f0_2'
    return pre+f"""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {{ u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 scale; f32 temp_f24; s32 var_s0; u8 *temp_v1;
    {pre_t}if (D_8004AA28 != 1) {{ temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); temp_f24 = D_800489F0;
        {scale} = D_800489F4;
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {scale}) - temp_f24;
        if ({c1}) {{ func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {{
                goto loop_2; }} }}
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        {t2} = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * {scale}) - temp_f24;
        if ({c2}) {{
            func_8001BF1C(arg0, arg1, var_s0, {t2}); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {{
                goto loop_5;
            }}
        }}
    }}
}}
"""
cands=[]
for thr_top in (0,1):
  for sa in (0,1):
    for tmp2 in (0,1):
      t2='temp_f0' if tmp2==0 else 'temp_f0_2'
      th='threshold' if thr_top else 'arg2'
      for c1 in (f"temp_f0 <= {th}", f"{th} >= temp_f0", f"(temp_f0_2 = {th}) >= temp_f0", f"temp_f0 <= (temp_f0_2 = {th})"):
        for c2 in (f"{th} < {t2}", f"({t2} > {th})", f"(temp_f0 = {th}) < {t2}" if tmp2 else f"(temp_f0_2 = {th}) < {t2}"):
          cands.append(((thr_top,sa,tmp2,c1,c2),gen(c1,c2,thr_top,sa,tmp2)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[0],(t[0] or (999,999))[1]))
for r,(k,s) in res[:10]: print(r,k)
