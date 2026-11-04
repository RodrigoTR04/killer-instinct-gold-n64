import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
exec(open('tools/scratch/nonmatching/T-158/r8004b.py').read().split("decl=")[0].split("import lib")[1])
cands=[]
for it in ('u8','s8','u16','s16','u32','s32'):
  for vt in ('u8','s32'):
    for shape in ('for','while','do','forp','forp2'):
      decl=f"    s32 conflict; {it} i; FrontendButtonMap *map; s32 slot; u8 used; s32 button; u8 *p; {vt} value;\n"
      if shape=='for': b="    conflict = 0; p = D_80292710[0];\n    for (i = 0; i < 34; i++) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n    }\n"
      if shape=='while': b="    conflict = 0; p = D_80292710[0]; i = 0;\n    while (i < 34) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n    }\n"
      if shape=='do': b="    conflict = 0; p = D_80292710[0]; i = 0;\n    do {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n    } while (i < 34);\n"
      if shape=='forp': b="    conflict = 0; p = D_80292710[0];\n    for (i = 0; i < 34; i++, p++) {\n        value = *p;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n    }\n"
      if shape=='forp2': b="    conflict = 0; p = D_80292710[0];\n    for (i = 0; i < 34; i++) {\n        value = *p++;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n    }\n"
      cands.append(((it,vt,shape),pre+decl+b+loop2))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
res=sorted(zip(out,cands),key=lambda t:((t[0] or (999,999))[1],(t[0] or (999,999))[0]))
for r,(k,s) in res[:12]: print(r,k)
