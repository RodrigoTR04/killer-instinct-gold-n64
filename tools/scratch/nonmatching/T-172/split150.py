"""Targeted expression splits that could shift z's temp-slot allocation (func_8002E150)."""
import sys
from collections import Counter
import re

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

SQ = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
'''
assert SQ in BASE

v = {'base93': BASE}

# Split the sqrt-branch polynomials into sequential statements on an existing local.
v['u_split'] = BASE.replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[3]*z+D_80048F38[2];
        u = u*z+D_80048F38[1];
        r = z*u*t/w+t;
''')
v['w_split'] = BASE.replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = z+D_80048F58[2];
        w = w*z+D_80048F58[1];
        w = D_80048F58[0]+w*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
''')
v['both_split'] = BASE.replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = z+D_80048F58[2];
        w = w*z+D_80048F58[1];
        w = D_80048F58[0]+w*z;
        u = D_80048F38[3]*z+D_80048F38[2];
        u = u*z+D_80048F38[1];
        r = z*u*t/w+t;
''')
# name the 0.5 constant
v['half_named'] = BASE.replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t;
        r = r/w;
        r = r+t;
''')
# split ratio chain in a different order
v['r_split'] = BASE.replace(SQ, '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u;
        r = r*t;
        r = r/w+t;
''')
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


print('TARGET', fmt(TF, TC))
for name, text in v.items():
    r = sig(text, name)
    if r is None:
        print(f'{name:12s} FAIL')
        continue
    w, s, f, c = r
    print(f'{name:12s} w={w} size={s} frame={f:#x} {dict(sorted(c.items()))} {"MATCH" if c == TC else ""}')
