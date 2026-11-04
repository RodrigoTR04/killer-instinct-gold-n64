import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
decl_s="extern FrontendSettings *D_80292710[];"
decl_t="extern u8 *D_802926F8[];"
sopts={'':"extern FrontendSettings *D_80292710[];",'vptr':"extern FrontendSettings *volatile D_80292710[];",'vpointee':"extern volatile FrontendSettings *D_80292710[];",'vall':"extern volatile FrontendSettings *volatile D_80292710[];"}
topts={'':"extern u8 *D_802926F8[];",'vptr':"extern u8 *volatile D_802926F8[];",'vpointee':"extern volatile u8 *D_802926F8[];",'vall':"extern volatile u8 *volatile D_802926F8[];"}
cands=[]
for (sk,sd),(tk,td) in itertools.product(sopts.items(),topts.items()):
    cands.append(((sk,tk),base.replace(decl_s,sd).replace(decl_t,td)))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
