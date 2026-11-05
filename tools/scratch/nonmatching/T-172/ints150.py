"""Declaration placement for the int temps in func_8002E150 (target: hi at sp+0x1C)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
DECL = '    double w, u, r, t, a, q, p, z;'
assert DECL in BASE
HDR = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
'''
assert HDR in BASE

v = {'base': BASE}

# int locals declared (uninitialised) BEFORE the doubles
v['ints_then_doubles'] = BASE.replace(
    HDR + DECL,
    '    s32 hi, exponent;\n' + DECL +
    '    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')

# int locals declared before the doubles, doubles on separate lines
v['ints_sep_doubles'] = BASE.replace(
    HDR + DECL,
    '    s32 hi, exponent;\n    double z;\n    double p;\n    double q;\n'
    '    double a;\n    double t;\n    double r;\n    double u;\n    double w;\n'
    '    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')

# hi from a separate local view, exponent computed inline at each use
v['exp_inline'] = BASE.replace(HDR, '    s32 hi = *(s32 *)&x;\n').replace(
    'exponent < 0x3FE', '((hi >> 20) & 0x7FF) < 0x3FE').replace(
    'exponent >= 0x3E3', '((hi >> 20) & 0x7FF) >= 0x3E3').replace(
    'exponent < 0x3FF', '((hi >> 20) & 0x7FF) < 0x3FF')

# u32 exponent
v['exp_u32'] = BASE.replace('s32 exponent', 'u32 exponent')

# hi as u32
v['hi_u32'] = BASE.replace('s32 hi', 'u32 hi')

detail.run('func_8002E150', v, jobs=5)
