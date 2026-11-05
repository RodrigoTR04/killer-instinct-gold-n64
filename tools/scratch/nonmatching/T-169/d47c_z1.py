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
G = '(((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3'
HEAD = (HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    u16 *src;\n    u16 *dst;\n    s32 i;\n'
        + PAL + '    src = var_v0;\n    dst = (u16 *)0;\n    if (D_8004EAB8 == 1) {\n'
        + f'        for (i = 0; i != 16; i++) {{\n            s32 p = src[i];\n            s32 l = {G};\n'
        + '            dst[i] = (l << 11) | (l << 6) | (l << 1);\n        }\n')
# zero-fill: 4 stores per pass, order variants; also copy variants
ZERO = {
'z_asc':  '            dst[0] = 0; dst[1] = 0; dst[2] = 0; dst[3] = 0;',
'z_rot':  '            dst[1] = 0; dst[2] = 0; dst[3] = 0; dst[0] = 0;',
'z_rot2': '            dst[2] = 0; dst[3] = 0; dst[0] = 0; dst[1] = 0;',
}
def tail(zk, order):
    z = ZERO[zk]
    cp = ' '.join(f'dst[{k}] = src[{k}];' for k in order)
    return (f'''    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 16; i++) {{
{z}
        }}
    }} else {{
        for (i = 0; i != 16; i++) {{
            {cp}
        }}
    }}
}}
''')
ORD = [(0,1,2,3), (1,2,3,0), (2,3,0,1), (3,0,1,2)]
out = Path('tools/scratch/nonmatching/T-169/z1'); out.mkdir(exist_ok=True)
paths = []
for zk in ZERO:
    for order in ORD:
        p = out / f'{zk}{"".join(map(str,order))}.c'
        p.write_text(HEAD + tail(zk, order)); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:10]: print(r)
