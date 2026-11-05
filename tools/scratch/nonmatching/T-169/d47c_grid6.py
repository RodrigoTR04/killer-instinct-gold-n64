#!/usr/bin/env python3
"""T-169 D47C: the counter `i` lands in a1; the target keeps it in t0 in all
three loops. Grid declaration order / scope of the named locals to move it."""
import concurrent.futures as cf
import importlib.util
import itertools
from pathlib import Path

ROOT = Path('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-4f670e05')
spec = importlib.util.spec_from_file_location('screen', ROOT / 'tools/permuter/screen.py')
screen = importlib.util.module_from_spec(spec)
spec.loader.exec_module(screen)
OUT = ROOT / 'tools/scratch/nonmatching/T-169/d47cg5'
OUT.mkdir(exist_ok=True)

DECLS = {
    'v_i': ['u16 *var_v0;', 's32 i;'],
    'i_v': ['s32 i;', 'u16 *var_v0;'],
    'v_d_i': ['u16 *var_v0;', 'u16 *dst;', 's32 i;'],
    'i_v_d': ['s32 i;', 'u16 *var_v0;', 'u16 *dst;'],
    'v_i_d': ['u16 *var_v0;', 's32 i;', 'u16 *dst;'],
    'd_i_v': ['u16 *dst;', 's32 i;', 'u16 *var_v0;'],
    'd_v_i': ['u16 *dst;', 'u16 *var_v0;', 's32 i;'],
    'i_d_v': ['s32 i;', 'u16 *dst;', 'u16 *var_v0;'],
}

G = '((var_v0[i] & 0x3E) >> 1)'
R = '((var_v0[i] & 0xF800) >> 11)'
B = '((var_v0[i] & 0x7C0) >> 6)'
SUM = f'{R} + {B} + {G}'

GRAY = '''    if (D_8004EAB8 == 1) {
        for (i = 0; i != 16; i++) {
            s32 l = (SUMEXP) / 3;
            ((u16 *)0)[i] = (l << 11) | (l << 6) | (l << 1);
        }
    } else if ((D_8004EA9E[arg0] == 9) && (D_8004EA78 < 2)) {
        for (i = 0; i != 16; i++) ((u16 *)0)[i] = 0;
    } else {
        for (i = 0; i != 16; i++) ((u16 *)0)[i] = var_v0[i];
    }
}
'''.replace('SUMEXP', SUM)

BODY = '''    if (D_8004EA9A == 0xB) {
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

PRE = '''extern u8 D_8004AC88;
extern u8 D_8004EA9E[];
extern s32 D_8004EA78;
extern u8 D_8004EA9A;
extern u8 D_8004EAB8;
extern u16 D_800614A0;
extern u8 D_801D3433;

void func_8001D47C(u8 arg0) {
'''

tasks = []
for name, decls in DECLS.items():
    src = PRE + ''.join('    ' + d + '\n' for d in decls) + BODY + GRAY
    p = OUT / f'{name}.c'
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
