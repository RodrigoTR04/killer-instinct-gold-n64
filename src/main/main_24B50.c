/* T-035: complete C for src/main/main_24B50.c (libultra pfs, 2.0 era).
 * Verified: with this file as src/main/main_24B50.c and the object built with
 * `-O2 -mips1` (instead of -mips2), make reports the ROM and all three images OK.
 * Needs a Makefile per-object override, e.g.
 *   build/src/main/main_24B50.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
 */
#include "common.h"
typedef struct T035Pfs {
    /* 0x00 */ s32 status;
    /* 0x04 */ void *queue;
    /* 0x08 */ s32 channel;
} T035Pfs;

extern u8 D_8006F110; /* __osContLastCmd */
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 __osPfsGetStatus(void *queue, s32 channel);
s32 __osGetId(T035Pfs *pfs);
s32 osPfsChecker(T035Pfs *pfs);

s32 osPfsInit(void *queue, T035Pfs *pfs, s32 channel) {
    s32 ret;

    __osSiGetAccess();
    ret = __osPfsGetStatus(queue, channel);
    D_8006F110 = 0xFF;
    __osSiRelAccess();
    if (ret != 0) {
        return ret;
    }
    pfs->queue = queue;
    pfs->channel = channel;
    pfs->status = 0;
    ret = __osGetId(pfs);
    if (ret != 0) {
        return ret;
    }
    ret = osPfsChecker(pfs);
    pfs->status |= 1;
    return ret;
}

typedef struct T035ContStatus {
    /* 0x00 */ u16 type;
    /* 0x02 */ u8 status;
    /* 0x03 */ u8 errno;
} T035ContStatus;

extern u8 D_8006F080[];
void __osPfsRequestData(u8 command);
void __osPfsGetInitData(u8 *pattern, T035ContStatus *data);
s32 __osSiRawStartDma(s32 direction, void *dramAddr);
s32 osRecvMesg(void *mq, void * *msg, s32 flag);

s32 __osPfsGetStatus(void *queue, s32 channel) {
    s32 ret = 0;
    void * dummy;
    u8 pattern;
    T035ContStatus data[4];

    __osPfsRequestData(0xFF);
    ret = __osSiRawStartDma(1, D_8006F080);
    osRecvMesg(queue, &dummy, 1);
    ret = __osSiRawStartDma(0, D_8006F080);
    osRecvMesg(queue, &dummy, 1);
    __osPfsGetInitData(&pattern, data);
    if ((data[channel].status & 1) && (data[channel].status & 2)) {
        return 2;
    }
    if (data[channel].errno != 0 || !(data[channel].status & 1)) {
        return 1;
    }
    if (data[channel].status & 4) {
        return 4;
    }
    return ret;
}

typedef struct T035Dir {
    /* 0x00 */ u32 game_code;
    /* 0x04 */ u16 company_code;
    /* 0x06 */ u16 start_page;
    /* 0x08 */ u8 status;
    /* 0x09 */ s8 reserved;
    /* 0x0A */ u16 data_sum;
    /* 0x0C */ u8 ext_name[4];
    /* 0x10 */ u8 game_name[16];
} T035Dir;

typedef struct T035PfsFull {
    /* 0x00 */ s32 status;
    /* 0x04 */ void *queue;
    /* 0x08 */ s32 channel;
    /* 0x0C */ u8 pad0C[0x44];
    /* 0x50 */ s32 dir_size;
    /* 0x54 */ s32 inode_table;
    /* 0x58 */ s32 minode_table;
    /* 0x5C */ s32 dir_table;
} T035PfsFull;

s32 __osCheckId(T035PfsFull *pfs);
s32 __osContRamRead(void *mq, s32 channel, u16 address, u8 *buffer);

s32 osPfsFindFile(T035PfsFull *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 *file_no) {
    s32 j;
    s32 i;
    T035Dir dir;
    s32 ret = 0;
    s32 fail;

    if (__osCheckId(pfs) == 2) {
        return 2;
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&dir);
        if (ret != 0) {
            return ret;
        }
        if (dir.company_code == company_code && dir.game_code == game_code) {
            fail = 0;
            if (game_name != 0) {
                for (i = 0; i < 16; i++) {
                    if (dir.game_name[i] != game_name[i]) {
                        fail = 1;
                        break;
                    }
                }
            }
            if (ext_name != 0 && fail == 0) {
                for (i = 0; i < 4; i++) {
                    if (dir.ext_name[i] != ext_name[i]) {
                        fail = 1;
                        break;
                    }
                }
            }
            if (fail == 0) {
                *file_no = j;
                return ret;
            }
        }
    }
    *file_no = -1;
    return 5;
}

