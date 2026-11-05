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
GRAY = '''    dst = (u16 *)0;
    if (D_8004EAB8 == 1) {
        for (n = 0; n != 32; n += 8) {
            s32 pixel;
            s32 l;
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(n + 0) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(n + 2) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(n + 4) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(n + 6) = (l << 11) | (l << 6) | (l << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
'''
ZERO = {
'z_ptr': '''        for (n = 0; n != 32; n += 8) {
''',
}
TAILS = {
't_ptrdst': '''    } else {
        for (n = 0; n != 32; n += 8) {
            *(u16 *)(n + 0) = *var_v0++;
            *(u16 *)(n + 2) = *var_v0++;
            *(u16 *)(n + 4) = *var_v0++;
            *(u16 *)(n + 6) = *var_v0++;
        }
    }
}
''',
}
# zero/copy via a second cursor walked in the same loop as dst
ALT = '''    dst = (u16 *)0;
    if (D_8004EAB8 == 1) {
        for (n = 0; n != 32; n += 8) {
            s32 pixel;
            s32 l;
            pixel = *var_v0++;
            l = LV0;
            *(u16 *)(n + 0) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = LV0;
            *(u16 *)(n + 2) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = LV0;
            *(u16 *)(n + 4) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = LV0;
            *(u16 *)(n + 6) = (l << 11) | (l << 6) | (l << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        src = (u16 *)0;
        while (src != (u16 *)0x20) {
            *(u16 *)((u8 *)src + 0) = 0;
            *(u16 *)((u8 *)src + 2) = 0;
            *(u16 *)((u8 *)src + 4) = 0;
            *(u16 *)((u8 *)src + 6) = 0;
            src += 4;
        }
    } else {
        src = (u16 *)0;
        while (src != (u16 *)0x20) {
            *(u16 *)((u8 *)src + 0) = *var_v0++;
            *(u16 *)((u8 *)src + 2) = *var_v0++;
            *(u16 *)((u8 *)src + 4) = *var_v0++;
            *(u16 *)((u8 *)src + 6) = *var_v0++;
            src += 4;
        }
    }
}
'''.replace('LV0', LV)
out = Path('tools/scratch/nonmatching/T-169/g7'); out.mkdir(exist_ok=True)
V = {
 'alt_a.c': HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    u16 *src;\n    u16 *dst;\n    s32 n;\n' + PAL + ALT,
}
paths = []
for k, v in V.items():
    p = out/k; p.write_text(v); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name + ' ' + str(e)[:80])
with concurrent.futures.ThreadPoolExecutor(2) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
