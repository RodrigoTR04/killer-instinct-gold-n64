import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
v={'base':base}
# explicit cursor var with hacks
b2=base.replace("    u8 value;\n","    u8 value;\n    FrontendSettings *s;\n").replace("    i = 0; for (;;) {","    s = D_80292710[0];\n    i = 0; for (;;) {").replace("D_80292710[0]->bytes[i]","s->bytes[i]")
v['s']=b2
v['s_cond']=b2.replace("        i++;\n","        i++;\n        if (conflict > 1) { s = D_80292710[0]; }\n",1)
v['s_cond2']=b2.replace("    s = D_80292710[0];\n","    s = D_80292710[0];\n    if (conflict > 1) { s = D_80292710[0]; }\n")
v['s_twice']=b2.replace("        if (value != 0 && value >= D_802926F8[0][i]) {","        if (value != 0 && value >= D_802926F8[0][i] && s->bytes[i] >= D_802926F8[0][i]) {")
cands=list(v.items())
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
