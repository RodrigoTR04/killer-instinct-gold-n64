import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
DL="temp_v1 = *arg0; *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);"
INIT1="var_s1 = &D_801D7E00; var_s0 = 0;"
L1="loop_2: temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f; if (temp_f0 <= arg2) { func_8001BF1C(arg0, arg1, var_s0, temp_f0); var_s0 += 1; var_s1 += 0x30; if (var_s0 < 0x28) { goto loop_2; } }"
INIT2="var_s1 = &D_801D8550; var_s0 = 0x27;"
L2="loop_5: temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * 1500.0f) - 590.0f; if (arg2 < temp_f0) { func_8001BF1C(arg0, arg1, var_s0, temp_f0); var_s0 -= 1; var_s1 -= 0x30; if (var_s0 >= 0) { goto loop_5; } }"
def wrap(kind, body):
    if kind=='none': return body
    if kind=='dw0': return "do { "+body+" } while (0);"
    if kind=='for1': return "for (;;) { "+body+" break; }"
    if kind=='while1': return "while (1) { "+body+" break; }"
    if kind=='blk': return "{ "+body+" }"
    if kind=='if1': return "if (1) { "+body+" }"
fn="void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) { u8 *var_s1; f32 temp_f0; s32 var_s0; u8 *temp_v1;\n    if (D_8004AA28 != 1) {\n%s\n    }\n}\n"
cands=[]
for kind in ('none','dw0','for1','while1','blk','if1'):
    for scope in ('dl+l1','l1','dl','all'):
        if scope=='dl+l1': b=wrap(kind,DL+" "+INIT1+" "+L1+" "+INIT2)+" "+L2
        elif scope=='l1': b=DL+" "+INIT1+" "+wrap(kind,L1)+" "+INIT2+" "+L2
        elif scope=='dl': b=wrap(kind,DL)+" "+INIT1+" "+L1+" "+INIT2+" "+L2
        else: b=wrap(kind,DL+" "+INIT1+" "+L1+" "+INIT2+" "+L2)
        cands.append(((kind,scope),head+fn%b))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,x) in sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1])): print(r,k)
