"""Find a shape that puts z at sp+0x30 in a 0x60 frame (func_8002E150).

Observed: 8 function-scope doubles -> frame 0x60 but z at 0x20 (0x10 too low).
p/q block-scoped -> z at the right *relative* spot but frame 0x50.
So the original had something live at 0x20/0x28 as well. Enumerate honest shapes
where a real computation is spelled with its own block-scoped temporaries while the
function-scope set stays at 8 doubles.
"""
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')
NAMES = ['w', 'u', 'r', 't', 'a', 'q', 'p', 'z']
TOPDECL = '\n'.join(f'    double {n};' for n in NAMES) + '\n    s32 hi;\n    s32 exponent;\n'
assert TOPDECL in BASE


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


v = {'base93': BASE}

# A: function-scope set of 8, but the small-|x| branch works on block-scoped copies
A = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in NAMES) + '\n    s32 hi;\n    s32 exponent;\n')
A = A.replace('''        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;''', '''        if (a < D_80048FA8) {
            double p2, q2;

            t = 2.0 * (x * x) - D_80048F78;''')
A = A.replace('''            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);''',
              '''            q2 = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p2 * t / q2 + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p2 * t / q2 + t);''')
A = A.replace('''            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]''', '''            do { p2 = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]''')
v['copy_pq'] = A

# B: sqrt branch computes its polynomials through block-scoped copies
B = BASE.replace('''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);''', '''        {
        double w2, u2;

        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);''')
B = B.replace('''        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }''', '''        w2 = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u2 = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u2*t/w2+t;
        }
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }''')
v['copy_wu'] = B

# C: branch-1 z block-scoped so it frees a slot, p/q stay at top
C = BASE.replace(TOPDECL, '\n'.join(f'    double {n};' for n in ['w', 'u', 'r', 't', 'a', 'q', 'p'])
                 + '\n    s32 hi;\n    s32 exponent;\n')
C = C.replace('''        if (exponent >= 0x3E3) {
            z = x * x;''', '''        if (exponent >= 0x3E3) {
            double z;

            z = x * x;''')
C = C.replace('''        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;''', '''        if (a < D_80048FA8) {
            double z;

            t = 2.0 * (x * x) - D_80048F78;''')
C = C.replace('''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);''', '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);''')
v['z_blocked'] = C

print(len(v), 'variants', flush=True)
print('TARGET', fmt(TF, TC), flush=True)
for name, text in v.items():
    r = sig(text, name)
    if r is None:
        print(f'{name:10s} FAIL'); continue
    w, s, f, c = r
    print(f'{name:10s} w={w} size={s} frame={f:#x} match={c == TC} {dict(sorted(c.items()))}')
