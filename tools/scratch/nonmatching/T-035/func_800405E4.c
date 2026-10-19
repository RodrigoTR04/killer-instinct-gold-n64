/* DRAFT. Remaining diff: not producible under the project's IDO 5.3 -O2 ABI. The original
 * (libaudio env.c _getRate) was built with interprocedural -O3: it takes count in a0, tgt in
 * f14, vol in f16 and ratel in s1, and uses s0/s1/s2/f20/f22 without saving them. Any -O2
 * compile of this C has a standard prologue saving those registers and standard argument
 * registers, so the whole function body differs. Structure below follows the asm control flow. */
#include "common.h"

extern f64 D_80048710[8]; /* log2 mantissa table, copied to the stack */
extern f64 D_80049620;
extern f64 D_80049628;
f64 _frexpf(f64 value, s32 *eptr);

s16 func_800405E4(f64 vol, f64 tgt, s32 count, u16 *ratel) {
    s16 s;
    f64 invn;
    f64 eps;
    f64 a;
    f64 fs;
    f64 mant;
    s32 i_invn;
    s32 ex;
    s32 indx;
    f64 logtab[8];

    if (count == 0) {
        if (tgt >= vol) {
            *ratel = 0xFFFF;
            return 0x7FFF;
        } else {
            *ratel = 0;
            return 0;
        }
    }
    if (tgt < 1.0) {
        tgt = 1.0;
    }
    if (vol <= 0) {
        vol = 1.0;
    }
    *(struct { f64 v[8]; } *)logtab = *(struct { f64 v[8]; } *)D_80048710;
    invn = (1.0 / count) * (f64)(1 << 30);
    i_invn = invn;
    mant = _frexpf(tgt / vol, &ex);
    indx = mant * 16;
    eps = (logtab[indx - 8] + ex) * D_80049620 / (1.0 * (1 << 30));
    fs = 1.0 + eps;
    a = 1.0;
    while (i_invn != 0) {
        if (i_invn & 1) {
            a *= fs;
        }
        fs *= fs;
        i_invn >>= 1;
    }
    a *= a;
    a *= a;
    a *= a;
    s = (s16)a;
    *ratel = (s16)((a - (f32)s) * D_80049628);
    return s;
}
