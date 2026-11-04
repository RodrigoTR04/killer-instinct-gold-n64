import sys, itertools, re
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
src=open('tools/scratch/nonmatching/T-158/w_2b8c_sib.c').read()
cands=[('sib',src)]
def drop(line_sub, fix=lambda s:s):
    return fix(src.replace(line_sub,""))
cands.append(('no_timer_ptr',src.replace("    s32 *timer = &D_801D30BC;\n","").replace("*timer","D_801D30BC")))
cands.append(('no_counter_ptr',src.replace("    s32 *counter = &D_801D30B8;\n","").replace("*counter","D_801D30B8")))
cands.append(('no_both_ptr',src.replace("    s32 *timer = &D_801D30BC;\n","").replace("*timer","D_801D30BC").replace("    s32 *counter = &D_801D30B8;\n","").replace("*counter","D_801D30B8")))
cands.append(('no_phase',src.replace("    f64 phase;\n","").replace("phase = (f64)arg3;\n    eye.y = (f32)(phase * D_80292970);","eye.y = (f32)((f64)arg3 * D_80292970);")))
cands.append(('no_prim',src.replace("    u32 primitive;\n","").replace("    primitive = 0xFA000000;\n","").replace("primitive","0xFA000000")))
cands.append(('no_packed',src.replace("    s32 packed;\n","").replace("packed","value")))
cands.append(('no_color2',src.replace("    s32 color2;\n","").replace("color2","value")))
cands.append(('p3',src.replace("*p0, *p1, *p2, *p3, *p4, *p5","*p0, *p1, *p2").replace("p3","p1").replace("p4","p1").replace("p5","p1")))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
