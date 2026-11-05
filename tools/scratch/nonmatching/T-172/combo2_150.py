"""Combine abs shape x sqrt-order x p-wrap for func_8002E150."""
import itertools
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()

ABS_NEG = '''        a = -x;
        if (x >= 0.0) a = x;
'''
ABS_RELOAD = '''        a = x;
        if (a < 0.0) a = -a;
'''
assert ABS_NEG in BASE

SQRT = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
'''
assert SQRT in BASE
STMTS = {
    'z': '        z = (D_80048F78 - a) * 0.5;\n',
    't': '        t = sqrtf((float)z);\n',
    'w': '        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;\n',
    'u': '        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;\n',
    'r': '        r = z*u*t/w+t;\n',
}

P_WRAP = '            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);\n'
P_PLAIN = '            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);\n'
assert P_WRAP in BASE

v = {}
for absname, absrc in (('neg', ABS_NEG), ('reload', ABS_RELOAD)):
    for wrapname, wrap in (('pwrap', P_WRAP), ('pplain', P_PLAIN)):
        for perm in itertools.permutations('ztwur'):
            body = BASE.replace(ABS_NEG, absrc).replace(P_WRAP, wrap)
            body = body.replace(SQRT, ''.join(STMTS[k] for k in perm))
            v[f'{absname}/{wrapname}/{perm[0]}{perm[1]}{perm[2]}{perm[3]}{perm[4]}'] = body
print(len(v), 'variants')
detail.run('func_8002E150', v, jobs=14)
