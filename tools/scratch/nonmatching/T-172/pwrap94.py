"""Test removing the existing p-wrap at the 94 base, plus alternative boundary wraps."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
PWRAP = '            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);\n'
PP = '            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);\n'
assert PWRAP in BASE

v = {'base_94': BASE, 'no_pwrap': BASE.replace(PWRAP, PP)}

# wrap the q statement instead in the same branch
QW = '            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;\n'
assert QW in BASE
v['wrap_q'] = BASE.replace(PWRAP, PP).replace(
    QW, '            do { ' + QW.strip() + ' } while (0);\n')

# wrap t = 2.0*... in the inner branch
TW = '            t = 2.0 * (x * x) - D_80048F78;\n'
v['wrap_t_inner'] = BASE.replace(TW, '            do { ' + TW.strip() + ' } while (0);\n')

detail.run('func_8002E150', v, jobs=4)
