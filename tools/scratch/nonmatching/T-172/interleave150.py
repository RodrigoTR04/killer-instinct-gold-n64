"""Interleave the s32 declarations among separate double declaration statements.

C89 allows any number of consecutive declaration statements in any order, so
`s32 hi;` and `s32 exponent;` can sit between individual `double z;` lines.
IDO assigns stack slots in declaration order, which is the one thing the
eight-way permutation sweep could not change.
"""
import itertools
import sys
from concurrent.futures import ThreadPoolExecutor

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
HDR = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
'''
DECL = '    double w, u, r, t, a, q, p, z;'
assert HDR in BASE and DECL in BASE

NAMES = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']

v = {}
# hi and exponent placed at every ordered pair of positions among the 8 doubles
slots = list(range(len(NAMES) + 1))
for hi_pos in slots:
    for ex_pos in slots:
        if hi_pos == ex_pos:
            continue
        lines = []
        for i in range(len(NAMES) + 1):
            if i == hi_pos:
                lines.append('    s32 hi;')
            if i == ex_pos:
                lines.append('    s32 exponent;')
            if i < len(NAMES):
                lines.append(f'    double {NAMES[i]};')
        body = BASE.replace(HDR + DECL,
                            '\n'.join(lines) + '\n'
                            '    hi = *(s32 *)&x;\n'
                            '    exponent = (hi >> 20) & 0x7FF;\n')
        v[f'hi{hi_pos}_ex{ex_pos}'] = body
print(len(v), 'variants', flush=True)
detail.run('func_8002E150', v, jobs=16)
