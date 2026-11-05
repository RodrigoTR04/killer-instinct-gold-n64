"""Declaration/statement-order variants for func_8002E150 at 100 words."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

BASE = open('tools/scratch/nonmatching/T-172/func_8002E150.c').read()
v = {'base': BASE}

DECL = '    double w, u, r, t, a, q, p, z;'
HDR = '''    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
'''
assert HDR in BASE and DECL in BASE

# int locals declared after the doubles
v['ints_after'] = BASE.replace(HDR + DECL,
                              DECL + '    s32 hi, exponent;\n')
# separate hi/exponent declarations
v['ints_sep'] = BASE.replace(HDR, '    s32 hi = *(s32 *)&x;\n    s32 exponent;\n    exponent = (hi >> 20) & 0x7FF;\n')
# exponent as u32
v['exp_u32'] = BASE.replace('s32 exponent', 'u32 exponent')
# hi computed as s32 from a union-free cast in a temp local
v['hi_late'] = BASE.replace(HDR, '    s32 hi, exponent;\n    hi = *(s32 *)&x;\n    exponent = (hi >> 20) & 0x7FF;\n')
# doubles declared before the ints but with a separate line each
v['two_lines'] = BASE.replace(DECL, '    double z, p, q, a, t, r, u, w;\n'.replace('z, p, q, a, t, r, u, w', 'w, u, r, t, a, q, p, z'))
# int slot: make hi a "long" 
v['hi_unsigned'] = BASE.replace('s32 hi', 'u32 hi')
# abs via if/else
ABS = '''        a = -x;
        if (x >= 0.0) a = x;
'''
assert ABS in BASE
v['abs_ifelse'] = BASE.replace(ABS, '''        if (x < 0.0) {
            a = -x;
        } else {
            a = x;
        }
''')
v['abs_reload'] = BASE.replace(ABS, '''        a = x;
        if (a < 0.0) a = -a;
''')
v['abs_ternary2'] = BASE.replace(ABS, '''        a = x < 0.0 ? -x : x;
''')
v['abs_ternary3'] = BASE.replace(ABS, '''        a = (x < 0.0) ? -x : x;
''')
detail.run('func_8002E150', v, jobs=12)
