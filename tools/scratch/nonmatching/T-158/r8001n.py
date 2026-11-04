import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
stm_dl=["temp_v1 = *arg0;","*arg0 += 8;","(*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;","(*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);"]
inits=["var_s1 = &D_801D7E00;","var_s0 = 0;"]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {
    u8 *var_s1; f32 temp_f0; s32 var_s0; u8 *temp_v1; f32 thr;
    thr = arg2;
    if (D_8004AA28 != 1) {
@BODY@
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f;
        if (temp_f0 <= thr) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) goto loop_2; }
        var_s1 = &D_801D8550; var_s0 = 0x27;
        if (arg1 > 3) thr = arg2;
        loop_5:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f;
        if (thr < temp_f0) { func_8001BF1C(arg0, arg1, var_s0, temp_f0); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) goto loop_5; }
    }
}
"""
cands=[]
# insert inits at any of 5 positions among dl stmts (order of the two inits both ways)
for io in (inits, inits[::-1]):
  for p1 in range(5):
    for p2 in range(p1,5):
      seq=list(stm_dl)
      # insert second first so indices stable
      seq.insert(p2,io[1]); seq.insert(p1,io[0])
      body='\n'.join('        '+s for s in seq)
      cands.append(((io[0][:9],p1,p2),head+tmpl.replace('@BODY@',body)))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:8]: print(r,k)
open('/tmp/w/r8001n_best.c','w').write(res[0][1][1])
