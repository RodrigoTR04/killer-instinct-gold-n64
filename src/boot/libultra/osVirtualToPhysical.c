/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

uintptr_t osVirtualToPhysical(void *addr) {
    if (IS_KSEG0(addr)) {
        return K0_TO_PHYS(addr);
    } else if (IS_KSEG1(addr)) {
        return (K1_TO_PHYS(addr));
    } else {
        return __osProbeTLB(addr);
    }
}
