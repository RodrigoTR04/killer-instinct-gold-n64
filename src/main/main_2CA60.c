/* T-035: complete C for src/main/main_2CA60.c (libultra 2.0-era contramwrite.c).
 * Verified: with this file as src/main/main_2CA60.c and the object built with
 * `-O2 -mips1` (instead of -mips2), make reports the ROM and all three images OK.
 * Needs a Makefile per-object override, e.g.
 *   build/src/main/main_2CA60.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
 */
#include "common.h"
typedef struct T035PifRam {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} T035PifRam;

typedef struct T035ContRamReadFormat {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 addrh;
    /* 0x05 */ u8 addrl;
    /* 0x06 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
    /* 0x27 */ u8 pad27;
} T035ContRamReadFormat;

extern T035PifRam D_8006F080; /* __osPfsPifRam */
extern u8 D_8006F110;         /* __osContLastCmd */
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osSiRawStartDma(s32 direction, void *dramAddr);
s32 osRecvMesg(void *mq, void **msg, s32 flag);
u8 __osContDataCrc(u8 *data);
s32 __osPfsGetStatus(void *queue, s32 channel);
void __osPackRamWriteData(s32 channel, u16 address, u8 *buffer);

s32 __osContRamWrite(void *mq, s32 channel, u16 address, u8 *buffer, s32 force) {
    s32 ret;
    s32 i;
    u8 *ptr;
    T035ContRamReadFormat ramwriteformat;
    s32 retry;

    ret = 0;
    ptr = (u8 *)&D_8006F080;
    retry = 2;
    if (force != 1 && address < 7 && address != 0) {
        return 0;
    }
    __osSiGetAccess();
    D_8006F110 = 3;
    __osPackRamWriteData(channel, address, buffer);
    ret = __osSiRawStartDma(1, &D_8006F080);
    osRecvMesg(mq, 0, 1);
    do {
        for (i = 0; i <= 15; i++) {
            D_8006F080.ramarray[i] = 0xFF;
        }
        D_8006F080.pifstatus = 0;
        ret = __osSiRawStartDma(0, &D_8006F080);
        osRecvMesg(mq, 0, 1);
        ptr = (u8 *)&D_8006F080;
        if (channel != 0) {
            for (i = 0; i < channel; i++) {
                ptr++;
            }
        }
        ramwriteformat = *(T035ContRamReadFormat *)ptr;
        ret = (ramwriteformat.rxsize & 0xC0) >> 4;
        if (ret == 0) {
            if (__osContDataCrc(buffer) != ramwriteformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }
                ret = 4;
            }
        }
    } while (ret == 4 && retry-- >= 0);
    __osSiRelAccess();
    return ret;
}

typedef struct T035ContRamPackFormat {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u16 address;
    /* 0x06 */ u8 data[32];
    /* 0x26 */ u8 datacrc;
} T035ContRamPackFormat;

extern T035PifRam D_8006F080; /* __osPfsPifRam */
u8 __osContAddressCrc(u16 addr);

void __osPackRamWriteData(s32 channel, u16 address, u8 *buffer) {
    u8 *ptr;
    T035ContRamPackFormat ramwriteformat;
    s32 i;

    ptr = (u8 *)D_8006F080.ramarray;
    for (i = 0; i < 16; i++) {
        D_8006F080.ramarray[i] = 0;
    }
    D_8006F080.pifstatus = 1;
    ramwriteformat.dummy = 0xFF;
    ramwriteformat.txsize = 0x23;
    ramwriteformat.rxsize = 1;
    ramwriteformat.cmd = 3;
    ramwriteformat.address = __osContAddressCrc(address) | (address << 5);
    ramwriteformat.datacrc = 0xFF;
    for (i = 0; i < 32; i++) {
        ramwriteformat.data[i] = *buffer++;
    }
    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(T035ContRamPackFormat *)ptr = ramwriteformat;
    ptr += sizeof(T035ContRamPackFormat);
    ptr[0] = 0xFE;
}

