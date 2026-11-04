import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head=open('tools/scratch/nonmatching/T-022/func_8001BDE0.c').read().split('void func_8001BDE0')[0]
tmpl="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {
    u8 *var_s1; f32 temp_f0; s32 var_s0; u8 *temp_v1; f32 thr; f32 bi; f32 sc;
    @A@thr = arg2;
    if (D_8004AA28 != 1) { temp_v1 = *arg0;
        *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
        @B@
        var_s1 = &D_801D7E00; var_s0 = 0;
        loop_2:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * @S@) - @BI@;
        if (temp_f0 <= thr) { func_8001BF1C(arg0, arg1, var_s0, temp_f0);
            var_s0 += 1; var_s1 += 0x30;
            if (var_s0 < 0x28) goto loop_2; }
        var_s1 = &D_801D8550; var_s0 = 0x27;
        if (arg1 > 3) thr = arg2;
        loop_5:
        temp_f0 = ((*(f32 *)((u8 *)(var_s1) + 0xF0)) * @S@) - @BI@;
        if (thr < temp_f0) { func_8001BF1C(arg0, arg1, var_s0, temp_f0); var_s0 -= 1; var_s1 -= 0x30;
            if (var_s0 >= 0) goto loop_5; }
    }
}
"""
cands=[]
for S,BI,B in [('1500.0f','590.0f',''),('sc','bi','bi = 590.0f; sc = 1500.0f;'),('sc','bi','sc = 1500.0f; bi = 590.0f;'),('sc','590.0f','sc = 1500.0f;'),('1500.0f','bi','bi = 590.0f;'),
               ('D_800489F4','D_800489F0',''),('sc','bi','bi = D_800489F0; sc = D_800489F4;'),('sc','bi','sc = D_800489F4; bi = D_800489F0;')]:
    for A in ('',):
        src=tmpl.replace('@A@',A).replace('@B@',B).replace('@S@',S).replace('@BI@',BI)
        cands.append(((S,BI,B),head+src))
out=lib.run('func_8001BDE0',[c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for i,(k,s) in enumerate(cands): open(f'/tmp/w/m_{i}.c','w').write(s)
