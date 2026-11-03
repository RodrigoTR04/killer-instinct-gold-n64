import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
#include "frontend.h"
"""
second="""    for (map = 0; map < 2; map++) {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            s32 button = D_80127C68[map].b[slot];
            if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
            used |= 1 << button;
        }
    }
    if (conflict != 0) { func_801C7F90(); }
}
"""
head="void func_801C8004(void) {\n    s32 conflict = 0; s32 i; s32 map; s32 slot; u8 used; u8 *cur; u8 value;\n"
loops={
'A':"    for (i = 0; i < 34; i++) { value = D_80292710[0][i]; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; }\n",
'B':"    for (i = 0; i < 34; i++) { if (D_80292710[0][i] != 0 && D_80292710[0][i] >= D_802926F8[0][i]) conflict = 1; }\n",
'C':"    cur = D_80292710[0]; for (i = 0; i < 34; i++, cur++) { value = *cur; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; }\n",
'D':"    cur = D_80292710[0]; i = 0; do { value = *cur; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; cur++; } while (++i < 34);\n",
'E':"    i = 0; do { value = D_80292710[0][i]; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; } while (++i < 34);\n",
'F':"    for (i = 0; i < 34; i++) { value = D_80292710[0][i]; if (value == 0) continue; if (value >= D_802926F8[0][i]) conflict = 1; }\n",
'G':"    i = 0; while (i < 34) { value = D_80292710[0][i]; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; i++; }\n",
'H':"    cur = D_80292710[0]; for (i = 0; i < 34; i++) { value = cur[i]; if (value != 0 && value >= D_802926F8[0][i]) conflict = 1; }\n",
'I':"    cur = D_80292710[0]; for (i = 0; i < 34; i++) { if (*cur != 0 && *cur >= D_802926F8[0][i]) conflict = 1; cur++; }\n",
'J':"    cur = D_80292710[0]; for (i = 0; i < 34; i++) { if (*cur != 0 && *cur++ >= D_802926F8[0][i]) conflict = 1; }\n",
}
cands=[(k,pre+head+l+second) for k,l in loops.items()]
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'tools/scratch/nonmatching/T-158/c/{k}.c','w').write(s)
