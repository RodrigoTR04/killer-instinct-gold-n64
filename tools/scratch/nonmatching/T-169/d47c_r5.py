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
        } else if ((D_801D3433 != 0) && (D_8004EA78 == 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
'''
# target order: andi 0x3E, andi 0xF800, sra 11, sra 1, andi 0x7C0, sra 6, addu, addu
TERMS = {
 't_bgr': '((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)',
 't_gbr': '((p & 0xF800) >> 11) + ((p & 0x3E) >> 1) + ((p & 0x7C0) >> 6)',
 't_bgr2': '((p & 0x3E) >> 1) + ((p & 0x7C0) >> 6) + ((p & 0xF800) >> 11)',
}
def make(term, idx):
    return HDR + '''
void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *src;
    u16 *dst;
    s32 i;
''' + PAL + f'''    src = var_v0;
    dst = (u16 *)0;
    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 16; i++) {{
            s32 p = src[i];
            s32 level = ({term}) / 3;
            dst[i] = (level << 11) | (level << 6) | (level << 1);
        }}
    }} else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {{
        for (i = 0; i != 16; i++) dst[i] = 0;
    }} else {{
        for (i = 0; i != 16; i++) dst[i] = src[i];
    }}
}}
'''.replace('p &', 'p &')
out = Path('tools/scratch/nonmatching/T-169/g9'); out.mkdir(exist_ok=True)
paths = []
for k, t in TERMS.items():
    p = out/f'{k}.c'; p.write_text(make(t, k)); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(3) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
