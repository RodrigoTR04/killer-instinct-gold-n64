/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

u32 __osSpGetStatus() {
    return IO_READ(SP_STATUS_REG);
}
