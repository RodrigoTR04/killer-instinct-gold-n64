import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
X="(*(f32 *)((u8 *)(var_s1) + 0xF0))"
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; s32 var_s0; u8 *temp_v1;
    if (D_8004AA28 != 1) { temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
        var_s1 = &D_801D7E00;
        var_s0 = 0;
        loop_2:
        temp_f0 = X1 * 1500.0f - 590.0f;
        if (temp_f0 <= arg2) { func_8001BF1C(arg0, arg1, var_s0, temp_f0 EXTRA);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) {
                goto loop_2; } }
        var_s1 = &D_801D8550;
        var_s0 = 0x27; loop_5:
        temp_f0 = X1 * 1500.0f - 590.0f;
        if (arg2 < temp_f0) {
            func_8001BF1C(arg0, arg1, var_s0, temp_f0 EXTRA); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) {
                goto loop_5;
            }
        }
    }
}
""".replace("X1",X)
cands=[('plain',tmpl.replace(" EXTRA","")),('plus0',tmpl.replace(" EXTRA"," + 0.0f*arg2")),
 ('t_in_call',tmpl.replace(" EXTRA","")),]
out=lib.run('func_8001BDE0',[head+c[1] for c in cands])
for r,c in zip(out,cands): print(r,c[0])
open('/tmp/w/g_plain.c','w').write(head+cands[0][1])
