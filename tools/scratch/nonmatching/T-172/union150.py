"""Union / bit-access shapes for func_8002E150 (target: hi at sp+0x1C, z at sp+0x30)."""
import sys

sys.path.insert(0, 'tools/scratch/nonmatching/T-172')
import detail

HEAD = '''extern double D_80048EE0[],D_80048F10[],D_80048F38[],D_80048F58[];
extern double D_80048F78,D_80048F80,D_80048F88,D_80048F90,D_80048F98,D_80048FA0,D_80048FA8;
extern float sqrtf(float);
typedef union { double d; struct { u32 lo, hi; } w; } T172Dbl;
'''

BODY = '''    T172Dbl u;
    s32 exponent;
    double z, p, q, a, t, r, x2;
    u.d = x;
    exponent = (u.w.hi >> 20) & 0x7FF;
    if (exponent < 0x3FE) {
        if (exponent >= 0x3E3) {
            z = x * x;
            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            return z * p * x / q + x;
        }
        return x;
    }
    if (exponent < 0x3FF) {
        a = -x;
        if (x >= 0.0) a = x;
        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;
            do { z = t * t; } while (0);
            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (u.w.hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
        }
        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        x2 = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        r = z*(D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z)*t/x2+t;
        if (u.w.hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }
    if (x != x) return 0.0;
    if (x == D_80048F78) return D_80048F90;
    if (x == D_80048F80) return D_80048FA0;
    return 0.0;
}
'''

v = {'union_hi': HEAD + 'double func_8002E150(double x) {\n' + BODY}

# union with s32 pair, exponent as s32 from hi field
v['union_s32'] = HEAD.replace('u32 lo, hi', 's32 lo, hi') + 'double func_8002E150(double x) {\n' + BODY

# keep a local copy of hi like the original bit test
v['union_hi_local'] = HEAD + 'double func_8002E150(double x) {\n' + BODY.replace(
    '    s32 exponent;\n', '    s32 exponent, hi;\n').replace(
    'exponent = (u.w.hi >> 20) & 0x7FF;',
    'hi = u.w.hi;\n    exponent = (hi >> 20) & 0x7FF;').replace('u.w.hi > 0', 'hi > 0')

detail.run('func_8002E150', v, jobs=3)
