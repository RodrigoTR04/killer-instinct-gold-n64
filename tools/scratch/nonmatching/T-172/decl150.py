"""Sweep declaration order + extra live temps for func_8002E150 (frame 0x60 goal)."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
DECL = '    double z, p, q, a, t, r, u, w;'
assert DECL in BASE

NAMES = ['z', 'p', 'q', 'a', 't', 'r', 'u', 'w', 's', 'k']
v = {}
# every rotation of the declaration list (keeps code identical, may change slot order)
for extra in ([], ['s'], ['s', 'k'], ['s', 'k', 'n2'], ['s', 'k', 'n2', 'n3']):
    names = [n for n in NAMES if n in 'zpqatruw' or n in extra]
    names = ['z', 'p', 'q', 'a', 't', 'r', 'u', 'w'] + extra
    joined = ', '.join(names)
    v['decl_' + '+'.join(extra) if extra else 'decl_base'] = BASE.replace(
        DECL, f'    double {joined};')
    v['rev_' + '+'.join(extra) if extra else 'rev_base'] = BASE.replace(
        DECL, f'    double {", ".join(reversed(names))};')
    v['rot_' + '+'.join(extra) if extra else 'rot_base'] = BASE.replace(
        DECL, f'    double {", ".join(names[1:] + names[:1])};')
detail.run('func_8002E150', v, jobs=12)
