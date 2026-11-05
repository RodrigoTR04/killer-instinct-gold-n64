"""Reassign the x parameter instead of copying to a local (func_8002E150)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
ABS = '''        a = x;
        if (a < 0.0) a = -x;
'''
assert ABS in BASE

v = {'base_94': BASE}

# 1. drop `a`: fold |x| into the parameter, then use x everywhere in the branch
v['param_fold'] = BASE.replace('    double w, u, r, t, a, q, p, z;',
                               '    double w, u, r, t, q, p, z;').replace(
    ABS, '''        if (x < 0.0) x = -x;
''').replace('if (a < D_80048FA8) {', 'if (x < D_80048FA8) {').replace(
    'z = (D_80048F78 - a) * 0.5;', 'z = (D_80048F78 - x) * 0.5;')

# 2. same but only the sqrt branch negates (a still used for the test)
v['param_fold_late'] = BASE.replace(
    ABS + '        if (a < D_80048FA8) {\n',
    '''        if (x < 0.0) a = -x; else a = x;
        if (a < D_80048FA8) {
''')

# 3. keep `a` but assign it via the parameter expression chain
v['a_from_x'] = BASE.replace(ABS, '''        a = x;
        if (x < 0.0) a = -x;
''')

# 4. x folded, and the first polynomial branch keeps the original sign via a local
v['param_fold_sep'] = BASE.replace('    double w, u, r, t, a, q, p, z;',
                                   '    double w, u, r, t, q, p, z;').replace(
    ABS, '''        if (x < 0.0) x = -x;
''').replace('if (a < D_80048FA8) {', 'if (x < D_80048FA8) {').replace(
    'z = (D_80048F78 - a) * 0.5;', 'z = (D_80048F78 - x) * 0.5;').replace(
    'if (hi > 0) return D_80048F90 - 2.0 * r;',
    'if (hi > 0) return D_80048F90 - 2.0 * r;')
detail.run('func_8002E150', v, jobs=4)
