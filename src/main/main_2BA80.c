/* T-035: complete C for src/main/main_2BA80.c (libultra pfs, 2.0 era).
 * Verified: with this file as src/main/main_2BA80.c and the object built with
 * `-O2 -mips1` (instead of -mips2), make reports the ROM and all three images OK.
 * Needs a Makefile per-object override, e.g.
 *   build/src/main/main_2BA80.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
 */
#include "common.h"
u16 __osSumcalc(u8 *ptr, s32 length) {
    s32 i;
    u32 sum = 0;
    u8 *tmp = ptr;

    for (i = 0; i < length; i++) {
        sum += *tmp++;
        sum = sum & 0xFFFF;
    }
    return sum;
}

s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum) {
    u16 data = 0;
    u32 j;

    *csum = *icsum = 0;
    for (j = 0; j < 28; j += 2) {
        data = *(u16 *)((u32)ptr + j);
        *csum += data;
        *icsum += ~data;
    }
    return 0;
}

typedef struct T035PackId {
    /* 0x00 */ u32 repaired;
    /* 0x04 */ u32 random;
    /* 0x08 */ u64 serial_mid;
    /* 0x10 */ u64 serial_low;
    /* 0x18 */ u16 deviceid;
    /* 0x1A */ u8 banks;
    /* 0x1B */ u8 version;
    /* 0x1C */ u16 checksum;
    /* 0x1E */ u16 inverted_checksum;
} T035PackId;

typedef struct T035Pfs {
    /* 0x00 */ s32 status;
    /* 0x04 */ void *queue;
    /* 0x08 */ s32 channel;
    /* 0x0C */ u8 id[32];
    /* 0x2C */ u8 label[32];
    /* 0x4C */ s32 version;
    /* 0x50 */ s32 dir_size;
    /* 0x54 */ s32 inode_table;
    /* 0x58 */ s32 minode_table;
    /* 0x5C */ s32 dir_table;
    /* 0x60 */ s32 inode_start_page;
    /* 0x64 */ u8 banks;
    /* 0x65 */ u8 activebank;
} T035Pfs;

u32 osGetCount(void);
s32 __osIdCheckSum(u16 *ptr, u16 *csum, u16 *icsum);
s32 __osPfsSelectBank(T035Pfs *pfs);
s32 __osContRamRead(void *mq, s32 channel, u16 address, u8 *buffer);
s32 __osContRamWrite(void *mq, s32 channel, u16 address, u8 *buffer, s32 force);

s32 __osRepairPackId(T035Pfs *pfs, T035PackId *badid, T035PackId *newid) {
    s32 ret = 0;
    u8 temp[32];
    u8 comp[32];
    u8 mask = 0;
    s32 i;
    s32 j;
    u16 index[4];

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    newid->repaired = -1;
    newid->random = osGetCount();
    newid->serial_mid = badid->serial_mid;
    newid->serial_low = badid->serial_low;
    j = 0;
    do {
        pfs->activebank = j;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, temp);
        if (ret != 0) {
            return ret;
        }
        temp[0] = j | 0x80;
        for (i = 1; i < 32; i++) {
            temp[i] = ~temp[i];
        }
        ret = __osContRamWrite(pfs->queue, pfs->channel, 0, temp, 0);
        if (ret != 0) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 0, comp);
        if (ret != 0) {
            return ret;
        }
        for (i = 0; i < 32; i++) {
            if (comp[i] != temp[i]) {
                break;
            }
        }
        if (i != 32) {
            break;
        }
        if (j > 0) {
            pfs->activebank = 0;
            ret = __osPfsSelectBank(pfs);
            if (ret != 0) {
                return ret;
            }
            ret = __osContRamRead(pfs->queue, pfs->channel, 0, temp);
            if (ret != 0) {
                return ret;
            }
            if (temp[0] != 0x80) {
                break;
            }
        }
        j++;
    } while (j < 62);
    pfs->activebank = 0;
    ret = __osPfsSelectBank(pfs);
    if (ret != 0) {
        return ret;
    }
    mask = (j > 0) ? 1 : 0;
    newid->deviceid = (badid->deviceid & 0xFFFE) | mask;
    newid->banks = j;
    newid->version = badid->version;
    __osIdCheckSum((u16 *)newid, &newid->checksum, &newid->inverted_checksum);
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 0; i < 4; i++) {
        ret = __osContRamWrite(pfs->queue, pfs->channel, index[i], (u8 *)newid, 1);
        if (ret != 0) {
            return ret;
        }
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < 32; i++) {
        if (temp[i] != ((u8 *)newid)[i]) {
            return 10;
        }
    }
    return 0;
}

