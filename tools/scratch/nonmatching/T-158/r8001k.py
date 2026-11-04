import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; s32 var_s0; u8 *temp_v1;
    {A}if (D_8004AA28 != 1) { temp_v1 = *arg0; {B}
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); {C}
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        T1 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f;
        if (T1 <= threshold) { func_8001BF1C(arg0, arg1, var_s0, T1);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        T2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f;
        if (threshold < T2) {
            func_8001BF1C(arg0, arg1, var_s0, T2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
"""
cands=[]
for t1,t2 in itertools.product(('temp_f0','arg2'),('temp_f0_2','temp_f0','arg2')):
  for pos in 'ABC':
    src=tmpl.replace('{A}','').replace('{B}','').replace('{C}','')
    if pos=='A': src=tmpl.replace('{A}','threshold = arg2; ').replace('{B}','').replace('{C}','')
    if pos=='B': src=tmpl.replace('{A}','').replace('{B}','threshold = arg2; ').replace('{C}','')
    if pos=='C': src=tmpl.replace('{A}','').replace('{B}','').replace('{C}','threshold = arg2; ')
    src=src.replace('T1',t1).replace('T2',t2)
    cands.append(((t1,t2,pos),head+src))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r8001k_best.c','w').write(res[0][1][1])
