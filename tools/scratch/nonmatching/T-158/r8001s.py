import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_bde_fmt.c').read()
old="""        temp_v1 = *arg0;
        *arg0 += 8;
        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;
        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
"""
assert old in base
T="*(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC)"
alts={
'base':old,
'join1':"        temp_v1 = *arg0; *arg0 += 8;\n        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;\n        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) "+T+";\n",
'join2':"        temp_v1 = *arg0;\n        *arg0 += 8;\n        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) "+T+";\n",
'join3':"        temp_v1 = *arg0; *arg0 += 8; (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000; (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) "+T+";\n",
'post':"        temp_v1 = *arg0;\n        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;\n        *arg0 += 8;\n        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) "+T+";\n",
'ptrstyle':"        u32 *cmd = (u32 *)*arg0;\n        *arg0 += 8;\n        cmd[0] = 0x06000000;\n        cmd[1] = (u32) "+T+";\n",
'incr':"        temp_v1 = *arg0;\n        *arg0 = temp_v1 + 8;\n        *(s32 *)temp_v1 = 0x06000000;\n        *(s32 *)(temp_v1 + 4) = "+T+";\n",
'incr2':"        temp_v1 = *arg0;\n        *arg0 = temp_v1 + 8;\n        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;\n        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) "+T+";\n",
'tbl':"        temp_v1 = *arg0;\n        *arg0 += 8;\n        (*(s32 *)((u8 *)(temp_v1) + 0)) = 0x06000000;\n        (*(s32 *)((u8 *)(temp_v1) + 4)) = (s32) D_8004A4C8_[arg1 * 3];\n",
}
cands=[]
for k,a in alts.items():
    s=base.replace(old,a)
    if k=='ptrstyle': s=s.replace("    u8 *temp_v1;\n","")
    if k=='tbl': s=s.replace("extern u8 D_8004A4C8;","extern s32 D_8004A4C8_[];").replace("D_8004A4C8_","D_8004A4C8")
    cands.append((k,s))
out=lib.run('func_8001BDE0',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