s32 __osCheckPackId(T035Pfs *pfs, T035PackId *temp) {
    u16 index[4];
    s32 ret = 0;
    u16 sum;
    u16 isum;
    s32 i;
    s32 j;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    index[0] = 1;
    index[1] = 3;
    index[2] = 4;
    index[3] = 6;
    for (i = 1; i < 4; i++) {
        ret = __osContRamRead(pfs->queue, pfs->channel, index[i], (u8 *)temp);
        if (ret != 0) {
            return ret;
        }
        __osIdCheckSum((u16 *)temp, &sum, &isum);
        if (temp->checksum == sum && temp->inverted_checksum == isum) {
            break;
        }
    }
    if (i == 4) {
        return 10;
    }
    for (j = 0; j < 4; j++) {
        if (j != i) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, index[j], (u8 *)temp, 1);
            if (ret != 0) {
                return ret;
            }
        }
    }
    return 0;
}

s32 __osRepairPackId(T035Pfs *pfs, T035PackId *badid, T035PackId *newid);
s32 __osCheckPackId(T035Pfs *pfs, T035PackId *temp);

s32 __osGetId(T035Pfs *pfs) {
    s32 k;
    u16 sum;
    u16 isum;
    u8 temp[32];
    T035PackId newid;
    s32 ret;
    T035PackId *id;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
    if (ret != 0) {
        return ret;
    }
    __osIdCheckSum((u16 *)temp, &sum, &isum);
    id = (T035PackId *)temp;
    if (id->checksum != sum || id->inverted_checksum != isum) {
        ret = __osCheckPackId(pfs, id);
        if (ret == 10) {
            ret = __osRepairPackId(pfs, id, &newid);
            if (ret != 0) {
                return ret;
            }
            id = &newid;
        } else if (ret != 0) {
            return ret;
        }
    }
    if ((id->deviceid & 1) == 0) {
        ret = __osRepairPackId(pfs, id, &newid);
        if (ret != 0) {
            return ret;
        }
        id = &newid;
        if ((id->deviceid & 1) == 0) {
            return 11;
        }
    }
    for (k = 0; k < 32; k++) {
        pfs->id[k] = *(u8 *)((u32)id + k);
    }
    pfs->version = id->version;
    pfs->banks = id->banks;
    pfs->inode_start_page = 1 + 2 + (2 * pfs->banks);
    pfs->dir_size = 2 * 8;
    pfs->inode_table = 1 * 8;
    pfs->minode_table = (1 + pfs->banks) * 8;
    pfs->dir_table = pfs->minode_table + (pfs->banks * 8);
    ret = __osContRamRead(pfs->queue, pfs->channel, 7, pfs->label);
    if (ret != 0) {
        return ret;
    }
    return 0;
}

s32 __osCheckId(T035Pfs *pfs) {
    s32 k;
    u8 temp[32];
    s32 ret;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
    if (ret != 0) {
        if (ret != 2) {
            return ret;
        }
        ret = __osContRamRead(pfs->queue, pfs->channel, 1, temp);
        if (ret != 0) {
            return ret;
        }
    }
    for (k = 0; k < 32; k++) {
        if (pfs->id[k] != temp[k]) {
            return 2;
        }
    }
    return 0;
}

typedef union T035InodeUnit {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
} T035InodeUnit;

typedef struct T035Inode {
    /* 0x000 */ T035InodeUnit inode_page[128];
} T035Inode;

u16 __osSumcalc(u8 *ptr, s32 length);

