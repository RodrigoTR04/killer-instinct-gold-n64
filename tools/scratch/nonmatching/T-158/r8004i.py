import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
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
decl="    s32 conflict; s32 i; FrontendButtonMap *map; s32 slot; u8 used; s32 button; u8 value; FrontendSettings *cur; u8 *lim;\n    conflict = 0; i = 0;\n"
types={
'T_u8':("extern u8 *D_802926F8[];",lambda i:f"D_802926F8[0][{i}]"),
'T_fs':("extern FrontendSettings *D_802926F8[];",lambda i:f"D_802926F8[0]->bytes[{i}]"),
'T_fsb':("extern FrontendSettings *D_802926F8[];",lambda i:f"D_802926F8[0]->fields.values[{i}]"),
'T_arr':("extern u8 (*D_802926F8[])[34];",lambda i:f"(*D_802926F8[0])[{i}]"),
}
srcs={
'S_fs':("extern FrontendSettings *D_80292710[];",lambda i:f"D_80292710[0]->bytes[{i}]"),
'S_arr':("extern u8 (*D_80292710[])[34];",lambda i:f"(*D_80292710[0])[{i}]"),
}
shapes={
'cb':"    for (;;) {{\n        value = {S};\n        if (value != 0 && value >= {T}) {{ conflict = 1; }}\n        i++;\n        if (i < 34) continue;\n        break;\n    }}\n",
'cb2':"    for (;;) {{\n        if ({S} != 0 && {S} >= {T}) {{ conflict = 1; }}\n        i++;\n        if (i < 34) continue;\n        break;\n    }}\n",
'ge':"    for (;;) {{\n        value = {S};\n        if (value != 0 && value >= {T}) {{ conflict = 1; }}\n        i++;\n        if (i >= 34) break;\n    }}\n",
}
cands=[]
for (tk,(td,tf)),(sk,(sd,sf)),(shk,sh) in itertools.product(types.items(),srcs.items(),shapes.items()):
    pre="extern void func_801C7F90();\nextern u8 D_80127C74;\n"+td+"\n"+sd+"\nvoid func_801C8004(void) {\n"
    cands.append(((tk,sk,shk),pre+decl+sh.format(S=sf('i'),T=tf('i'))+second))
out=lib.run('func_801C8004',[c[1] for c in cands],prefix=False)
for r,(k,s) in sorted(zip(out,cands),key=lambda t:(t[0] or (999,999))[1])[:12]: print(r,k)
