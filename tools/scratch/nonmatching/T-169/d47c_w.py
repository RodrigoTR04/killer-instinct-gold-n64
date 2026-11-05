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
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
'''
G1 = '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *var_v0++;
            s32 level = (((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
'''
T = {
't0': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;
    }
}
''',
't1': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        u16 *dst = (u16 *)0;
        for (i = 0; i != 16; i++) dst[i] = 0;
    } else {
        u16 *dst = (u16 *)0;
        for (i = 0; i != 16; i++) dst[i] = *var_v0++;
    }
}
''',
't2': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;
    } else {
        for (i = 0; i != 16; i++) ((u16 *)0)[i] = *var_v0++;
    }
}
''',
't3': '''    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i < 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i < 32; i += 2) *(u16 *)i = *var_v0++;
    }
}
''',
}
D = {'d0': '    u16 *var_v0;\n    s32 i;\n', 'd1': '    s32 i;\n    u16 *var_v0;\n', 'd2': '    u16 *var_v0;\n    s32 i;\n    u16 *dst;\n'}
out = Path('tools/scratch/nonmatching/T-169/dw'); out.mkdir(exist_ok=True)
paths=[]
for tk, tv in T.items():
    for dk, dv in D.items():
        txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + dv + PAL + G1 + tv
        p = out/f'{tk}{dk}.c'; p.write_text(txt); paths.append(p)
def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception:
        return (9999, 0, p.name)
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    for r in sorted(pool.map(run, paths)): print(r)
