/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

s32 osPiRawReadIo(u32 devAddr, u32 *data) {
    register u32 status;

    WAIT_ON_IO_BUSY(status);
    *data = IO_READ(osRomBase | devAddr);
    return 0;
}
