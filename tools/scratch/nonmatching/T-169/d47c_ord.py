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
DECLS = [
 '    u16 *var_v0;\n    u16 *src;\n    u16 *dst;\n    s32 i;\n',
 '    u16 *var_v0;\n    u16 *dst;\n    u16 *src;\n    s32 i;\n',
 '    u16 *var_v0;\n    u16 *src;\n    s32 i;\n',   # no dst: indexed dest
]
ASSN = {
'a_sd': '    src = var_v0;\n    dst = (u16 *)0;\n',
'a_ds': '    dst = (u16 *)0;\n    src = var_v0;\n',
'a_s':  '    src = var_v0;\n',
'a_n':  '',
}
def gray(use_dst, srcname):
    d = '*dst++' if use_dst else '*(u16 *)i'
    return f'''    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 32; i += 2) {{
            s32 pixel = *{srcname}++;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            {d} = (level << 11) | (level << 6) | (level << 1);
        }}
'''
def tail(use_dst, srcname):
    if use_dst:
        return f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) *dst++ = 0;
    }} else {{
        dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) *dst++ = *{srcname}++;
    }}
}}
'''
    return f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    }} else {{
        for (i = 0; i != 32; i += 2) *(u16 *)i = *{srcname}++;
    }}
}}
'''
out = Path('tools/scratch/nonmatching/T-169/ord'); out.mkdir(exist_ok=True)
paths = []
for di, decl in enumerate(DECLS):
    use_dst = 'dst;' in decl
    for ak, av in ASSN.items():
        if not use_dst and ak in ('a_sd', 'a_ds'):
            continue
        if use_dst and ak == 'a_s':
            continue
        for srcname in ('src', 'var_v0'):
            if srcname == 'src' and 'src;' not in decl:
                continue
            txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + decl + PAL + av + gray(use_dst, srcname) + tail(use_dst, srcname)
            p = out / f'd{di}{ak}s{srcname[0]}.c'
            p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:12]: print(r)
