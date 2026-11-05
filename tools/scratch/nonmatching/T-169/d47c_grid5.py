#!/usr/bin/env python3
"""T-169 D47C: last 34 words -- the zero-fill loop's 4x unroll emits its stores
in the wrong rotation (target: -6,-4,-2,bne,-8). Grid zero-fill spellings."""
import concurrent.futures as cf
import importlib.util
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/d47cg4'
OUT.mkdir(exist_ok=True)

HEAD = '''extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
    u16 *var_v0;
    u16 *dst;
    s32 i;
    if (D_8004EA9A == 0xB) {
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

G = '((var_v0[i] & 0x3E) >> 1)'
R = '((var_v0[i] & 0xF800) >> 11)'
B = '((var_v0[i] & 0x7C0) >> 6)'
SUM = f'{R} + {B} + {G}'

GRAY = '''        for (i = 0; i != 16; i++) {
            s32 l = (%s) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''' % SUM

COPY = '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = var_v0[i];'

ZERO = {
    'base': '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;',
    'dstlocal': '        for (i = 0; i != 16; i++) dst[i] = 0;',
    'dstcast': '        for (i = 0; i != 16; i++) *(dst + i) = 0;',
    'ptr': '        dst = (u16 *)0;\n        for (i = 0; i != 16; i++) dst[i] = 0;',
    'u32': '        for (i = 0; i != 32; i += 2) ((u16 *)0)[i] = 0;',
    'sh8': '        for (i = 0; i != 32; i += 8) {\n'
           '            *(u16 *)i = 0;\n            *(u16 *)(i + 2) = 0;\n'
           '            *(u16 *)(i + 4) = 0;\n            *(u16 *)(i + 6) = 0;\n        }',
    'sh8b': '        for (i = 0; i != 32; i += 8) {\n'
            '            *(u16 *)(i + 2) = 0;\n            *(u16 *)(i + 4) = 0;\n'
            '            *(u16 *)(i + 6) = 0;\n            *(u16 *)i = 0;\n        }',
    'sh4': '        for (i = 0; i != 32; i += 4) {\n'
           '            *(u16 *)i = 0;\n            *(u16 *)(i + 2) = 0;\n        }',
    'dw': '        for (i = 0; i != 16; i += 2) {\n'
          '            *(u16 *)i = 0;\n            *(u16 *)(i + 2) = 0;\n        }',
    'dwp': '        for (i = 0; i != 16; i += 2) dst[i] = dst[i + 1] = 0;',
    'zero4': '        for (i = 0; i != 16; i += 4) dst[i] = dst[i + 1] = dst[i + 2] = dst[i + 3] = 0;',
    'zero8': '        for (i = 0; i != 16; i += 8) dst[i] = dst[i + 1] = dst[i + 2] = dst[i + 3] = dst[i + 4] = dst[i + 5] = dst[i + 6] = dst[i + 7] = 0;',
    'dowhile': '        for (i = 0; i != 16; i++) do { dst[i] = 0; } while (0);',
    'memset': '        for (i = 0; i != 16; i++) {\n            dst = (u16 *)0;\n            dst[i] = 0;\n        }',
}

tasks = []
for name, zero in ZERO.items():
    for head in (HEAD, HEAD.replace('    u16 *dst;\n', '')):
        tag = 'D' if 'u16 *dst;' in head else 'N'
        if tag == 'N' and 'dst' in zero:
            continue
        src = head + '    if (D_8004EAB8 == 1) {\n' + GRAY + '''
    } else if ((D_8004EA9E[arg0] == 9) && (D_8004EA78 < 2)) {
''' + zero + '''
    } else {
''' + COPY + '''
    }
}
'''
        p = OUT / f'{name}_{tag}.c'
        p.write_text(src)
        tasks.append(p)


def score(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:60])


with cf.ThreadPoolExecutor(8) as pool:
    for r in sorted(pool.map(score, tasks)):
        print(r)
