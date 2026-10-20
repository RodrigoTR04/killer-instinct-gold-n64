/* Pinned SM64-US SDK source; see docs/libultra_rebuild.md (T-080). */
#include "sdk/libultra.h"

u32 __osRdbSendMessage = 0;
u32 __osRdbWriteOK = 1;

void __osSyncPutChars(s32 type, s32 length, u8 *buf) {
    rdbPacket packet;
    s32 i;
    u32 mask;
    packet.type = type;
    packet.length = length;

    for (i = 0; i < length; i++) {
        packet.buf[i] = buf[i];
    }

    while (!__osAtomicDec(&__osRdbWriteOK)) {
        ;
    }

    mask = __osDisableInt();

    *(u32 *) RDB_BASE_REG = *(u32 *) &packet;
    while (!(__osGetCause() & CAUSE_IP6)) {
        ;
    }
    *(u32 *) RDB_READ_INTR_REG = 0;
    __osRdbWriteOK++;

    __osRestoreInt(mask);
}
