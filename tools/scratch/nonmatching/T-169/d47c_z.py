import importlib.util, itertools, concurrent.futures
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
ORDER = {
 'o0': '    entry = &D_8004EA9E[arg0];\n    p = var_v0;\n',
 'o1': '    p = var_v0;\n    entry = &D_8004EA9E[arg0];\n',
 'o2': '    entry = &D_8004EA9E[arg0];\n',
 'o3': '    p = var_v0;\n',
}
COND = {'c0': '*entry == 9', 'c1': 'D_8004EA9E[arg0] == 9'}
DCL = {'d0': '    u16 *var_v0;\n    u16 *p;\n    u8 *entry;\n    s32 i;\n',
       'd1': '    u16 *var_v0;\n    u8 *entry;\n    u16 *p;\n    s32 i;\n'}
def gray(src):
    return f'''    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 32; i += 2) {{
            s32 pixel = *{src}++;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }}
'''
def tail(src, cond):
    return f'''    }} else if ({cond} && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    }} else {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = *{src}++;
    }}
}}
'''
out = Path('tools/scratch/nonmatching/T-169/dz'); out.mkdir(exist_ok=True)
paths = []
for ok, ov in ORDER.items():
    for ck, cv in COND.items():
        for dk, dv in DCL.items():
            use_p = 'p' in ov
            src = 'p' if use_p else 'var_v0'
            txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + dv + PAL + ov + gray(src) + tail(src, cv)
            p = out/f'{ok}{ck}{dk}.c'; p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
