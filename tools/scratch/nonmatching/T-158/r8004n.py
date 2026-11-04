import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
v={'base':base}
for n in ('[6]','[8]','[1]'):
    v['sz'+n]=base.replace("D_80292710[];","D_80292710"+n+";").replace("D_802926F8[];","D_802926F8"+n+";")
v['ptrs']=base.replace("extern FrontendSettings *D_80292710[];","extern FrontendSettings *D_80292710;").replace("D_80292710[0]->","D_80292710->")
v['ptrs2']=base.replace("extern u8 *D_802926F8[];","extern u8 *D_802926F8;").replace("D_802926F8[0][i]","D_802926F8[i]")
v['ptrs3']=v['ptrs'].replace("extern u8 *D_802926F8[];","extern u8 *D_802926F8;").replace("D_802926F8[0][i]","D_802926F8[i]")
v['fs_tab']=base.replace("extern u8 *D_802926F8[];","extern FrontendSettings *D_802926F8[];").replace("D_802926F8[0][i]","D_802926F8[0]->bytes[i]")
cands=list(v.items())
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
