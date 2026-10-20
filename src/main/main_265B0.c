#include "common.h"

/* libultra 2.0 (pre-J) pfsfilestate.c, built -O2 -mips1 */
typedef struct T037Pfs {
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
} T037Pfs;

typedef union T037InodeUnit {
    struct {
        u8 bank;
        u8 page;
    } inode_t;
    u16 ipage;
} T037InodeUnit;

typedef struct T037Dir {
    /* 0x00 */ u32 game_code;
    /* 0x04 */ u16 company_code;
    /* 0x06 */ T037InodeUnit start_page;
    /* 0x08 */ u8 status;
    /* 0x09 */ s8 reserved;
    /* 0x0A */ u16 data_sum;
    /* 0x0C */ u8 ext_name[4];
    /* 0x10 */ u8 game_name[16];
} T037Dir;

typedef struct T037Inode {
    /* 0x000 */ T037InodeUnit inode_page[128];
} T037Inode;

typedef struct T037PfsState {
    /* 0x00 */ s32 file_size;
    /* 0x04 */ u32 game_code;
    /* 0x08 */ u16 company_code;
    /* 0x0A */ char ext_name[4];
    /* 0x0E */ char game_name[16];
} T037PfsState;

s32 func_8003BFC0(T037Pfs *pfs);
s32 func_8003BD24(T037Pfs *pfs, T037Inode *inode, u8 flag, u8 bank);
s32 func_8003C030(void *mq, s32 channel, u16 address, u8 *buffer);

s32 func_80035F10(T037Pfs *pfs, s32 file_no, T037PfsState *state) {
    s32 ret;
    int pages;
    T037Inode inode;
    T037Dir dir;
    T037InodeUnit next_page;
    int j;
    u8 bank;
    u8 start_page;

    if (file_no >= pfs->dir_size || file_no < 0) {
        return 5;
    }
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
    ret = func_8003C030(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir);
    if (ret != 0) {
        return ret;
    }
    if (dir.company_code == 0 || dir.game_code == 0) {
        return 5;
    }
    if (dir.start_page.ipage < pfs->inode_start_page) {
        return 3;
    }
    pages = 0;
    start_page = dir.start_page.inode_t.page;
    bank = dir.start_page.inode_t.bank;
    while (bank < pfs->banks) {
        ret = func_8003BD24(pfs, &inode, 0, bank);
        if (ret != 0) {
            return ret;
        }
        next_page = inode.inode_page[start_page];
        pages++;
        while (next_page.ipage >= pfs->inode_start_page) {
            pages++;
            next_page = inode.inode_page[next_page.inode_t.page];
            if (next_page.inode_t.bank != bank) {
                bank = next_page.inode_t.bank;
                start_page = next_page.inode_t.page;
                break;
            }
        }
        if (next_page.ipage == 1) {
            break;
        }
    }
    if (next_page.ipage != 1) {
        return 3;
    }
    state->file_size = pages * 256;
    state->company_code = dir.company_code;
    state->game_code = dir.game_code;
    for (j = 0; j < 16; j++) {
        state->game_name[j] = dir.game_name[j];
    }
    for (j = 0; j < 4; j++) {
        state->ext_name[j] = dir.ext_name[j];
    }
    return 0;
}
