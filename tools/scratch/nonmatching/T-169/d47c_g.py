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
LV = {
 'a': '(((pixel & 0x3E) >> 1) + ((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6)) / 3',
 'b': '(((pixel & 0xF800) >> 11) + ((pixel & 0x7C0) >> 6) + ((pixel & 0x3E) >> 1)) / 3',
 'c': '(((pixel & 0x3E) >> 1) + ((pixel & 0x7C0) >> 6) + ((pixel & 0xF800) >> 11)) / 3',
}
GRAY = {
 'g0': '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *src++;
            s32 level = %L%;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *src++;
    }
}
''',
 'g1': '''    if (D_8004EAB8 == 1) {
        u16 *dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) {
            s32 pixel = *src++;
            s32 level = %L%;
            *dst++ = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *src++;
    }
}
''',
 'g2': '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 32; i += 2) {
            s32 level = %L2%;
            *(u16 *)i = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *src++;
    }
}
''',
 'g3': '''    if (D_8004EAB8 == 1) {
        u16 *dst = (u16 *)0;
        for (i = 0; i != 32; i += 2) {
            s32 level = %L2%;
            *dst++ = (level << 11) | (level << 6) | (level << 1);
        }
    } else if (D_8004EA9E[arg0] == 9 && D_8004EA78 < 2) {
        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;
    } else {
        for (i = 0; i != 32; i += 2) *(u16 *)i = *src++;
    }
}
''',
}
DCL = {
 'd0': '    u16 *var_v0;\n    u16 *src;\n    s32 i;\n',
 'd1': '    u16 *var_v0;\n    s32 i;\n    u16 *src;\n',
 'd2': '    u16 *var_v0;\n    u16 *src;\n    s32 i;\n    u16 *dst;\n',
}
SRCSET = {'s0': '        src = var_v0;\n', 's1': ''}
out = Path('tools/scratch/nonmatching/T-169/dgen3'); out.mkdir(exist_ok=True)
paths = []
for lk, gk, dk in itertools.product(LV, GRAY, DCL):
    if gk in ('g0','g1') and 'src' not in DCL[dk]: continue
    body = GRAY[gk].replace('%L%', LV[lk]).replace('%L2%', '*src++')
    if '%L2%' in body or gk in ('g0','g1'):
        body = body.replace('%L2%', LV[lk])
    dcl = DCL[dk]
    if 'dst' in body and 'dst;' not in dcl:
        dcl = dcl + '    u16 *dst;\n'
    if gk in ('g0','g1'):
        pre = '        src = var_v0;\n'
    src_ = body.replace('*src++', '*var_v0++').replace('src = var_v0;', '') if gk in ('g2','g3') else body
    if gk in ('g2','g3'):
        dcl = dcl.replace('    u16 *src;\n', '')
    txt = HDR + '\nvoid func_8001D47C(u8 arg0) {\n' + dcl + PAL + src_
    n = f'{lk}{gk}{dk}.c'
    p = out / n; p.write_text(txt); paths.append(p)

def run(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (9999, 0, p.name+' ERR')
with concurrent.futures.ThreadPoolExecutor(6) as pool:
    res = sorted(pool.map(run, paths))
for r in res[:12]: print(r)
