import importlib.util, concurrent.futures, itertools
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
LV = '(((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3'

# dest cursor declared as u16* starting at 0, bound as pointer
GRAY = '''    if (D_8004EAB8 == 1) {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            s32 pixel;
            s32 l;
            pixel = *var_v0++;
            l = ''' + LV + ''';
            dst[0] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            dst[1] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            dst[2] = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            dst[3] = (l << 11) | (l << 6) | (l << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
            dst[3] = 0;
        }
    } else {
        for (dst = (u16 *)0; dst != (u16 *)0x20; dst += 4) {
            dst[0] = *var_v0++;
            dst[1] = *var_v0++;
            dst[2] = *var_v0++;
            dst[3] = *var_v0++;
        }
    }
}
'''
V = {
 'pc0': '    u16 *var_v0;\n    u16 *dst;\n    s32 i;\n',
 'pc1': '    u16 *var_v0;\n    s32 i;\n    u16 *dst;\n',
}
out = Path('tools/scratch/nonmatching/T-169/g6'); out.mkdir(exist_ok=True)
paths = []
for k, d in V.items():
    p = out/f'{k}.c'
    p.write_text(HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + d + PAL + GRAY)
    paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(2) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
