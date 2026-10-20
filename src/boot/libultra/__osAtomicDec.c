/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

s32 __osAtomicDec(u32 *a0) {
    s32 sp1c;
    s32 sp18;
    sp1c = __osDisableInt();

    if (*a0 != 0) {
        (*a0)--;
        sp18 = 1;
    } else {
        sp18 = 0;
    }

    __osRestoreInt(sp1c);
    return sp18;
}
