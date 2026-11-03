#!/usr/bin/env python3
"""Loop-form search for func_801BBB60 gradient loops. usage: bbsearch.py"""
import sys, itertools
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
import lib
base = Path('tools/scratch/nonmatching/T-158/w/bb60_base.c').read_text()
a = base.index('    if (i < 40) do')
b = base.index('    D_802C9F64 = 0;')
head, tail = base[:a], base[b:]
def forms(hi, expr_fn, var):
    # expr_fn(x) -> value expression given the index expression x
    e = expr_fn('i')
    F = {}
    F['dowhile_i++'] = f'    if (i < {hi}) do {{ {var} = i - LO; i++; *palette++ = {expr_fn(var)}; }} while (i < {hi});\n'
    F['for'] = f'    for (; i < {hi}; i++) *palette++ = {expr_fn("(i - LO)")};\n'
    F['for_var'] = f'    for (; i < {hi}; i++) {{ {var} = i - LO; *palette++ = {expr_fn(var)}; }}\n'
    F['for_noinc'] = f'    for (; i < {hi};) {{ {var} = i - LO; i++; *palette++ = {expr_fn(var)}; }}\n'
    F['while'] = f'    while (i < {hi}) {{ *palette++ = {expr_fn("(i - LO)")}; i++; }}\n'
    F['while_post'] = f'    while (i < {hi}) *palette++ = {expr_fn("((i++) - LO)")};\n'
    F['dowhile_post'] = f'    if (i < {hi}) do {{ *palette++ = {expr_fn("((i++) - LO)")}; }} while (i < {hi});\n'
    F['dowhile_inc_after'] = f'    if (i < {hi}) do {{ *palette++ = {expr_fn("(i - LO)")}; i++; }} while (i < {hi});\n'
    F['dowhile_inc_before'] = f'    if (i < {hi}) do {{ i++; *palette++ = {expr_fn("(i - LO - 1)")}; }} while (i < {hi});\n'
    F['for_idx'] = f'    for (; i < {hi}; i++) {{ {var} = i - LO; palette[0] = {expr_fn(var)}; palette++; }}\n'
    F['for_s16'] = f'    for (; i < {hi}; i++) *palette++ = (s16)({expr_fn("(i - LO)")});\n'
    F['for_tmp'] = f'    for (; i < {hi}; i++) {{ {var} = {expr_fn("(i - LO)")}; *palette++ = {var}; }}\n'
    return F
L1 = forms(40, lambda x: f'({x} << 11) | 1', 'red')
L2 = forms(72, lambda x: f'(({x} << 6) & 0x7C0) | 0xF801', 'green')
L3 = forms(128, lambda x: f'{x} | 0xFFC1', 'red')
LO = (8, 40, 72)
def mk(f1, f2, f3):
    t = ''.join(s.replace('LO', str(lo)) for s, lo in zip((f1, f2, f3), LO))
    return head + t + tail
res = {}
names = []; srcs = []
for k1 in L1:
    for k2 in L2:
        for k3 in L3:
            names.append((k1, k2, k3)); srcs.append(mk(L1[k1], L2[k2], L3[k3]).replace('s32 i, red, green;', 's32 i, red, green;'))
out = lib.run('func_801BBB60', srcs, prefix=False, workers=16)
best = sorted([(r[1], r[0], n) for n, r in zip(names, out) if r])
for x in best[:15]: print(x)
Path('/tmp/bbsearch.txt').write_text('\n'.join(map(str, best)))