s32 __osPfsRWInode(T035Pfs *pfs, T035Inode *inode, u8 flag, u8 bank) {
    u8 sum;
    s32 j;
    s32 ret;
    s32 offset;
    u8 *addr;

    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = __osPfsSelectBank(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    if (bank > 0) {
        offset = 1;
    } else {
        offset = pfs->inode_start_page;
    }
    if (flag == 1) {
        inode->inode_page[0].inode_t.page = __osSumcalc((u8 *)(inode->inode_page + offset), (128 - offset) * 2);
    }
    for (j = 0; j < 8; j++) {
        addr = (u8 *)inode->inode_page + j * 32;
        if (flag == 1) {
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
        } else {
            ret = __osContRamRead(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr);
        }
        if (ret != 0) {
            return ret;
        }
    }
    if (flag == 0) {
        sum = __osSumcalc((u8 *)(inode->inode_page + offset), (128 - offset) * 2);
        if (sum != inode->inode_page[0].inode_t.page) {
            for (j = 0; j < 8; j++) {
                addr = (u8 *)inode->inode_page + j * 32;
                ret = __osContRamRead(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr);
            }
            if (sum != inode->inode_page[0].inode_t.page) {
                return 3;
            }
            for (j = 0; j < 8; j++) {
                addr = (u8 *)inode->inode_page + j * 32;
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->inode_table + bank * 8 + j, addr, 0);
            }
        } else {
            for (j = 0; j < 8; j++) {
                addr = (u8 *)inode->inode_page + j * 32;
                ret = __osContRamWrite(pfs->queue, pfs->channel, pfs->minode_table + bank * 8 + j, addr, 0);
            }
        }
    }
    return 0;
}

s32 __osPfsSelectBank(T035Pfs *pfs) {
    u8 temp[32];
    s32 i;
    s32 ret = 0;

    for (i = 0; i < 32; i++) {
        temp[i] = pfs->activebank;
    }
    ret = __osContRamWrite(pfs->queue, pfs->channel, 0x400, temp, 0);
    return ret;
}

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
void __osPackRamReadData(s32 channel, u16 address);

s32 __osContRamRead(void *mq, s32 channel, u16 address, u8 *buffer) {
    s32 ret;
    s32 i;
    u8 *ptr;
    T035ContRamReadFormat ramreadformat;
    s32 retry;

    ret = 0;
    ptr = (u8 *)&D_8006F080;
    retry = 2;
    __osSiGetAccess();
    D_8006F110 = 2;
    __osPackRamReadData(channel, address);
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
        ramreadformat = *(T035ContRamReadFormat *)ptr;
        ret = (ramreadformat.rxsize & 0xC0) >> 4;
        if (ret == 0) {
            if (__osContDataCrc(ramreadformat.data) != ramreadformat.datacrc) {
                ret = __osPfsGetStatus(mq, channel);
                if (ret != 0) {
                    __osSiRelAccess();
                    return ret;
                }
                ret = 4;
            } else {
                for (i = 0; i <= 31; i++) {
                    *buffer++ = ramreadformat.data[i];
                }
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

void __osPackRamReadData(s32 channel, u16 address) {
    u8 *ptr;
    T035ContRamPackFormat ramreadformat;
    s32 i;

    ptr = (u8 *)D_8006F080.ramarray;
    for (i = 0; i < 16; i++) {
        D_8006F080.ramarray[i] = 0;
    }
    D_8006F080.pifstatus = 1;
    ramreadformat.dummy = 0xFF;
    ramreadformat.txsize = 3;
    ramreadformat.rxsize = 0x21;
    ramreadformat.cmd = 2;
    ramreadformat.address = __osContAddressCrc(address) | (address << 5);
    ramreadformat.datacrc = 0xFF;
    for (i = 0; i < 32; i++) {
        ramreadformat.data[i] = 0xFF;
    }
    if (channel != 0) {
        for (i = 0; i < channel; i++) {
            *ptr++ = 0;
        }
    }
    *(T035ContRamPackFormat *)ptr = ramreadformat;
    ptr += sizeof(T035ContRamPackFormat);
    ptr[0] = 0xFE;
}

