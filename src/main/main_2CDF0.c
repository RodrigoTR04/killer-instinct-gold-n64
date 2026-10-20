/* T-035: complete C for src/main/main_2CDF0.c (libultra pfsfreeblocks.c).
 * Verified: with this file as src/main/main_2CDF0.c and the object built with
 * `-O2 -mips1` (instead of -mips2), make reports the ROM and all three images OK.
 * Needs a Makefile per-object override, e.g.
 *   build/src/main/main_2CDF0.c.o: CFLAGS := -c -G 0 -non_shared -Xcpluscomm -Wab,-r4300_mul -O2 -mips1 -32
 */
#include "common.h"
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

s32 __osCheckId(T035Pfs *pfs);
s32 __osPfsRWInode(T035Pfs *pfs, T035Inode *inode, u8 flag, u8 bank);

s32 osPfsFreeBlocks(T035Pfs *pfs, s32 *bytes_not_used) {
    s32 j;
    s32 pages = 0;
    T035Inode inode;
    s32 ret = 0;
    u8 bank;
    s32 offset;

    if ((pfs->status & 1) == 0) {
        return 5;
    }
    if (__osCheckId(pfs) == 2) {
        return 2;
    }
    for (bank = 0; bank < pfs->banks; bank++) {
        ret = __osPfsRWInode(pfs, &inode, 0, bank);
        if (ret != 0) {
            return ret;
        }
        offset = (bank > 0) ? 1 : pfs->inode_start_page;
        for (j = offset; j < 128; j++) {
            if (inode.inode_page[j].ipage == 3) {
                pages++;
            }
        }
    }
    *bytes_not_used = pages << 8;
    return 0;
}

