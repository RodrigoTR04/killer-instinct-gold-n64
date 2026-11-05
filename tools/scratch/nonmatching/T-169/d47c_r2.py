import importlib.util, itertools, concurrent.futures, random
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

LEVELS = {
 'L0': '(((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3',
 'L1': '(((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6) + ((pixel & 0x3E) >> 1)) / 3',
 'L2': '((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)',
 'L3': '(((pixel & 0x3E) / 2) + ((pixel & 0xF800) / 2048) + ((pixel & 0x7C0) / 64)) / 3',
 'L4': '(((pixel % 0x40) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3',
}
PIXT = {'P0': 's32 pixel', 'P1': 'u16 pixel', 'P2': 'int pixel'}
# gray body generator
def gray(body_pixel_type, level, srckind, itype):
    src_setup_pre = ''
    src_expr = 'var_v0'
    if srckind == 's1':
        src_setup_pre = '    src = var_v0;\n'
        src_expr = 'src'
    g = ''
    g += '    if (D_8004EAB8 == 1) {\n'
    if srckind == 's2':
        g += '        src = var_v0;\n'
    g += '        for (i = 0; i != 32; i += 2) {\n'
    g += f'            {body_pixel_type} = *{src_expr}++;\n'
    g += f'            s32 level = {level};\n'
    g += '            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);\n'
    g += '        }\n'
    g += '    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {\n'
    g += '        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;\n'
    g += '    } else {\n'
    if srckind in ('s1','s2'):
        g += '        src = var_v0;\n'
    g += f'        for (i = 0; i != 32; i += 2) *(u16 *)i = *{src_expr}++;\n'
    g += '    }\n}\n'
    return src_setup_pre + g

out = Path('tools/scratch/nonmatching/T-169/dgen2'); out.mkdir(exist_ok=True)
cands = {}
for lt, lv in LEVELS.items():
    for pt, pv in PIXT.items():
        for sk in ('s0','s1','s2'):
            for it in ('s32','u32'):
                decl = f'    u16 *var_v0;\n    {it} i;\n'
                if sk == 's1':
                    decl = f'    u16 *var_v0;\n    u16 *src;\n    {it} i;\n'
                # pixel declaration inside loop uses pv name -> need var name
                pv2 = pv.replace('pixel', 'pixel')
                body = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + decl + PAL + gray(pv2, lv, sk, it)
                n = f'{lt}_{pt}_{sk}_{it}.c'
                (out / n).write_text(body)
                cands[n] = body

def run(n):
    p = out / n
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], n)
    except Exception as e:
        return (9999, 0, n + ' ERR')
with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
    res = list(pool.map(run, sorted(cands)))
res.sort()
for r in res[:15]: print(r)
print('n=', len(res))
