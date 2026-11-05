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
'''
COND = {
'n_00': '        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {',
'n_01': '        } else if ((D_801D3433 != 0) && (D_8004EA78 == 0)) {',
'n_02': '        } else if (D_8004EA78 == 0 && D_801D3433) {',
'n_03': '        } else if (!D_8004EA78 && D_801D3433) {',
}
DECL = {
'd_i':   '    u16 *var_v0;\n    s32 i;\n',
'd_pp':  '    u16 *var_v0;\n    u16 *dst;\n    s32 i;\n',
'd_pi':  '    u16 *var_v0;\n    s32 i;\n    u16 *dst;\n',
}
GRAY = {
'g_idx': '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *var_v0++;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
''',
'g_dst': '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *var_v0++;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            *dst++ = (level << 11) | (level << 6) | (level << 1);
        }
''',
}
TAIL = {
't_idx': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;
    }
}
''',
't_dst': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) *dst++ = 0;
    } else {
        dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) *dst++ = *var_v0++;
    }
}
''',
}
PRE = {'p0': '', 'p1': '    dst = (u16 *)0;\n'}
out = Path('tools/scratch/nonmatching/T-169/grid'); out.mkdir(exist_ok=True)
paths = []
for ck, dk, gk, tk, pk in itertools.product(COND, DECL, GRAY, TAIL, PRE):
    if gk == 'g_idx' and pk == 'p1':
        continue
    if tk == 't_dst' and 'dst;' not in DECL[dk]:
        continue
    txt = (HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + DECL[dk] + PAL +
           '    if (D_8004AC88 == 0xC) {\n        if (D_8004EA78 == 1) {\n'
           '            var_v0 = (u16 *)0x803A3FC0;\n' + COND[ck] + '\n'
           '            var_v0 = (u16 *)0x803A3FE0;\n        }\n    }\n' +
           PRE[pk] + GRAY[gk] + TAIL[tk])
    p = out / f'{ck}{dk}{gk}{tk}{pk}.c'
    p.write_text(txt)
    paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(8) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:15]: print(r)
print('n', len(res))
