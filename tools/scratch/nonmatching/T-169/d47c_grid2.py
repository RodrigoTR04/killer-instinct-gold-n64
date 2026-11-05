#!/usr/bin/env python3
"""T-169 D47C register-allocation grid: vary how the three loops spell their
cursors, measure official words."""
import concurrent.futures as cf
import importlib.util
import itertools
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)

OUT = ROOT / 'tools/scratch/nonmatching/T-169/d47cg'
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
    u16 *src;
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

GRAY = {
    'src': '''        for (i = 0; i != 16; i++) {
            s32 p = src[i];
            s32 l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            dst[i] = (l << 11) | (l << 6) | (l << 1);
        }''',
    'v0': '''        for (i = 0; i != 16; i++) {
            s32 p = var_v0[i];
            s32 l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''',
    'v0flat': '''        for (i = 0; i != 16; i++) {
            s32 l = (((var_v0[i] & 0x3E) >> 1) + ((var_v0[i] & 0xF800) >> 11) + ((var_v0[i] & 0x7C0) >> 6)) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''',
    'pp': '''        for (i = 0; i != 16; i++) {
            s32 p = src[i];
            s32 l = ((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6);
            l /= 3;
            dst[i] = (l << 11) | (l << 6) | (l << 1);
        }''',
    'srcnull': '''        for (i = 0; i != 16; i++) {
            s32 p = src[i];
            s32 l = (((p & 0x3E) >> 1) + ((p & 0xF800) >> 11) + ((p & 0x7C0) >> 6)) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''',
}

ZERO = {
    'i32': '        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;',
    'i16': '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;',
    'dst': '        for (i = 0; i != 16; i++) dst[i] = 0;',
    'src': '        for (i = 0; i != 16; i++) src[i] = 0;',
}

COPY = {
    'sd': '        for (i = 0; i != 16; i++) dst[i] = src[i];',
    'vs': '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = var_v0[i];',
    'vd': '        for (i = 0; i != 16; i++) dst[i] = var_v0[i];',
    'sv': '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = src[i];',
}

PREAMBLE = {
    'assign': '    src = var_v0;\n    dst = (u16 *)0;\n',
    'none': '',
}


def build(g, z, c, pre):
    return HEAD + PREAMBLE[pre] + '''    if (D_8004EAB8 == 1) {
''' + GRAY[g] + '''
    } else if ((D_8004EA9E[arg0] == 9) && (D_8004EA78 < 2)) {
''' + ZERO[z] + '''
    } else {
''' + COPY[c] + '''
    }
}
'''


tasks = []
for g, z, c, pre in itertools.product(GRAY, ZERO, COPY, PREAMBLE):
    if pre == 'none' and ('src' in GRAY[g] or 'src' in ZERO[z] or 'src' in COPY[c]):
        continue
    name = f'{g}_{z}_{c}_{pre}.c'
    p = OUT / name
    p.write_text(build(g, z, c, pre))
    tasks.append(p)


def score(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:80])


with cf.ThreadPoolExecutor(8) as pool:
    for r in sorted(pool.map(score, tasks))[:20]:
        print(r)
