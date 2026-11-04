import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; f32 temp_f0_2; f32 threshold; f32 bi; f32 n1; f32 n2; f32 n3; s32 var_s0; u8 *temp_v1;
    @A@if (D_8004AA28 != 1) { temp_v1 = *arg0; @B@
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC); @C@
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - bi;
        if (temp_f0 <= threshold) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0_2 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * arg2) - bi;
        if (threshold < temp_f0_2) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0_2); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
"""
chains=[["threshold = arg2;"],["n1 = arg2;","threshold = n1;"],["n1 = arg2;","n2 = n1;","threshold = n2;"],["n1 = arg2;","n2 = arg2;","threshold = n1;"],["n1 = arg2;","threshold = n1;","n2 = threshold;"],["threshold = arg2;","n1 = threshold;"],["threshold = arg2;","n1 = arg2;"],["threshold = arg2;","threshold = arg2;"]]
cands=[]
for ci,ch in enumerate(chains):
  for ca in range(3):
    for cb in range(ca,3):
      for variant in range(2):
        # bias then scale at C in order given by variant
        tail=["bi = D_800489F0;","arg2 = D_800489F4;"] if variant==0 else ["bi = D_800489F0;","n3 = D_800489F4;","arg2 = n3;"]
        slots={'A':[],'B':[],'C':[]}
        for st in ch: slots['ABC'[ca if st is ch[0] else cb]].append(st)
        slots['C']+=tail
        src=tmpl
        for k in 'ABC': src=src.replace('@'+k+'@',' '.join(slots[k])+' ')
        cands.append(((ci,ca,cb,variant),head+src))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:10]: print(r,k)
open('/tmp/w/r8001o_best.c','w').write(res[0][1][1])
