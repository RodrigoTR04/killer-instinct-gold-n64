"""Sweep z's position among the separate double declarations (target z at sp+0x30)."""
import itertools
import sys

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, prof

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
NAMES = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']
OLD = '\n'.join(f'    double {n};' for n in NAMES) + '\n    s32 hi;\n    s32 exponent;\n'
assert OLD in BASE

v = {}
for order in itertools.permutations(NAMES):
    v['/'.join(order)] = BASE.replace(OLD, '\n'.join(f'    double {n};' for n in order)
                                      + '\n    s32 hi;\n    s32 exponent;\n')
print(len(v), 'variants', flush=True)
out = detail.run('func_8002E150', v, jobs=16)
best = [(w, s, f, n) for n, w, s, f, _ in out]
print('--- frame 0x60 with word<93:')
for w, s, f, n in best:
    if f == 0x60 and w is not None and w < 93:
        print(w, s, hex(f), n)
