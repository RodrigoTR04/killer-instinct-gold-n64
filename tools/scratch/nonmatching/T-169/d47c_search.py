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

CND = {
'a':'''    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if ((D_8004EA78 == 0) && (D_801D3433 != 0)) {
            var_v0 = (u16 *)0x803A3FE0;
        }
    }
''',
'b':'''    if (D_8004AC88 == 0xC) {
        if (D_8004EA78 == 1) {
            var_v0 = (u16 *)0x803A3FC0;
        } else if (D_8004EA78 == 0) {
            if (D_801D3433 != 0) {
                var_v0 = (u16 *)0x803A3FE0;
            }
        }
    }
''',
}

# loop body variants; %SRC% is the source expression name, %I% the counter
LEVEL = {
'l0': '(pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6',
'l1': '(pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6) + ((pixel & 0x3E) >> 1',
}
DCL = {
'd0': '    u16 *var_v0;\n    u16 *src;\n    s32 i;\n',
'd1': '    u16 *var_v0;\n    s32 i;\n    u16 *src;\n',
'd2': '    s32 i;\n    u16 *var_v0;\n    u16 *src;\n',
'd3': '    u16 *var_v0;\n    s32 i;\n',
'd4': '    s32 i;\n    u16 *var_v0;\n',
'd5': '    u16 *src;\n    u16 *var_v0;\n    s32 i;\n',
}
SRCC = {
's0': 'src = var_v0;\n',
's1': '',
}
GRAY = {
'g0':'    if (D_8004EAB8 == 1) {\n        for (i = 0; i != 32; i += 2) {\n            s32 pixel = *%S%++;\n            s32 level = ((%L%)) / 3;\n            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);\n        }\n    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {\n        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;\n    } else {\n        for (i = 0; i != 32; i += 2) *(u16 *)i = *%S%++;\n    }\n}\n',
'g1':'    if (D_8004EAB8 == 1) {\n        %S% = var_v0;\n        for (i = 0; i != 32; i += 2) {\n            s32 pixel = *%S%++;\n            s32 level = ((%L%)) / 3;\n            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);\n        }\n    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {\n        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;\n    } else {\n        %S% = var_v0;\n        for (i = 0; i != 32; i += 2) *(u16 *)i = *%S%++;\n    }\n}\n',
'g2':'    if (D_8004EAB8 == 1) {\n        %S% = var_v0;\n        for (i = 0; i != 32; i += 2) {\n            s32 pixel = *%S%++;\n            s32 level = ((%L%)) / 3;\n            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);\n        }\n    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {\n        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;\n    } else {\n        for (i = 0; i != 32; i += 2) *(u16 *)i = *var_v0++;\n    }\n}\n',
}

out = Path('tools/scratch/nonmatching/T-169/dgen'); out.mkdir(exist_ok=True)
items = []
for ck, dk, lk, gk in itertools.product(CND, DCL, LEVEL, GRAY):
    dcl = DCL[dk]
    srcname = 'src' if 'src' in dcl else 'var_v0'
    if gk == 'g0' and srcname == 'src':
        pass
    g = GRAY[gk].replace('%S%', srcname).replace('%L%', LEVEL[lk])
    body = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + dcl + PAL + CND[ck] + g
    if gk != 'g0' and srcname == 'var_v0':
        continue
    n = f'{ck}{dk}{lk}{gk}.c'
    p = out / n
    p.write_text(body)
    items.append(p)

def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name + ' ERR')
with concurrent.futures.ThreadPoolExecutor(max_workers=6) as pool:
    res = list(pool.map(run, items))
res.sort()
for r in res[:20]: print(r)
print('n=', len(res))
