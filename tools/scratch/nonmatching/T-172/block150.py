"""Block-scope the polynomial temporaries in func_8002E150.

IDO allocates stack slots at the block where a local lives, so declaring p, q, r
inside the branch (instead of once at function top) changes both which temps need
slots and their order - the one dimension the whole-function declaration sweeps
could not reach.
"""
import itertools
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

TOPDECL = '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z'])
TOPDECL = TOPDECL + '\n    s32 hi;\n    s32 exponent;\n'
assert TOPDECL in BASE

BR1 = '''        if (exponent >= 0x3E3) {
            z = x * x;'''
assert BR1 in BASE
BR2 = '''        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;'''
assert BR2 in BASE
SQRTB = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);'''
assert SQRTB in BASE


def decl(names, indent='    '):
    return ''.join(f'{indent}double {n};\n' for n in names)


v = {}
# 1: p,q block-scoped in branch 1 only
t = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'z'])
                 + '\n    s32 hi;\n    s32 exponent;\n')
t = t.replace(BR1, BR1.replace('            z = x * x;', '            double p, q;\n\n            z = x * x;'))
# branch 2 also uses p,q -> declare there too
t = t.replace(BR2, BR2.replace('            t = 2.0', '            double p, q;\n\n            t = 2.0'))
v['pq_blocked'] = t

# 2: only the sqrt branch's locals blocked (z, t, w, u, r) and p,q at top
t2 = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in ['p', 'q'])
                  + '\n    s32 hi;\n    s32 exponent;\n')
t2 = t2.replace(BR1, BR1.replace('            z = x * x;', '            double z;\n\n            z = x * x;'))
t2 = t2.replace(BR2, BR2.replace('            t = 2.0', '            double z, t;\n\n            t = 2.0'))
t2 = t2.replace(SQRTB, '        {\n        double z, t, w, u, r;\n\n' + SQRTB)
t2 = t2.replace('''        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }''', '''        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
        }
    }''')
v['sqrt_blocked'] = t2

# 3: all polynomial temps blocked in both branches, only z/t shared
for order in itertools.permutations(['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']):
    pass

print(len(v), 'variants', flush=True)


def sig(text, label):
    w, s, f, _ = detail.detail('func_8002E150', text, label)
    if f is None:
        return None
    lines = slotdump.dump('func_8002E150', text, label)
    c = Counter()
    for ln in lines:
        for m in re.finditer(r'(\d+)\(sp\)', ln):
            c[int(m.group(1))] += 1
    return w, s, f, c


print('TARGET', fmt(TF, TC), flush=True)
for name, text in v.items():
    r = sig(text, name)
    if r is None:
        print(f'{name:14s} FAIL'); continue
    w, s, f, c = r
    print(f'{name:14s} w={w} size={s} frame={f:#x} match={c == TC} {dict(sorted(c.items()))}')
