/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

OSMesgQueue *osPiGetCmdQueue(void) {
    if (!__osPiDevMgr.active) {
        return NULL;
    }
    return __osPiDevMgr.cmdQueue;
}
