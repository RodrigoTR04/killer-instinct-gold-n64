/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

s32 __osSiRawReadIo(u32 devAddr, u32 *data) {
    if (__osSiDeviceBusy()) {
        return -1;
    }
    *data = IO_READ(devAddr);
    return 0;
}
