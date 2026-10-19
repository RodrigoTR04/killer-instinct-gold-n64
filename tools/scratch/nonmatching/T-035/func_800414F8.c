/* DRAFT. Remaining diff: register allocation: original cycles only t6-t9 and keeps value in a1/c in v0 (IPA -O3 build of libaudio seq.c); 4+ temp-register words differ under -O2. */
#include "common.h"

typedef struct T035Seq {
    /* 0x00 */ u8 *base;
    /* 0x04 */ s32 len;
    /* 0x08 */ u8 *curPtr;
} T035Seq;

u32 func_800414F8(T035Seq *seq) {
    u32 value;
    u32 c;

    c = *seq->curPtr++;
    value = c;
    if (c & 0x80) {
        value = c & 0x7F;
        do {
            c = *seq->curPtr++;
            value = (value << 7) + (c & 0x7F);
        } while (c & 0x80);
    }
    return value;
}
