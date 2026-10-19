/* DRAFT. Remaining diff: instruction order/temp registers (original interleaves first two loads and reuses t6/t7; IDO 5.3/7.1 -O2/-O3 standalone all differ). */
#include "common.h"

typedef struct T035Seq {
    /* 0x00 */ u8 *base;
    /* 0x04 */ s32 len;
    /* 0x08 */ u8 *curPtr;
} T035Seq;

s32 func_80041978(T035Seq *seq) {
    s32 tmp;

    tmp = *seq->curPtr++ << 24;
    tmp |= *seq->curPtr++ << 16;
    tmp |= *seq->curPtr++ << 8;
    tmp |= *seq->curPtr++;
    return tmp;
}
