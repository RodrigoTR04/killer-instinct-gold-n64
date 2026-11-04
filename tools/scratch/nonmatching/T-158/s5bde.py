import sys, itertools
sys.path.insert(0,'tools/scratch/nonmatching/T-155')
import lib
pre="""extern u8 D_8004AA28;
void func_8001BF1C(u8 **, s32, s32, f32);
extern u8 D_8004A4C8;

typedef struct { u8 pad[0x30]; } Rec;

extern u8 D_801D7E00;
"""
hdr="""void func_8001BDE0(u8 **arg0, s32 arg1, f32 arg2) {
    s32 i; f32 depth; u8 *cmd;
    if (D_8004AA28 == 1) return;
    cmd = *arg0; *arg0 += 8;
    *(s32 *)cmd = 0x06000000; *(s32 *)(cmd + 4) = *(s32 *)((u8 *)&D_8004A4C8 + arg1 * 0xC);
"""
def Z(i): return f"(*(f32 *)(&D_801D7E00 + 0xF0 + (i) * 0x30))"
forms={
'f1':hdr+f"""    for (i = 0; i < 40; i++) {{
        depth = {Z('i')} * 1500.0f - 590.0f;
        if (depth > arg2) break;
        func_8001BF1C(arg0, arg1, i, depth);
    }}
    for (i = 39; i >= 0; i--) {{
        depth = {Z('i')} * 1500.0f - 590.0f;
        if (!(arg2 < depth)) break;
        func_8001BF1C(arg0, arg1, i, depth);
    }}
}}
""",
'f2':hdr+f"""    for (i = 0; i < 40; i++) {{
        depth = {Z('i')} * 1500.0f - 590.0f;
        if (!(depth <= arg2)) break;
        func_8001BF1C(arg0, arg1, i, depth);
    }}
    for (i = 39; i >= 0; i--) {{
        depth = {Z('i')} * 1500.0f - 590.0f;
        if (!(arg2 < depth)) break;
        func_8001BF1C(arg0, arg1, i, depth);
    }}
}}
""",
'f3':hdr+f"""    i = 0;
    while (i < 40 && ({Z('i')} * 1500.0f - 590.0f) <= arg2) {{
        func_8001BF1C(arg0, arg1, i, {Z('i')} * 1500.0f - 590.0f);
        i++;
    }}
    i = 39;
    while (i >= 0 && arg2 < ({Z('i')} * 1500.0f - 590.0f)) {{
        func_8001BF1C(arg0, arg1, i, {Z('i')} * 1500.0f - 590.0f);
        i--;
    }}
}}
""",
}
cands=list(forms.items())
out=lib.run('func_8001BDE0',[pre+c[1] for c in cands])
for r,(k,s) in zip(out,cands): print(r,k)
for k,s in cands: open(f'tools/scratch/nonmatching/T-158/b/{k}.c','w').write(pre+s)
