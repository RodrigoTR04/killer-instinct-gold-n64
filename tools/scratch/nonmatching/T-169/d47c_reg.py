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
 ['u16 *var_v0;', 'u16 *src;', 'u16 *dst;', 's32 i;'],
 ['u16 *var_v0;', 'u16 *dst;', 'u16 *src;', 's32 i;'],
 ['u16 *src;', 'u16 *dst;', 'u16 *var_v0;', 's32 i;'],
 ['u16 *dst;', 'u16 *src;', 'u16 *var_v0;', 's32 i;'],
 ['u16 *var_v0;', 'u16 *dst;', 's32 i;'],
 ['u16 *var_v0;', 's32 i;', 'u16 *dst;'],
 ['u16 *var_v0;', 's32 i;'],
]
ASSN = ['    src = var_v0;\n    dst = (u16 *)0;\n',
        '    dst = (u16 *)0;\n    src = var_v0;\n',
        '    dst = (u16 *)0;\n',
        '']
G = '(((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3'
def body(use_dst, srcname):
    g = f'''    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 16; i++) {{
            s32 p = {srcname}[i];
            s32 l = {G};
            {'dst[i]' if use_dst else '((u16 *)0)[i]'} = (l << 11) | (l << 6) | (l << 1);
        }}
    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 16; i++) {'dst[i]' if use_dst else '((u16 *)0)[i]'} = 0;
    }} else {{
        for (i = 0; i != 16; i++) {'dst[i]' if use_dst else '((u16 *)0)[i]'} = {srcname}[i];
    }}
}}
'''
    return g
out = Path('tools/scratch/nonmatching/T-169/reg'); out.mkdir(exist_ok=True)
paths = []
for di, d in enumerate(DECLS):
    use_dst = any('dst;' in x for x in d)
    for ai, a in enumerate(ASSN):
        if not use_dst and ai != 3:
            continue
        for srcname in ('src', 'var_v0'):
            if srcname == 'src' and not any('src;' in x for x in d):
                continue
            txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + ''.join('    ' + x + '\n' for x in d) + PAL + a + body(use_dst, srcname)
            p = out / f'd{di}a{ai}s{srcname[0]}.c'
            p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:14]: print(r)
