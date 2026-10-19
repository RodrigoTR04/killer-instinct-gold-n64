/* DRAFT. Remaining diff: ABI: original receives samples in a0, ratem in a1, ratel in a2 alongside ivol in f12 (IPA -O3 non-standard argument passing); with -O2 ABI they arrive in a1-a3; also f4 vs f16/f18 FP regs. ~20 words. */
#include "common.h"

f32 func_80040A4C(f32 ivol, s32 samples, s16 ratem, u16 ratel) {
    f32 r;
    f32 a;
    s32 i;

    samples >>= 3;
    if (samples == 0) {
        return ivol;
    }
    r = ((f32)(ratem << 16) + (f32)ratel) / 65536;
    a = 1.0f;
    for (i = 0; i < 32; i++) {
        if (samples & 1) {
            a *= r;
        }
        samples >>= 1;
        if (samples == 0) {
            break;
        }
        r *= r;
    }
    ivol *= a;
    return ivol;
}
