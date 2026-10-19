/* DRAFT. Remaining diff: not producible under the project's IDO 5.3 -O2 ABI. The original
 * (libaudio env.c _pullSubFrame) was built with interprocedural -O3: it receives the mixer in
 * s3, inp in s6, outCount in s5, the output-buffer pointer in s0 and the command pointer in t0,
 * clobbers s0-s7 without saving them, and calls func_800405E4 with arguments in a0/f14/f16/s1.
 * A standard-ABI compile differs from the prologue onward. Body follows the asm. */
#include "common.h"

typedef struct T035EnvSource {
    /* 0x00 */ u8 pad0[4];
    /* 0x04 */ s32 *(*handler)(struct T035EnvSource *, s16 *, s32, s32, s32 *);
} T035EnvSource;

typedef struct T035EnvMixer {
    /* 0x00 */ T035EnvSource *source;
    /* 0x04 */ u8 pad4[0x10];
    /* 0x14 */ void *state;
    /* 0x18 */ s16 pan;
    /* 0x1A */ s16 volume;
    /* 0x1C */ s16 cvolL;
    /* 0x1E */ s16 cvolR;
    /* 0x20 */ s16 dryamt;
    /* 0x22 */ s16 wetamt;
    /* 0x24 */ u16 lratl;
    /* 0x26 */ s16 lratm;
    /* 0x28 */ s16 ltgt;
    /* 0x2A */ u16 rratl;
    /* 0x2C */ s16 rratm;
    /* 0x2E */ s16 rtgt;
    /* 0x30 */ s32 delta;
    /* 0x34 */ s32 segEnd;
    /* 0x38 */ s32 first;
    /* 0x3C */ u8 pad3C[0xC];
    /* 0x48 */ s32 motion;
} T035EnvMixer;

extern s16 D_80048610[]; /* eqpower */
extern s16 D_8004870E[]; /* &eqpower[127] */
s16 func_800405E4(f64 vol, f64 tgt, s32 count, u16 *ratel);
u32 osVirtualToPhysical(void *);

s32 *func_800407B4(T035EnvMixer *e, s16 *inp, s16 *outp, s32 outCount, s32 sampleOffset, s32 *p) {
    T035EnvSource *source = e->source;
    s32 *ptr;

    if (e->motion != 1 || outCount == 0) {
        return p;
    }
    ptr = source->handler(source, inp, outCount, sampleOffset, p);
    ptr[0] = 0x08000000 | (*inp & 0xFFFF);
    ptr[1] = ((*outp + 0x440) << 16) | ((outCount << 1) & 0xFFFF);
    ptr[2] = 0x08080000 | ((*outp + 0x580) & 0xFFFF);
    ptr[3] = ((*outp + 0x6C0) << 16) | ((*outp + 0x800) & 0xFFFF);
    ptr += 4;
    if (e->first) {
        e->first = 0;
        e->ltgt = (D_80048610[e->pan] * e->volume) >> 15;
        e->lratm = func_800405E4(e->cvolL, e->ltgt, e->segEnd, &e->lratl);
        e->rtgt = (D_8004870E[-e->pan] * e->volume) >> 15;
        e->rratm = func_800405E4(e->cvolR, e->rtgt, e->segEnd, &e->rratl);
        ptr[0] = 0x09060000 | (e->cvolL & 0xFFFF);
        ptr[1] = 0;
        ptr[2] = 0x09040000 | (e->cvolR & 0xFFFF);
        ptr[3] = 0;
        ptr[4] = 0x09020000 | (e->ltgt & 0xFFFF);
        ptr[5] = (e->lratm << 16) | e->lratl;
        ptr[6] = 0x09000000 | (e->rtgt & 0xFFFF);
        ptr[7] = (e->rratm << 16) | e->rratl;
        ptr[8] = 0x09080000 | (e->dryamt & 0xFFFF);
        ptr[9] = e->wetamt & 0xFFFF;
        ptr[10] = 0x03090000;
        ptr[11] = osVirtualToPhysical(e->state);
        ptr += 12;
    } else {
        ptr[0] = 0x03080000;
        ptr[1] = osVirtualToPhysical(e->state);
        ptr += 2;
    }
    *inp += outCount << 1;
    e->delta += outCount;
    return ptr;
}
