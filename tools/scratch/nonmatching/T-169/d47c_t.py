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
PIX = {'p_s32': 's32 pixel = *var_v0++;', 'p_u16': 'u16 pixel = *var_v0++;', 'p_s16': 's16 pixel = *var_v0++;'}
LVL = {
 'l_s32': 's32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;',
 'l_u16': 'u16 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;',
 'l_d3': 's32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) >> 1;',
}
DST = {'d_i': '*(u16 *)i', 'd_p': '*(u16 *)((u8 *)0 + i)'}
TAIL = {
 't0': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;
    }
}
''',
}
out = Path('tools/scratch/nonmatching/T-169/dt'); out.mkdir(exist_ok=True)
paths=[]
for pk, lk, dk, tk in itertools.product(PIX, LVL, DST, TAIL):
    gray = f'''    if (D_8004EAB8 == 1) {{
        for (i = 0; i != 32; i += 2) {{
            {PIX[pk]}
            {LVL[lk]}
            {DST[dk]} = (level << 11) | (level << 6) | (level << 1);
        }}
''' + TAIL[tk]
    txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n    u16 *var_v0;\n    s32 i;\n' + PAL + gray
    p = out/f'{pk}{lk}{dk}{tk}.c'; p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
