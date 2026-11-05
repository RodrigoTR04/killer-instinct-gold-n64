extern double D_80048EE0[],D_80048F10[],D_80048F38[],D_80048F58[];
extern double D_80048F78,D_80048F80,D_80048F88,D_80048F90,D_80048F98,D_80048FA0,D_80048FA8;
extern float sqrtf(float);
double func_8002E150(double x) {
    s32 hi = *(s32 *)&x;
    s32 exponent = (hi >> 20) & 0x7FF;
    double w, u, r, t, a, q, p, z;
    if (exponent < 0x3FE) {
        if (exponent >= 0x3E3) {
            z = x * x;
            p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            return z * p * x / q + x;
        }
        return x;
    }
    if (exponent < 0x3FF) {
        a = x;
        if (a < 0.0) a = -x;
        if (a < D_80048FA8) {
            t = 2.0 * (x * x) - D_80048F78;
            do { z = t * t; } while (0);
            do { p = D_80048EE0[1]+((((D_80048EE0[5]*z+D_80048EE0[4])*z+D_80048EE0[3])*z+D_80048EE0[2])*z); } while (0);
            q = D_80048F10[0]+(((z+D_80048F10[3])*z+D_80048F10[2])*z+D_80048F10[1])*z;
            if (hi > 0) return 0.5 * (z * p * t / q + t) + D_80048F88;
            return D_80048F98 - 0.5 * (z * p * t / q + t);
        }
        z = (D_80048F78 - a) * 0.5;
        t = sqrtf((float)z);
        w = D_80048F58[0]+((z+D_80048F58[2])*z+D_80048F58[1])*z;
        u = D_80048F38[1]+(D_80048F38[3]*z+D_80048F38[2])*z;
        r = z*u*t/w+t;
        if (hi > 0) return D_80048F90 - 2.0 * r;
        return 2.0 * r + D_80048FA0;
    }
    if (x != x) return 0.0;
    if (x == D_80048F78) return D_80048F90;
    if (x == D_80048F80) return D_80048FA0;
    return 0.0;
}
