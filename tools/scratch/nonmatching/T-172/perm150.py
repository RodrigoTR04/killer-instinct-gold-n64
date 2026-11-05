"""Permutation sweep of the sqrt-branch statements in func_8002E150."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()

STMT = {
    'z': '        z = (D_80048F78 - a) * 0.5;\n',
    't': '        t = sqrtf((float)z);\n',
    'u': '        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;\n',
    'w': '        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;\n',
    'r': '        r = z*u*t/w+t;\n',
}
ORDER = ['z', 't', 'u', 'w', 'r']
OLD = ''.join(STMT[k] for k in ORDER)
assert OLD in BASE

variants = {}
for perm in itertools.permutations(ORDER):
    variants[''.join(perm)] = BASE.replace(OLD, ''.join(STMT[k] for k in perm))

out = detail.run('func_8002E150', variants, jobs=12)
good = [(w, s, f, n) for n, w, s, f, _ in out if f == 0x60]
print('frame 0x60 variants:', len(good))
for w, s, f, n in good[:15]:
    print(w, s, hex(f), n)
