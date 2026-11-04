import sys, random, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
void func_801C8004(void) {
"""
loop2="""    map = D_80127C68;
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
decl="    s32 conflict; s32 i; FrontendButtonMap *map; s32 slot; u8 used; s32 button; u8 *p; u8 value; u8 *t;\n"
bodies={
 'p_idx':"    conflict = 0; p = D_80292710[0]; i = 0;\n    for (;;) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
 'p_idx2':"    conflict = 0; p = D_80292710[0]; i = 0;\n    for (;;) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i >= 34) break;\n    }\n",
 'p_idx3':"    conflict = 0; p = D_80292710[0]; i = 0;\n    for (;;) {\n        if (p[i] != 0 && p[i] >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
 'p_idx4':"    conflict = 0; p = D_80292710[0]; i = 0;\n    for (;;) {\n        value = p[i];\n        if (value != 0) { if (value >= D_802926F8[0][i]) conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
 't_idx':"    conflict = 0; t = D_802926F8[0]; p = D_80292710[0]; i = 0;\n    for (;;) {\n        value = p[i];\n        if (value != 0 && value >= t[i]) { conflict = 1; }\n        i++;\n        if (i < 34) continue;\n        break;\n    }\n",
 'p_for':"    conflict = 0; p = D_80292710[0];\n    for (i = 0; i < 34; i++) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n    }\n",
 'p_while':"    conflict = 0; p = D_80292710[0]; i = 0;\n    while (i < 34) {\n        value = p[i];\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n        i++;\n    }\n",
}
cands=[(k,pre+decl+b+loop2) for k,b in bodies.items()]
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'/tmp/w/rb_{k}.c','w').write(s)
