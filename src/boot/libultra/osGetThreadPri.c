/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

OSPri osGetThreadPri(OSThread *thread) {
    if (thread == NULL) {
        thread = __osRunningThread;
    }
    return thread->priority;
}
