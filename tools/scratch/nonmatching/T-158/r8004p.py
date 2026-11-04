import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern FrontendSettings *D_80292710[];
void func_801C8004(void) {
    s32 conflict;
    s32 i;
    s32 j;
    u8 used;
    s32 button;
    conflict = 0;
"""
L1={
'for':"    for (i = 0; i < 34; i++) {\n        if (D_80292710[0]->bytes[i] != 0 && D_80292710[0]->bytes[i] >= D_802926F8[0][i]) {\n            conflict = 1;\n        }\n    }\n",
'for_if':"    for (i = 0; i < 34; i++) {\n        if (D_80292710[0]->bytes[i] != 0) {\n            if (D_80292710[0]->bytes[i] >= D_802926F8[0][i]) {\n                conflict = 1;\n            }\n        }\n    }\n",
'for_cont':"    for (i = 0; i < 34; i++) {\n        if (D_80292710[0]->bytes[i] == 0) {\n            continue;\n        }\n        if (D_80292710[0]->bytes[i] >= D_802926F8[0][i]) {\n            conflict = 1;\n        }\n    }\n",
}
L2={
'idx':"    for (i = 0; i < 2; i++) {\n        used = 0;\n        for (j = 0; j < 6; j++) {\n            button = D_80127C68[i].b[j];\n            if (button >= 8 || ((1 << button) & used)) {\n                conflict = 2;\n            }\n            used |= 1 << button;\n        }\n    }\n",
}
tail="    if (conflict != 0) {\n        func_801C7F90();\n    }\n}\n"
cands=[]
for (k1,l1),(k2,l2) in itertools.product(L1.items(),L2.items()):
    cands.append(((k1,k2),pre+l1+l2+tail))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,x) in zip(out,cands): print(r,k)
