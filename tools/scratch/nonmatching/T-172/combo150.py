"""Combined abs-shape x sqrt-branch-order sweep for func_8002E150."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()

OLD_SQRT = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        r = z*u*t/w+t;
'''
assert OLD_SQRT in BASE

ABS = '''        a = -x;
        if (x >= 0.0) a = x;
'''
assert ABS in BASE

STMTS = {
    'z': '        z = (D_80048F78 - a) * 0.5;\n',
    't': '        t = sqrtf((float)z);\n',
    'u': '        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;\n',
    'w': '        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;\n',
    'r': '        r = z*u*t/w+t;\n',
}
ABS_VARIANTS = {
    'neg': ABS,
    'reload': '        a = x;\n        if (a < 0.0) a = -a;\n',
    'ifno': '        a = -x;\n        if (x > 0.0) a = x;\n' if False else '        a = -x;\n        if (0.0 <= x) a = x;\n',
    'neg2': '        a = -x;\n        if (x >= 0.0) { a = x; }\n',
}

v = {}
for aname, absrc in ABS_VARIANTS.items():
    body = BASE.replace(ABS, absrc)
    for perm in itertools.permutations('ztuwr'):
        order = ''.join(perm)
        v[f'{aname}/{order}'] = body.replace(OLD_SQRT, ''.join(STMTS[k] for k in perm))
print(len(v), 'variants')
out = detail.run('func_8002E150', v, jobs=14)
