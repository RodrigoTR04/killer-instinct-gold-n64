import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
base=open('tools/scratch/nonmatching/T-158/w_8004_join.c').read()
start=base.index("    i = 0; for (;;) {")
end=base.index("    map = D_80127C68;")
loop1=base[start:end]
def wrap(kind, body):
    return {'none':body,'dw0':"    do {\n"+body+"    } while (0);\n",'for1':"    for (;;) {\n"+body+"        break;\n    }\n",'while1':"    while (1) {\n"+body+"        break;\n    }\n"}[kind]
cands=[]
for kind in ('none','dw0','for1','while1'):
    cands.append((kind,base[:start]+wrap(kind,loop1)+base[end:]))
# also loop 2 wrapped
for kind in ('dw0',):
    l2start=end
    l2=base[end:base.index("    if (conflict != 0)")]
    cands.append(('l2dw0',base[:start]+loop1+wrap(kind,l2)+base[base.index("    if (conflict != 0)"):]))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
for k,x in cands: open(f'/tmp/w/r8004k_{k}.c','w').write(x)
