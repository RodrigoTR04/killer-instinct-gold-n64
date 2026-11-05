"""Sweep abs shapes x sqrt-branch order filtered on the exact target slot signature."""
import itertools
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

ABS = '''        if (x < 0.0) a = -x;
'''
assert ABS in BASE

SQ = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
'''
assert SQ in BASE
S = {
    'z': '        z = (D_80048F78 - a) * 0.5;\n',
    't': '        t = sqrtf((float)z);\n',
    'w': '        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;\n',
    'u': '        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;\n',
    'r': '        r = z*u*t/w+t;\n',
}

# abs is the line just before; base text is "a = x;" then the if on the next line
ABSL = '        a = x;\n        if (x < 0.0) a = -x;\n'
assert ABSL in BASE
ABS_FORMS = {
    'ifneg': ABSL,
    'negif': '        a = -x;\n        if (x >= 0.0) a = x;\n',
    'ifneg_neg_a': '        a = x;\n        if (x < 0.0) a = -a;\n',
    'if_a_neg_x': '        a = x;\n        if (a < 0.0) a = -x;\n',
    'if_a_neg_a': '        a = x;\n        if (a < 0.0) a = -a;\n',
    'negif_neg_a': '        a = -x;\n        if (a <= x) a = x;\n',
}

variants = {}
for an, ar in ABS_FORMS.items():
    for perm in itertools.permutations('ztwur'):
        text = BASE.replace(ABSL, ar).replace(SQ, ''.join(S[k] for k in perm))
        variants[f'{an}/{perm[0]}{perm[1]}{perm[2]}{perm[3]}{perm[4]}'] = text
print(len(variants), 'variants', flush=True)


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
rows = []
for name, text in variants.items():
    r = sig(text, name)
    if r:
        rows.append((r[0], name, r[1], r[2], r[3] == TC))
rows.sort()
for w, name, s, f, match in rows[:12]:
    print(f'{w}\t{name}\t{s}\t{f:#x}\tmatch={match}')
