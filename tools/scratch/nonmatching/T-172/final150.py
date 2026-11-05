"""Final focused sweep for func_8002E150: abs-compare source and the 0.5 multiply order."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
ABS = '''        a = -x;
        if (x >= 0.0) a = x;
'''
assert ABS in BASE

v = {'base': BASE}
# a) compare the original x but negate a (keeps x live, c.lt.d on x)
v['x_neg_a'] = BASE.replace(ABS, '''        a = x;
        if (x < 0.0) a = -a;
''')
# b) keep a as x and negate x
v['x_neg_x'] = BASE.replace(ABS, '''        a = x;
        if (a < 0.0) a = -x;
''')
# c) negate first then compare a (target order: c.lt.d then neg in delay)
v['neg_then_cmp'] = BASE.replace(ABS, '''        a = -x;
        if (a > x) a = x;
''')

# d) 0.5 as a right-hand multiply
h_half = '0.5 * (z * p * t / q + t)'
assert h_half in BASE
v['half_right'] = BASE.replace(h_half, '(z * p * t / q + t) * 0.5')
v['half_right_x_neg'] = v['x_neg_a'].replace(h_half, '(z * p * t / q + t) * 0.5')
v['half_div2'] = BASE.replace(h_half, '(z * p * t / q + t) / 2.0')
v['half_right_div2'] = BASE.replace(h_half, '0.5 * (z * p * t / q + t)').replace(
    'return D_80048F98 - 0.5 * (z * p * t / q + t);',
    'return D_80048F98 - (z * p * t / q + t) * 0.5;')
detail.run('func_8002E150', v, jobs=8)
