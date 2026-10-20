/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

void osSpTaskYield(void) {
    __osSpSetStatus(SPSTATUS_SET_SIGNAL0);
}
