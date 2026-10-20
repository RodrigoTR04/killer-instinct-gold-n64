/* T-035: complete C for src/main/main_24820.c (libultra pfs, 2.0 era).
 * Verified: with this file as src/main/main_24820.c and the object built with
 * `-O2 -mips1` (instead of -mips2), make reports the ROM and all three images OK.
 * Needs a Makefile per-object override, e.g.
 *   build/src/main/main_24820.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
 */
#include "common.h"
typedef struct T035PifRam {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} T035PifRam;

typedef struct T035ContStatus {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 status;
    /* 0x03 */ u8 errno;
} T035ContStatus;

extern T035PifRam D_8006F080; /* __osPfsPifRam */
extern u8 D_8006F110;   /* __osContLastCmd */
extern u8 D_8006F111;   /* __osMaxControllers */
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osSiRawStartDma(s32 direction, void *dramAddr);
s32 osRecvMesg(void *mq, void **msg, s32 flag);
void __osPfsRequestData(u8 command);
void __osPfsGetInitData(u8 *pattern, T035ContStatus *data);

s32 osPfsIsPlug(void *queue, u8 *pattern) {
    s32 ret = 0;
    void *dummy;
    u8 bitpattern;
    T035ContStatus data[4];
    s32 channel;
    u8 bits = 0;
    s32 crc_error_cnt = 3;

    __osSiGetAccess();
    do {
        __osPfsRequestData(0);
        ret = __osSiRawStartDma(1, &D_8006F080);
        osRecvMesg(queue, &dummy, 1);
        ret = __osSiRawStartDma(0, &D_8006F080);
        osRecvMesg(queue, &dummy, 1);
        __osPfsGetInitData(&bitpattern, data);
        for (channel = 0; channel < D_8006F111; channel++) {
            if ((data[channel].status & 4) == 0) {
                crc_error_cnt--;
                break;
            }
        }
        if (D_8006F111 == channel) {
            crc_error_cnt = 0;
        }
    } while (crc_error_cnt > 0);
    for (channel = 0; channel < D_8006F111; channel++) {
        if (data[channel].errno == 0 && (data[channel].status & 1) != 0) {
            bits |= (1 << channel);
        }
    }
    __osSiRelAccess();
    D_8006F110 = 0xFF;
    *pattern = bits;
    return ret;
}

typedef struct T035ContRequestFormat {
    /* 0x00 */ u8 dummy;
    /* 0x01 */ u8 txsize;
    /* 0x02 */ u8 rxsize;
    /* 0x03 */ u8 cmd;
    /* 0x04 */ u8 typeh;
    /* 0x05 */ u8 typel;
    /* 0x06 */ u8 status;
    /* 0x07 */ u8 dummy1;
} T035ContRequestFormat;

extern T035PifRam D_8006F080; /* __osPfsPifRam */
extern u8 D_8006F111;         /* __osMaxControllers */

void __osPfsRequestData(u8 command) {
    u8 *ptr;
    T035ContRequestFormat requestformat;
    s32 i;

    for (i = 0; i < 16; i++) {
        D_8006F080.ramarray[i] = 0;
    }
    D_8006F080.pifstatus = 1;
    ptr = (u8 *)&D_8006F080;
    requestformat.dummy = 0xFF;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = command;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;
    requestformat.dummy1 = 0xFF;
    for (i = 0; i < D_8006F111; i++) {
        *((T035ContRequestFormat *)ptr)++ = requestformat;
    }
    *ptr = 0xFE;
}

extern T035PifRam D_8006F080; /* __osPfsPifRam */
extern u8 D_8006F111;   /* __osMaxControllers */

void __osPfsGetInitData(u8 *pattern, T035ContStatus *data) {
    u8 *ptr;
    T035ContRequestFormat requestformat;
    s32 i;
    u8 bits = 0;

    ptr = (u8 *)&D_8006F080;
    for (i = 0; i < D_8006F111; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(T035ContRequestFormat *)ptr;
        data->errno = (requestformat.rxsize & 0xC0) >> 4;
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= (1 << i);
        }
    }
    *pattern = bits;
}

