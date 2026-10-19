/* DRAFT. Remaining diff: none under IDO 5.3 -O2 -mips1 (T-035: libultra osPfsNumFiles; byte-identical standalone). Needs a per-object `-mips1` CFLAGS override for build/src/main/main_26480.c.o. */

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

s32 func_8003BC0C(T035Pfs *pfs);
s32 func_8003BFC0(T035Pfs *pfs);
s32 func_8003C030(void *mq, s32 channel, u16 address, u8 *buffer);

s32 func_80035DE0(T035Pfs *pfs, s32 *max_files, s32 *files_used) {
    s32 j;
    s32 ret;
    T035Dir dir;
    s32 files = 0;

    if ((pfs->status & 1) == 0) {
        return 5;
    }
    if (func_8003BC0C(pfs) == 2) {
        return 2;
    }
    if (pfs->activebank != 0) {
        pfs->activebank = 0;
        ret = func_8003BFC0(pfs);
        if (ret != 0) {
            return ret;
        }
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = func_8003C030(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&dir);
        if (ret != 0) {
            return ret;
        }
        if (dir.company_code != 0 && dir.game_code != 0) {
            files++;
        }
    }
    *files_used = files;
    *max_files = pfs->dir_size;
    return 0;
}
