/* DRAFT. Remaining diff: temp registers only (original reuses t9 for curPtr+2 and t6/t7; ours t0/t1/t3); 6 words. */
#include "common.h"

typedef struct T035Seq {
    /* 0x00 */ u8 *base;
    /* 0x04 */ s32 len;
    /* 0x08 */ u8 *curPtr;
} T035Seq;

s16 func_800419C8(T035Seq *seq) {
    s16 tmp;

    tmp = *seq->curPtr++ << 8;
    tmp |= *seq->curPtr++;
    return tmp;
}
