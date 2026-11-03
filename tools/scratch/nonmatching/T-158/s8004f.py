import sys, itertools, random
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
exec(open('tools/scratch/nonmatching/T-158/s8004c.py').read().split("tail=")[0].split("import lib")[1])
tail="    if (conflict != 0) { func_801C7F90(); }\n}\n"
L={
'a':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'b':"    for (;;) {\n        if (D_80292710[0][i] != 0 && D_80292710[0][i] >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'c':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && D_802926F8[0][i] <= value) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'd':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0) { if (value >= D_802926F8[0][i]) { conflict = 1; } }\n        if (++i < 34) continue;\n        break;\n    }\n",
'e':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i >= 34) break;\n    }\n",
'f':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        if (++i >= 34) break;\n    }\n",
'g':"    for (;;) {\n        value = D_80292710[0][i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) { continue; }\n        else { break; }\n    }\n",
}
cands=[]
for k,l in L.items():
  for s in seconds:
    decls="s32 conflict; s32 i; FrontendButtonMap *map; s32 slot; u8 used; u8 *cur; u8 value; u8 *q; s32 button;"
    src=pre+"void func_801C8004(void) {\n"+decls+"\n    conflict = 0; i = 0;\n"+l+seconds[s]+tail
    cands.append(((k,s),src))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in zip(out,cands): print(r,k)
