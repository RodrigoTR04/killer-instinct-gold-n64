import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
v={}
v['base']=base
v['local_s']=base.replace("    u8 value;\n","    u8 value;\n    FrontendSettings *s;\n").replace("    i = 0; for (;;) {","    s = D_80292710[0];\n    i = 0; for (;;) {").replace("D_80292710[0]->bytes[i]","s->bytes[i]")
v['local_s2']=base.replace("    u8 value;\n","    u8 value;\n    FrontendSettings *s;\n").replace("    conflict = 0;\n","    conflict = 0;\n    s = D_80292710[0];\n").replace("D_80292710[0]->bytes[i]","s->bytes[i]")
v['local_u8']=base.replace("    u8 value;\n","    u8 value;\n    u8 *s;\n").replace("    i = 0; for (;;) {","    s = D_80292710[0]->bytes;\n    i = 0; for (;;) {").replace("D_80292710[0]->bytes[i]","s[i]")
v['local_t']=base.replace("    u8 value;\n","    u8 value;\n    u8 *t;\n").replace("    i = 0; for (;;) {","    t = D_802926F8[0];\n    i = 0; for (;;) {").replace("D_802926F8[0][i]","t[i]")
v['both']=v['local_s'].replace("    u8 value;\n","    u8 value;\n    u8 *t;\n").replace("    i = 0; for (;;) {","    t = D_802926F8[0];\n    i = 0; for (;;) {").replace("D_802926F8[0][i]","t[i]")
cands=list(v.items())
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
