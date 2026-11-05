import importlib.util, concurrent.futures
from pathlib import Path
ROOT = Path(__file__).resolve().parents[4]
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec); spec.loader.exec_module(screen)
HDR = '''extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;
'''
PAL = '''    if (D_8004EA9A == 0xB) {
        var_v0 = &D_800614A0;
    } else {
        var_v0 = (u16 *)((arg0 << 5) + (u8 *)D_8004CE90);
    }
    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
'''
LV = '(((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3'
def build(gray_src, mid, tail_src):
    return HDR + '''
void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    s32 i;
''' + PAL + f'''    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 32; i += 2) {{
            s32 pixel = *{gray_src}++;
            s32 level = {LV};
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }}
''' + mid + f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    }} else {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = *{tail_src}++;
    }}
}}
'''
V = {
 # copy into a fresh pointer used only by the gray loop (target: or a0,v0,zero before the test)
 'c_pre': ('p', '    p = var_v0;\n', 'var_v0'),
 # reuse the parameter name via a local of the same shape
 'c_pp': ('p', '', 'var_v0'),
 # copy assigned inside the gray branch
 'c_in': ('p', '', 'var_v0'),
}
out = Path('tools/scratch/nonmatching/T-169/g8'); out.mkdir(exist_ok=True)
paths = []
# variant 1: p = var_v0 before the EAB8 test
txt = HDR + '''
void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *p;
    s32 i;
''' + PAL + f'''    p = var_v0;
    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 32; i += 2) {{
            s32 pixel = *p++;
            s32 level = {LV};
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }}
''' + f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    }} else {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = *p++;
    }}
}}
'''
p = out/'c_pre.c'; p.write_text(txt); paths.append(p)
# variant 2: p = var_v0 only inside the gray branch (copy appears as the or)
txt2 = HDR + '''
void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *p;
    s32 i;
''' + PAL + f'''    if (D_8004EAB8 == 1) {{
        p = var_v0;
        for (i = 0; i != 32; i += 2) {{
            s32 pixel = *p++;
            s32 level = {LV};
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }}
''' + f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    }} else {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;
    }}
}}
'''
p = out/'c_in.c'; p.write_text(txt2); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(2) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
