/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

extern OSViContext *__osViCurr;

OSViContext *__osViGetCurrentContext() {
    return __osViCurr;
}
