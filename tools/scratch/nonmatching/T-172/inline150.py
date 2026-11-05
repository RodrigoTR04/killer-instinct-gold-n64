"""Inlining-level variants for func_8002E150, watching frame size."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

HEAD = '''extern double D_80048EE0[],D_80048F10[],D_80048F38[],D_80048F58[];
extern double D_80048F78,D_80048F80,D_80048F88,D_80048F90,D_80048F98,D_80048FA0,D_80048FA8;
extern float sqrtf(float);
'''

P = 'D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z)'
Q = 'D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z'
U = 'D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z'
W = 'D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z'

TAIL = '''    if (x != x) return 0.0;
    if (x == D_80048F78) return D_80048F90;
    if (x == D_80048F80) return D_80048FA0;
    return 0.0;
}
'''


def build(branch1, branch2, branch2b):
    return (HEAD + 'double func_8002E150(double x) {\n'
            '    s32 hi = *(s32 *)&x;\n'
            '    s32 exponent = (hi >> 20) & 0x7FF;\n'
            '    double z, p, q, a, t, r, u, w;\n'
            '    if (exponent < 0x3FE) {\n' + branch1 +
            '        return x;\n    }\n'
            '    if (exponent < 0x3FF) {\n        a = x;\n'
            '        if (a < 0.0) a = -a;\n'
            '        if (a < D_80048FA8) {\n' + branch2b +
            '        }\n' + branch2 +
            '    }\n' + TAIL)


b1_local = f'''        if (exponent >= 0x3E3) {{
            z = x * x;
            p = {P};
            q = {Q};
            return z * p * x / q + x;
        }}
'''
b1_inline = f'''        if (exponent >= 0x3E3) {{
            z = x * x;
            return z * ({P}) * x / ({Q}) + x;
        }}
'''
b1_allin = '''        if (exponent >= 0x3E3) {
            return x * x * (D_80048EE0[1]+((((D_80048EE0[5]*(x*x)+D_80048EE0[4])*(x*x)+D_80048EE0[3])*(x*x)+D_80048EE0[2])*(x*x))) * x / (D_80048F10[0]+(((x*x+D_80048F10[3])*(x*x)+D_80048F10[2])*(x*x)+D_80048F10[1])*(x*x)) + x;
        }
'''

b2_local = f'''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        u = {U};
        w = {W};
        r = z*u*t/w+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
'''
b2_inline = f'''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        r = z*({U})*t/({W})+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
'''
b2_allin = '''        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        if (hi > 0) return D_80048F90 - 2.0 * (z*(D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z)*t/(D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z)+t);
        return 2.0 * (z*(D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z)*t/(D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z)+t) + D_80048FA0;
'''

b2b_local = f'''            t = 2.0 * (x * x) - D_80048F78;
            do {{ z = t * t; }} while (0);
            p = {P};
            q = {Q};
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
'''
b2b_inline = f'''            t = 2.0 * (x * x) - D_80048F78;
            do {{ z = t * t; }} while (0);
            if (hi > 0) return 0.5 * (z * ({P}) * t / ({Q}) + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * ({P}) * t / ({Q}) + t);
'''

v = {
    'lll': build(b1_local, b2_local, b2b_local),
    'lli': build(b1_local, b2_inline, b2b_local),
    'lii': build(b1_local, b2_inline, b2b_inline),
    'iil': build(b1_inline, b2_local, b2b_local),
    'ili': build(b1_inline, b2_local, b2b_inline),
    'iii': build(b1_inline, b2_inline, b2b_inline),
    'ili_ai': build(b1_inline, b2_allin, b2b_inline),
}
detail.run('func_8002E150', v, jobs=7)
