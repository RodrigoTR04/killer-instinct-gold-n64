/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

s32 osPiRawStartDma(s32 dir, u32 cart_addr, void *dram_addr, size_t size) {
    register u32 status;

    WAIT_ON_IO_BUSY(status);

    IO_WRITE(PI_DRAM_ADDR_REG, osVirtualToPhysical(dram_addr));

    IO_WRITE(PI_CART_ADDR_REG, K1_TO_PHYS((uintptr_t) osRomBase | cart_addr));

    switch (dir) {
        case OS_READ:
            IO_WRITE(PI_WR_LEN_REG, size - 1);
            break;
        case OS_WRITE:
            IO_WRITE(PI_RD_LEN_REG, size - 1);
            break;
        default:
            return -1;
    }
    return 0;
}
