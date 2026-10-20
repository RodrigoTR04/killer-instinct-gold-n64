/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

void __osSpSetStatus(u32 status) {
    IO_WRITE(SP_STATUS_REG, status);
}
