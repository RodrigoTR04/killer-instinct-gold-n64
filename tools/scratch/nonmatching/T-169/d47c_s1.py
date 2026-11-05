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
def gray(order):
    lines = []
    for k in order:
        lines.append(f'            p = src[{k}];')
        lines.append(f'            l = {G};')
        lines.append(f'            dst[{k}] = (l << 11) | (l << 6) | (l << 1);')
    return '\n'.join(lines)
V = {}
for order in ((0,1,2,3), (1,2,3,0)):
    tag = ''.join(map(str, order))
    V['o'+tag] = '''    src = var_v0;
    dst = (u16 *)0;
    de = dst + 16;
    if (D_8004EAB8 == 1) {
        s32 p;
        s32 l;
        while (dst != de) {
''' + gray(order) + '''
            src += 4;
            dst += 4;
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        dst = (u16 *)0;
        de = dst + 16;
        while (dst != de) {
''' + '\n'.join(f'            dst[{k}] = 0;' for k in order) + '''
            dst += 4;
        }
    } else {
        src = var_v0;
        dst = (u16 *)0;
        de = dst + 16;
        while (dst != de) {
''' + '\n'.join(f'            dst[{k}] = src[{k}];' for k in order) + '''
            src += 4;
            dst += 4;
        }
    }
}
'''
out = Path('tools/scratch/nonmatching/T-169/s1'); out.mkdir(exist_ok=True)
paths = []
for k, v in V.items():
    p = out/f'{k}.c'
    p.write_text(HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    u16 *src;\n    u16 *dst;\n    u16 *de;\n' + PAL + v)
    paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(2) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
