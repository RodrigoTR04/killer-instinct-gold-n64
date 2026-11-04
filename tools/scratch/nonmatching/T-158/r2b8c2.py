import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
s=open('tools/scratch/nonmatching/T-025/func_801B2B8C.c').read()
# base T-025; add explicit pointer locals
def mk(flagvar, offvar, flag_pos, off_pos, decl_ptrs=True):
    b=s
    # flag: replace the D_801D308C update
    old_flag="if ((s32)D_801D308C <= 0) D_801D308C += 1;"
    assert old_flag in b
    new_flag=(f"{flagvar} = &D_801D308C; " if flag_pos=='at' else "")+f"if ((s32)*{flagvar} <= 0) *{flagvar} += 1;"
    b=b.replace(old_flag,new_flag)
    # offset: replace later uses after guTranslate
    old_off="if (D_801D3094 < 0) D_802C87D0 = D_801D3094 + 255; else D_802C87D0 = 255;"
    assert old_off in b
    new_off=(f"{offvar} = &D_801D3094; " if off_pos=='at' else "")+f"if (*{offvar} < 0) D_802C87D0 = *{offvar} + 255; else D_802C87D0 = 255;"
    b=b.replace(old_off,new_off)
    b=b.replace("p0->w1 = (alpha + D_801D3094) & 0xFF;",f"p0->w1 = (alpha + *{offvar}) & 0xFF;")
    return b
cands=[]
for fv,ov in [('fp_','op_')]:
  b=mk(fv,ov,'at','at')
  decls="    u8 *fp_; s16 *op_;\n"
  b=b.replace("    u8 alpha;\n","    u8 alpha;\n"+decls,1)
  cands.append((('ptrs',),b))
  # order variants
  b2=b.replace("    u8 alpha;\n"+decls,"    u8 alpha;\n    s16 *op_; u8 *fp_;\n",1)
  cands.append((('ptrs_rev',),b2))
out=lib.run('func_801B2B8C',[c[1] for c in cands])
for r,(k,x) in zip(out,cands): print(r,k)
for i,(k,x) in enumerate(cands): open(f'/tmp/w/r2b8c2_{i}.c','w').write(x)
