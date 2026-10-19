#include "common.h"

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

typedef struct T037Inode {
    /* 0x000 */ T037InodeUnit inode_page[128];
} T037Inode;

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

s32 func_80034630(T037Pfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 *file_no);
u16 func_8003B3E0(u8 *ptr, s32 length);
s32 func_8003BC0C(T037Pfs *pfs);
s32 func_8003BD24(T037Pfs *pfs, T037Inode *inode, u8 flag, u8 bank);
s32 func_8003BFC0(T037Pfs *pfs);
s32 func_8003C030(void *mq, s32 channel, u16 address, u8 *buffer);
s32 func_8003C3C0(void *mq, s32 channel, u16 address, u8 *buffer, s32 force);
s32 func_80036440(T037Pfs *pfs, T037Inode *inode, u8 start_page, u16 *sum, u8 bank, T037InodeUnit *last_page, s32 flag);
s32 func_80036644(T037Pfs *pfs, u8 page_no, u16 *sum, u8 bank);

s32 func_800361C0(T037Pfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name) {
    s32 file_no;
    s32 ret;
    s32 j;
    T037Inode inode;
    T037Dir dir;
    u16 sum = 0;
    T037InodeUnit last_page;
    u8 bank;
    u8 startpage;

    if (company_code == 0 || game_code == 0) {
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
    ret = func_80034630(pfs, company_code, game_code, game_name, ext_name, &file_no);
    if (ret != 0) {
        return ret;
    }
    if (file_no == -1) {
        return 5;
    }
    ret = func_8003C030(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir);
    if (ret != 0) {
        return ret;
    }
    startpage = dir.start_page.inode_t.page;
    for (bank = dir.start_page.inode_t.bank; bank < pfs->banks;) {
        ret = func_8003BD24(pfs, &inode, 0, bank);
        if (ret != 0) {
            return ret;
        }
        ret = func_80036440(pfs, &inode, startpage, &sum, bank, &last_page, 1);
        if (ret != 0) {
            return ret;
        }
        ret = func_8003BD24(pfs, &inode, 1, bank);
        if (ret != 0) {
            return ret;
        }
        if (last_page.ipage == 1) {
            break;
        }
        bank = last_page.inode_t.bank;
        startpage = last_page.inode_t.page;
    }
    if (bank >= pfs->banks) {
        return 3;
    }
    dir.game_code = 0;
    dir.company_code = 0;
    dir.start_page.ipage = 0;
    dir.data_sum = 0;
    for (j = 0; j < 16; j++) {
        dir.game_name[j] = 0;
    }
    for (j = 0; j < 4; j++) {
        dir.ext_name[j] = 0;
    }
    dir.status = 0;
    ret = func_8003C3C0(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir, 0);
    return ret;
}

s32 func_80036440(T037Pfs *pfs, T037Inode *inode, u8 start_page, u16 *sum, u8 bank, T037InodeUnit *last_page, s32 flag) {
    T037InodeUnit next_page;
    T037InodeUnit old_page;
    s32 ret;
    s32 lim;

    next_page = inode->inode_page[start_page];
    if (next_page.ipage != 1) {
        lim = (next_page.inode_t.bank > 0) ? 1 : pfs->inode_start_page;
    } else {
        lim = (bank > 0) ? 1 : pfs->inode_start_page;
    }
    if (next_page.inode_t.page < lim && next_page.ipage != 1) {
        return 3;
    }
    *last_page = next_page;
    if (flag == 1) {
        inode->inode_page[start_page].ipage = 3;
    }
    ret = func_80036644(pfs, start_page, sum, bank);
    if (ret != 0) {
        return ret;
    }
    if (next_page.ipage == 1) {
        return 0;
    }
    while (next_page.ipage >= pfs->inode_start_page) {
        old_page = next_page;
        next_page = inode->inode_page[next_page.inode_t.page];
        inode->inode_page[old_page.inode_t.page].ipage = 3;
        ret = func_80036644(pfs, old_page.inode_t.page, sum, bank);
        if (ret != 0) {
            return ret;
        }
        if (next_page.inode_t.bank != bank) {
            break;
        }
    }
    if (next_page.ipage >= pfs->inode_start_page) {
        inode->inode_page[next_page.inode_t.page].ipage = 3;
    }
    *last_page = next_page;
    return 0;
}

s32 func_80036644(T037Pfs *pfs, u8 page_no, u16 *sum, u8 bank) {
    s32 i;
    s32 ret;
    u8 buf[32];

    pfs->activebank = bank;
    ret = func_8003BFC0(pfs);
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < 8; i++) {
        ret = func_8003C030(pfs->queue, pfs->channel, page_no * 8 + i, buf);
        if (ret != 0) {
            pfs->activebank = 0;
            func_8003BFC0(pfs);
            return ret;
        }
        *sum = *sum + func_8003B3E0(buf, 32);
    }
    pfs->activebank = 0;
    ret = func_8003BFC0(pfs);
    return ret;
}
