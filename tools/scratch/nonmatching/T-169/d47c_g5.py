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
        } else if ((D_801D3433 != 0) && (D_8004EA78 == 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
'''
LV = '(((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3'
TAILT = '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 8) {
            *(u16 *)(i + 0) = 0;
            *(u16 *)(i + 2) = 0;
            *(u16 *)(i + 4) = 0;
            *(u16 *)(i + 6) = 0;
        }
    } else {
        for (i = 0; i != 32; i += 8) {
            *(u16 *)(i + 0) = *var_v0++;
            *(u16 *)(i + 2) = *var_v0++;
            *(u16 *)(i + 4) = *var_v0++;
            *(u16 *)(i + 6) = *var_v0++;
        }
    }
}
'''
def body(loadpos):
    # four copies; each copy stores to i+N; pixel reloaded at end of copy when loadpos=='end'
    parts = []
    for n, off in enumerate((0, 2, 4, 6)):
        s = f'''            l = {LV};
            *(u16 *)(i + {off}) = (l << 11) | (l << 6) | (l << 1);
'''
        if loadpos == 'end':
            s += '            pixel = *var_v0++;\n'
        parts.append(s)
    return ''.join(parts)
V = {
'h_lead': '''    if (D_8004EAB8 == 1) {
        s32 pixel;
        s32 l;
        pixel = *var_v0++;
        for (i = 0; i != 32; i += 8) {
''' + body('end') + '''        }
''' + TAILT,
'h_dup': '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 8) {
            s32 pixel = *var_v0++;
            s32 l;
            l = ''' + LV + ''';
            *(u16 *)(i + 0) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(i + 2) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(i + 4) = (l << 11) | (l << 6) | (l << 1);
            pixel = *var_v0++;
            l = ''' + LV + ''';
            *(u16 *)(i + 6) = (l << 11) | (l << 6) | (l << 1);
        }
''' + TAILT,
}
out = Path('tools/scratch/nonmatching/T-169/g5'); out.mkdir(exist_ok=True)
paths = []
for k, v in V.items():
    p = out/f'{k}.c'
    p.write_text(HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    s32 i;\n' + PAL + v)
    paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(2) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
