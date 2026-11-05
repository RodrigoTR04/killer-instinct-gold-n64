"""float/double intermediate combos plus abs shapes, filtered on slot signature."""
import itertools
import re
import sys
from collections import Counter

sys.path.insert(0, '/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172')
import detail, slotdump
from slotsig import target_sig, fmt

BASE = open('/home/rodri/.t3/worktrees/killer-instinct-gold-n64/t3-3ac7a743/tools/scratch/nonmatching/T-172/func_8002E150.c').read()
TF, TC = target_sig('func_8002E150')

ABS = '''        a = x;
        if (x < 0.0) a = -x;
'''
assert ABS in BASE

SQ = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
'''
assert SQ in BASE

ABS_FORMS = {
    'ifneg': ABS,
    'ifelse': '        if (x < 0.0) {\n            a = -x;\n        } else {\n            a = x;\n        }\n',
    'tern': '        a = (x < 0.0) ? -x : x;\n',
    'negif': '        a = -x;\n        if (x >= 0.0) a = x;\n',
    'negif2': '        a = -x;\n        if (0.0 <= x) a = x;\n',
}

SQRT_FORMS = {
    'base': SQ,
    # t as a float local (needs a separate f32 variable)
    'float_t': '''        z = (D_80048F78 - a) * 0.5;
        ft = sqrtf((float)z);
        t = ft;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
''',
    # ratio computed into a named double first
    'ratio': '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w;
        r = r+t;
''',
}

v = {}
for aname, absrc in ABS_FORMS.items():
    for sname, sqrtrc in SQRT_FORMS.items():
        text = BASE.replace(ABS, absrc).replace(SQ, sqrtrc)
        if 'ft' in sqrtrc:
            text = text.replace('    s32 hi;\n', '    f32 ft;\n    s32 hi;\n')
        v[f'{aname}/{sname}'] = text
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
best = []
for name, text in v.items():
    r = sig(text, name)
    if r is None:
        print(f'{name:18s} FAIL'); continue
    w, s, f, c = r
    best.append((w, name, s, f, c))
best.sort(key=lambda x: (x[0] is None, x[0]))
for w, name, s, f, c in best:
    print(f'{w}\t{name}\t{s}\t{f:#x}\t{TC == c}')
