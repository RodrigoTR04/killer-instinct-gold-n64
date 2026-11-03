import sys, itertools
sys.path.insert(0,'.')
import lib
b = open('../T-023/func_801BAA78.c').read()
Y0 = "y0 = arg3 + ((s32)(arg4->scale * 0xB4) >> 0xA) + yOffsetScaled;"
Y1 = "y1 = (arg2 * 4) + ((s32)(arg4->scale * 0x350) >> 0xA) + (arg4->yOffset * 4);"
X0 = "x0 = (arg1 * 4) + ((s32)(((arg5 * 0x16) + 0x165) * arg4->scale) >> 0xA);"
X1 = "x1 = (arg1 * 4) + ((s32)(((arg5 * 0x13) + 0x71) * arg4->scale) >> 0xA);"
for s in (Y0,Y1,X0,X1): assert s in b
y0t = ["arg3", "((s32)(arg4->scale * 0xB4) >> 0xA)", "yOffsetScaled"]
y1t = ["(arg2 * 4)", "((s32)(arg4->scale * 0x350) >> 0xA)", "(arg4->yOffset * 4)"]
x0t = ["(arg1 * 4)", "((s32)(((arg5 * 0x16) + 0x165) * arg4->scale) >> 0xA)"]
x1t = ["(arg1 * 4)", "((s32)(((arg5 * 0x13) + 0x71) * arg4->scale) >> 0xA)"]
cands=[]
for p0 in itertools.permutations(range(3)):
  for p1 in itertools.permutations(range(3)):
    for q0 in itertools.permutations(range(2)):
      for q1 in itertools.permutations(range(2)):
        s=b.replace(Y0,"y0 = "+" + ".join(y0t[i] for i in p0)+";").replace(Y1,"y1 = "+" + ".join(y1t[i] for i in p1)+";").replace(X0,"x0 = "+" + ".join(x0t[i] for i in q0)+";").replace(X1,"x1 = "+" + ".join(x1t[i] for i in q1)+";")
        cands.append(((p0,p1,q0,q1),s))
res=lib.run('func_801BAA78',[s for _,s in cands],prefix=False)
rows=sorted([(r,c) for (c,_),r in zip(cands,res) if r],key=lambda t:(t[0][1],t[0][0]))
for r,c in rows[:6]: print(r,c)
