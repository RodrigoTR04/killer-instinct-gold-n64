import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
head="""extern u8 D_8004AA28;
void func_8001BF1C(u8 **, s32, s32, f32);
extern u8 D_8004A4C8;
typedef struct { f32 z; f32 y; u8 pad[0x28]; } Item8001;
extern struct { u8 pad[0xF0]; Item8001 items[40]; } D_801D7E00;
"""
Z="D_801D7E00.items[i].z * 1500.0f - 590.0f"
pre="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {
    s32 i; f32 depth; u8 *temp_v1;
    if (D_8004AA28 != 1) {
        temp_v1 = *arg0;
        *arg0 += 8;
        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;
        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
"""
post="    }\n}\n"
L1={
'brk_gt':f"        for (i = 0; i < 40; i++) {{ depth = {Z}; if (depth > arg2) {{ break; }} func_8001BF1C(arg0, arg1, i, depth); }}\n",
'if_le_else_brk':f"        for (i = 0; i < 40; i++) {{ depth = {Z}; if (depth <= arg2) {{ func_8001BF1C(arg0, arg1, i, depth); }} else {{ break; }} }}\n",
'brk_not_le':f"        for (i = 0; i < 40; i++) {{ depth = {Z}; if (!(depth <= arg2)) {{ break; }} func_8001BF1C(arg0, arg1, i, depth); }}\n",
'while_cond':f"        i = 0; while (i < 40 && ((depth = {Z}) <= arg2)) {{ func_8001BF1C(arg0, arg1, i, depth); i++; }}\n",
'for_cond':f"        for (i = 0; i < 40 && ((depth = {Z}) <= arg2); i++) {{ func_8001BF1C(arg0, arg1, i, depth); }}\n",
'for_cond2':f"        for (i = 0; i < 40; i++) {{ if (((depth = {Z}) <= arg2)) {{ func_8001BF1C(arg0, arg1, i, depth); }} else {{ break; }} }}\n",
}
Z2=Z
L2={
'brk_le':f"        for (i = 39; i >= 0; i--) {{ depth = {Z}; if (depth <= arg2) {{ break; }} func_8001BF1C(arg0, arg1, i, depth); }}\n",
'if_gt':f"        for (i = 39; i >= 0; i--) {{ depth = {Z}; if (arg2 < depth) {{ func_8001BF1C(arg0, arg1, i, depth); }} else {{ break; }} }}\n",
'while_cond':f"        i = 39; while (i >= 0 && (arg2 < (depth = {Z}))) {{ func_8001BF1C(arg0, arg1, i, depth); i--; }}\n",
}
cands=[]
for (k1,l1),(k2,l2) in itertools.product(L1.items(),L2.items()):
    cands.append(((k1,k2),head+pre+l1+l2+post))
out=lib.run('func_8001BDE0',[c[1] for c in cands],prefix=False)
for r,(k,x) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])[:10]: print(r,k)
for i,(k,x) in enumerate(cands): open(f'/tmp/w/r8001r_{i}.c','w').write(x)
