"""Remove the `a` local entirely in func_8002E150 (target reloads x from its arg home)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
DECL = '    double w, u, r, t, a, q, p, z;'
assert DECL in BASE
ABS = '''        a = x;
        if (a < 0.0) a = -x;
        if (a < D_80048FA8) {
'''
assert ABS in BASE
ZSQ = '        z = (D_80048F78 - a) * 0.5;\n'
assert ZSQ in BASE

# 1: ternary inline, two uses of the abs, no `a`
v = {'inline_tern_two': BASE.replace(DECL, '    double w, u, r, t, q, p, z;').replace(
    ABS, '''        if ((x < 0.0 ? -x : x) < D_80048FA8) {
''').replace(ZSQ, '        z = (D_80048F78 - (x < 0.0 ? -x : x)) * 0.5;\n')}

# 2: one ternary in a condition guard, abs recomputed from x directly
v['inline_negx'] = BASE.replace(DECL, '    double w, u, r, t, q, p, z;').replace(
    ABS, '''        if ((x < 0.0 ? -x : x) < D_80048FA8) {
''').replace(ZSQ, '        z = (D_80048F78 + x) * 0.5;\n')

# 3: keep `a` but only assign once from the ternary (no if)
v['tern_once'] = BASE.replace(ABS, '''        a = (x < 0.0) ? -x : x;
        if (a < D_80048FA8) {
''')
detail.run('func_8002E150', v, jobs=3)
