/* DRAFT. Remaining diff: (1) jump table and float constants (jtbl_80049690, D_800496B0, D_800496B8) are rodata owned by the main data asm; compiling this switch emits a new .rodata table (+8 bytes padding, wrong addresses). (2) original keeps the switch bounds check (sltiu/beqz) even though p & 7 covers 0-7, and loads val in v1 in the branch delay slot; IDO 5.3 -O2 elides the check, so val lands in a3 and the lp pointer in v1 (about 15 register words). Likely -O3 libaudio build (reverb.c alFxParamHdl). */
#include "common.h"

typedef struct T035LowPass {
    /* 0x00 */ s16 fc;
} T035LowPass;

typedef struct T035Delay {
    /* 0x00 */ u32 input;
    /* 0x04 */ u32 output;
    /* 0x08 */ s16 ffcoef;
    /* 0x0A */ s16 fbcoef;
    /* 0x0C */ s16 gain;
    /* 0x10 */ f32 rsinc;
    /* 0x14 */ f32 rsval;
    /* 0x18 */ s32 rsdelta;
    /* 0x1C */ f32 rsgain;
    /* 0x20 */ T035LowPass *lp;
    /* 0x24 */ void *rs;
} T035Delay;

typedef struct T035Fx {
    /* 0x00 */ u8 pad0[0x20];
    /* 0x20 */ T035Delay *delay;
} T035Fx;

s32 func_80042198(void *filter, s32 paramID, void *param) {
    T035Fx *f = (T035Fx *)filter;
    s32 p = paramID - 2;
    s32 val = *(s32 *)param;

    switch (p & 7) {
        case 0:
            f->delay[p / 8].input = val;
            break;
        case 1:
            f->delay[p / 8].output = val;
            break;
        case 2:
            f->delay[p / 8].ffcoef = val;
            break;
        case 3:
            f->delay[p / 8].fbcoef = val;
            break;
        case 4:
            f->delay[p / 8].gain = val;
            break;
        case 5:
            f->delay[p / 8].rsinc = (f32)val / 16777215.0f;
            break;
        case 6:
            f->delay[p / 8].rsgain = ((f32)val / 173123.404906676) * (f->delay[p / 8].output - f->delay[p / 8].input);
            break;
        default:
            return 0;
        case 7:
            if (f->delay[p / 8].lp != 0) {
                f->delay[p / 8].lp->fc = val;
            }
            break;
    }
    return 0;
}
