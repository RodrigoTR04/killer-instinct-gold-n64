import sys
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern void func_801C7F90();
extern u8 D_80127C74;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
"""
second="""    map = D_80127C68;
    do {
        used = 0;
        for (slot = 0; slot < 6; slot++) {
            s32 button = map->b[slot];
            if (button >= 8 || ((1 << button) & used)) { conflict = 2; }
            used |= 1 << button;
        }
        map++;
    } while (map != (FrontendButtonMap *)&D_80127C74);
    if (conflict != 0) { func_801C7F90(); }
}
"""
head="void func_801C8004(void) {\n    s32 conflict = 0; s32 i; FrontendButtonMap *map; s32 slot; u8 used; u8 *cur; u8 value;\n    cur = D_80292710[0]; i = 0;\n"
body="        value = *cur;\n        if (value != 0 && value >= D_802926F8[0][i]) { conflict = 1; }\n"
loops={
'1':"    for (;;) {\n"+body+"        i++; cur++;\n        if (i >= 34) break;\n    }\n",
'2':"    for (;;) {\n"+body+"        i++; cur++;\n        if (!(i < 34)) break;\n    }\n",
'3':"    for (;;) {\n"+body+"        i++; cur++;\n        if (i > 33) break;\n    }\n",
'4':"    for (;;) {\n"+body+"        i++; cur++;\n        if (i < 34) continue;\n        break;\n    }\n",
'5':"    for (;;) {\n"+body+"        cur++; i++;\n        if (i >= 34) break;\n    }\n",
'6':"    for (;;) {\n"+body+"        i = i + 1; cur = cur + 1;\n        if (i >= 34) break;\n    }\n",
'7':"    for (;;) {\n"+body+"        cur++;\n        if (++i >= 34) break;\n    }\n",
'8':"    while (1) {\n"+body+"        cur++;\n        if (++i == 34) break;\n    }\n",
'9':"    do {\n"+body+"        cur++;\n    } while (++i < 34);\n",
'a':"    for (;;) {\n"+body+"        i++; cur++;\n        if (i >= 34) goto done;\n    }\n    done:\n",
'b':"    for (; i < 34; ) {\n"+body+"        i++; cur++;\n    }\n",
'c':"  loop:\n"+body+"        i++; cur++;\n        if (i < 34) goto loop;\n",
}
cands=[(k,pre+head+l+second) for k,l in loops.items()]
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'tools/scratch/nonmatching/T-158/c/b{k}.c','w').write(s)
