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
G = {
'g_std': '(((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3',
'g_16':  '(((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3',
}
LEN = {'n16': 'i = 0; i != 16; i++', 'n32': 'i = 0; i != 32; i += 2', 'n16s': 'i = 0; i < 16; i++'}
DST = {'d_idx': 'dst[i]', 'd_u16': '((u16 *)0)[i]'}
TAILS = {
't_sep': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 16; i++) %D% = 0;
    } else {
        for (i = 0; i != 16; i++) %D% = src[i];
    }
}
''',
't_sep2': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i < 16; i++) %D% = 0;
    } else {
        for (i = 0; i < 16; i++) %D% = src[i];
    }
}
''',
}
out = Path('tools/scratch/nonmatching/T-169/reg2'); out.mkdir(exist_ok=True)
paths = []
for lk, lv in LEN.items():
    for dk, dv in DST.items():
        for tk, tv in TAILS.items():
            body = f'''    if (D_8004EAB8 == 1) {{
        for ({lv}) {{
            s32 p = src[i];
            s32 l = {G['g_std']};
            {dv} = (l << 11) | (l << 6) | (l << 1);
        }}
''' + tv.replace('%D%', dv)
            txt = (HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    u16 *src;\n    u16 *dst;\n    s32 i;\n'
                   + PAL + '    src = var_v0;\n    dst = (u16 *)0;\n' + body)
            p = out / f'{lk}{dk}{tk}.c'
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
