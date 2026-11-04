import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
v={'base':base}
v['c1']=base.replace("extern FrontendSettings *D_80292710[];","extern FrontendSettings *const D_80292710[];")
v['c2']=base.replace("extern u8 *D_802926F8[];","extern u8 *const D_802926F8[];")
v['c12']=v['c1'].replace("extern u8 *D_802926F8[];","extern u8 *const D_802926F8[];")
v['cc']=base.replace("extern FrontendSettings *D_80292710[];","extern const FrontendSettings *D_80292710[];")
v['vol']=base.replace("extern u8 *D_802926F8[];","extern u8 *volatile D_802926F8[];")
v['vol2']=base.replace("extern FrontendSettings *D_80292710[];","extern FrontendSettings *volatile D_80292710[];")
cands=list(v.items())
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
