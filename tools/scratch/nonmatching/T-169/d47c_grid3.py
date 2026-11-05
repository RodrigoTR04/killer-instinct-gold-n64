#!/usr/bin/env python3
"""T-169 D47C: term-order and zero-fill shape grid from the 49-word base."""
import concurrent.futures as cf
import importlib.util
import itertools
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/d47cg2'
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
TERMS = {'G': G, 'R': R, 'B': B}
ORDERS = list(itertools.permutations('GRB'))

GRAY = {}
for o in ORDERS:
    key = ''.join(o)
    GRAY[key] = ('''        for (i = 0; i != 16; i++) {
            s32 l = %s / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''' % ' + '.join(TERMS[c] for c in o))
    GRAY[key + '_div'] = ('''        for (i = 0; i != 16; i++) {
            s32 l = (%s) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }''' % ' + '.join(TERMS[c] for c in o))

ZERO = {
    'i16': '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;',
    'i32step2': '        for (i = 0; i != 32; i += 2) *(u16 *)i = 0;',
    'i32step8': '        for (i = 0; i != 32; i += 8) { *(u16 *)i = 0; *(u16 *)(i + 2) = 0; *(u16 *)(i + 4) = 0; *(u16 *)(i + 6) = 0; }',
    'rot': '        for (i = 0; i != 32; i += 8) { *(u16 *)(i + 2) = 0; *(u16 *)(i + 4) = 0; *(u16 *)(i + 6) = 0; *(u16 *)i = 0; }',
    'step4': '        for (i = 0; i != 32; i += 4) { *(u16 *)i = 0; *(u16 *)(i + 2) = 0; }',
}

COPY = '        for (i = 0; i != 16; i++) ((u16 *)0)[i] = var_v0[i];'

tasks = []
for g, z in itertools.product(GRAY, ZERO):
    src = HEAD + '''    if (D_8004EAB8 == 1) {
''' + GRAY[g] + '''
    } else if ((D_8004EA9E[arg0] == 9) && (D_8004EA78 < 2)) {
''' + ZERO[z] + '''
    } else {
''' + COPY + '''
    }
}
'''
    p = OUT / f'{g}_{z}.c'
    p.write_text(src)
    tasks.append(p)


def score(p):
    try:
        r = dict(screen.measure('func_8001D47C', p))
        return (r['words'], r['compiled'], p.name)
    except Exception as e:
        return (10**6, 0, p.name + ' ' + str(e)[:60])


with cf.ThreadPoolExecutor(8) as pool:
    for r in sorted(pool.map(score, tasks))[:20]:
        print(r)
