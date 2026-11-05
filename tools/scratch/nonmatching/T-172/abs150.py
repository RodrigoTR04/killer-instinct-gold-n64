"""Shape variants for the |x| and 0.5 regions of func_8002E150."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()

ABS = '''        a = x;
        if (a < 0.0) a = -a;
'''
assert ABS in BASE

v = {'base': BASE}
v['abs_ternary'] = BASE.replace(ABS, '''        a = (x < 0.0) ? -x : x;
''')
v['abs_ternary_a'] = BASE.replace(ABS, '''        a = x < 0.0 ? -x : x;
''')
v['abs_fabsf'] = BASE.replace(ABS, '''        a = (x < 0.0) ? -x : x;
'''.replace('a = ', 'a = '))
v['abs_if_else'] = BASE.replace(ABS, '''        a = x;
        if (a < 0.0) {
            a = -a;
        }
''')
v['abs_no_local'] = BASE.replace(ABS, '''        if (x < 0.0) a = -x; else a = x;
''')
v['abs_neg_ternary'] = BASE.replace(ABS, '''        a = -x;
        if (x >= 0.0) a = x;
''')
v['abs_0minus'] = BASE.replace(ABS, '''        a = x;
        if (a < 0.0) a = 0.0 - a;
''')
detail.run('func_8002E150', v, jobs=7)
