import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern FrontendSettings *D_80292710[];
void func_801C8004(void) {
"""
loops={
'idx_cb':"    for (;;) {\n        if (S[i] != 0 && S[i] >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'idx_val':"    for (;;) {\n        value = S[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
'for':"    for (i = 0; i < 34; i++) {\n        if (S[i] != 0 && S[i] >= D_802926F8[0][i]) { conflict = 1; }\n    }\n",
'for_val':"    for (i = 0; i < 34; i++) {\n        value = S[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n    }\n",
'ge':"    for (;;) {\n        if (S[i] != 0 && S[i] >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i >= 34) break;\n    }\n",
}
second="""    map = D_80127C68;
    do {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            button = map->b[slot];
            if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
            used |= 1 << button;
        }
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
    if (conflict != 0) { func_801C7F90(); }
}
"""
decl="    s32 conflict; s32 i; FrontendButtonMap *map; s32 slot; u8 used; s32 button; u8 value;\n    conflict = 0; i = 0;\n"
cands=[]
for k,l in loops.items():
    for S in ('D_80292710[0]->bytes','D_80292710[0]->fields.values'):
        if 'values' in S and False: continue
        cands.append(((k,S),pre+decl+l.replace('S[',S+'[')+second))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1]): print(r,k)
for i,(k,s) in enumerate(cands): open(f'/tmp/w/r8004h_{i}.c','w').write(s)
