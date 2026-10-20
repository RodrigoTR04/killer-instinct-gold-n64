/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

extern OSViContext *__osViNext;

// TODO: name magic constants
void osViBlack(u8 active) {
    register u32 int_disabled = __osDisableInt();
    if (active) {
        __osViNext->unk00 |= 0x20;
    } else {
        __osViNext->unk00 &= ~0x20;
    }
    __osRestoreInt(int_disabled);
}
