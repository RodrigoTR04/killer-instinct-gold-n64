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

typedef struct T037InodeCache {
    /* 0x000 */ T037Inode inode;
    /* 0x100 */ u8 bank;
    /* 0x101 */ u8 map[256];
} T037InodeCache;

s32 func_80034630(T037Pfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 *file_no);
s32 func_8003BA08(T037Pfs *pfs);
s32 func_8003BC0C(T037Pfs *pfs);
s32 func_8003BD24(T037Pfs *pfs, T037Inode *inode, u8 flag, u8 bank);
s32 func_8003BFC0(T037Pfs *pfs);
s32 func_8003C030(void *mq, s32 channel, u16 address, u8 *buffer);
s32 func_8003C3C0(void *mq, s32 channel, u16 address, u8 *buffer, s32 force);
s32 func_80034DBC(T037Pfs *pfs, T037InodeCache *cache);
s32 func_800350A0(T037Pfs *pfs, T037InodeUnit fpage, T037InodeCache *cache);
s32 func_8003C750(T037Pfs *pfs, s32 *bytes_not_used);
s32 func_80035A84(T037Pfs *pfs, T037Inode *inode, s32 file_size_in_pages, s32 *first_page, u8 bank, s32 *decleared, s32 *last_page);
s32 func_80035C84(T037Pfs *pfs, s32 page_no, u8 *data, u8 bank);

s32 func_800347D0(T037Pfs *pfs) {
    s32 j;
    s32 ret;
    T037InodeUnit next_page;
    T037Inode checked_inode;
    T037Inode tmp_inode;
    T037Dir tmp_dir;
    T037InodeUnit file_next_node[16];
    T037InodeCache cache;
    s32 fixed = 0;
    u8 bank;
    s32 cc;
    s32 cl;
    s32 offset;

    ret = func_8003BC0C(pfs);
    if (ret == 2) {
        ret = func_8003BA08(pfs);
    }
    if (ret != 0) {
        return ret;
    }
    ret = func_80034DBC(pfs, &cache);
    if (ret != 0) {
        return ret;
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = func_8003C030(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir);
        if (ret != 0) {
            return ret;
        }
        if (tmp_dir.company_code != 0 && tmp_dir.game_code != 0) {
            cc = 0;
            next_page = tmp_dir.start_page;
            cl = 0;
            bank = 0xFF;
            while (next_page.ipage >= pfs->inode_start_page && next_page.inode_t.bank < pfs->banks
                   && next_page.inode_t.page > 0 && next_page.inode_t.page < 128) {
                if (bank != next_page.inode_t.bank) {
                    bank = next_page.inode_t.bank;
                    ret = func_8003BD24(pfs, &tmp_inode, 0, bank);
                    if (ret != 0 && ret != 3) {
                        return ret;
                    }
                }
                if ((cc = func_800350A0(pfs, next_page, &cache) - cl) != 0) {
                    break;
                }
                cl = 1;
                next_page = tmp_inode.inode_page[next_page.inode_t.page];
            }
            if (cc != 0 || next_page.ipage != 1) {
                tmp_dir.company_code = 0;
                tmp_dir.game_code = 0;
                tmp_dir.start_page.ipage = 0;
                tmp_dir.status = 0;
                tmp_dir.data_sum = 0;
                if (pfs->activebank != 0) {
                    pfs->activebank = 0;
                    ret = func_8003BFC0(pfs);
                    if (ret != 0) {
                        return ret;
                    }
                }
                ret = func_8003C3C0(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir, 0);
                if (ret != 0) {
                    return ret;
                }
                fixed++;
            }
        } else if (tmp_dir.company_code != 0 || tmp_dir.game_code != 0) {
            tmp_dir.company_code = 0;
            tmp_dir.game_code = 0;
            tmp_dir.start_page.ipage = 0;
            tmp_dir.status = 0;
            tmp_dir.data_sum = 0;
            if (pfs->activebank != 0) {
                pfs->activebank = 0;
                ret = func_8003BFC0(pfs);
                if (ret != 0) {
                    return ret;
                }
            }
            ret = func_8003C3C0(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir, 0);
            if (ret != 0) {
                return ret;
            }
            fixed++;
        }
    }
    for (j = 0; j < pfs->dir_size; j++) {
        ret = func_8003C030(pfs->queue, pfs->channel, pfs->dir_table + j, (u8 *)&tmp_dir);
        if (ret != 0) {
            return ret;
        }
        if (tmp_dir.company_code != 0 && tmp_dir.game_code != 0
            && tmp_dir.start_page.ipage >= (u16)pfs->inode_start_page) {
            file_next_node[j].ipage = tmp_dir.start_page.ipage;
        } else {
            file_next_node[j].ipage = 0;
        }
    }
    for (bank = 0; bank < pfs->banks; bank++) {
        ret = func_8003BD24(pfs, &tmp_inode, 0, bank);
        if (ret != 0 && ret != 3) {
            return ret;
        }
        offset = (bank > 0) ? 1 : pfs->inode_start_page;
        for (j = 0; j < offset; j++) {
            checked_inode.inode_page[j].ipage = tmp_inode.inode_page[j].ipage;
        }
        for (; j < 128; j++) {
            checked_inode.inode_page[j].ipage = 3;
        }
        for (j = 0; j < pfs->dir_size; j++) {
            while (file_next_node[j].inode_t.bank == bank
                   && file_next_node[j].ipage >= (u16)pfs->inode_start_page) {
                u8 pp = file_next_node[j].inode_t.page;
                file_next_node[j] = checked_inode.inode_page[pp] = tmp_inode.inode_page[pp];
            }
        }
        ret = func_8003BD24(pfs, &checked_inode, 1, bank);
        if (ret != 0) {
            return ret;
        }
    }
    if (fixed) {
        pfs->status |= 2;
    } else {
        pfs->status &= ~2;
    }
    return 0;
}

s32 func_80034DBC(T037Pfs *pfs, T037InodeCache *cache) {
    s32 i;
    s32 n;
    s32 offset;
    u8 bank;
    T037InodeUnit tpage;
    T037Inode tmp_inode;
    s32 ret;

    for (i = 0; i < 256; i++) {
        cache->map[i] = 0;
    }
    cache->bank = 0xFF;
    for (bank = 0; bank < pfs->banks; bank++) {
        offset = (bank > 0) ? 1 : pfs->inode_start_page;
        ret = func_8003BD24(pfs, &tmp_inode, 0, bank);
        if (ret != 0 && ret != 3) {
            return ret;
        }
        for (i = offset; i < 128; i++) {
            tpage = tmp_inode.inode_page[i];
            if (tpage.ipage >= pfs->inode_start_page && tpage.inode_t.bank != bank) {
                n = (tpage.inode_t.page / 4) + 32 * (tpage.inode_t.bank % 8);
                cache->map[n] |= 1 << (bank % 8);
            }
        }
    }
    return 0;
}

s32 func_800350A0(T037Pfs *pfs, T037InodeUnit fpage, T037InodeCache *cache) {
    s32 j;
    s32 n;
    s32 hit = 0;
    u8 bank;
    s32 offset;
    s32 ret = 0;

    n = (fpage.inode_t.page / 4) + 32 * (fpage.inode_t.bank % 8);
    for (bank = 0; bank < pfs->banks; bank++) {
        offset = (bank > 0) ? 1 : pfs->inode_start_page;
        if (bank == fpage.inode_t.bank || (cache->map[n] & (1 << (bank % 8)))) {
            if (bank != cache->bank) {
                ret = func_8003BD24(pfs, &cache->inode, 0, bank);
                if (ret != 0 && ret != 3) {
                    return ret;
                }
                cache->bank = bank;
            }
            for (j = offset; hit < 2 && j < 128; j++) {
                if (cache->inode.inode_page[j].ipage == fpage.ipage) {
                    hit++;
                }
            }
            if (hit > 1) {
                return 2;
            }
        }
    }
    return hit;
}

s32 func_80035240(T037Pfs *pfs, u8 *bank, T037Inode *inode, T037InodeUnit *page) {
    s32 ret;

    if (page->inode_t.bank != *bank) {
        *bank = page->inode_t.bank;
        ret = func_8003BD24(pfs, inode, 0, *bank);
        if (ret != 0) {
            return ret;
        }
    }
    *page = inode->inode_page[page->inode_t.page];
    if (page->ipage < pfs->inode_start_page || page->inode_t.bank >= pfs->banks || page->inode_t.page <= 0
        || page->inode_t.page >= 128) {
        if (page->ipage == 1) {
            return 5;
        }
        return 3;
    }
    return 0;
}

s32 func_80035320(T037Pfs *pfs, s32 file_no, u8 flag, s32 offset, s32 size_in_bytes, u8 *data_buffer) {
    s32 ret;
    T037Dir dir;
    T037Inode inode;
    T037InodeUnit cur_page;
    s32 cur_block;
    s32 siz;
    u8 *buffer;
    u8 bank;
    u16 blockno;

    if (file_no >= pfs->dir_size || file_no < 0) {
        return 5;
    }
    if (size_in_bytes <= 0 || (size_in_bytes % 32) != 0) {
        return 5;
    }
    if (offset < 0 || (offset % 32) != 0) {
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
    if (dir.start_page.ipage < pfs->inode_start_page || dir.start_page.inode_t.bank >= pfs->banks
        || dir.start_page.inode_t.page <= 0 || dir.start_page.inode_t.page >= 128) {
        if (dir.start_page.ipage == 1) {
            return 5;
        }
        return 3;
    }
    if (flag == 0 && (dir.status & 2) == 0) {
        return 6;
    }
    bank = 0xFF;
    cur_block = offset / 32;
    cur_page = dir.start_page;
    while (cur_block >= 8) {
        ret = func_80035240(pfs, &bank, &inode, &cur_page);
        if (ret != 0) {
            return ret;
        }
        cur_block -= 8;
    }
    siz = size_in_bytes / 32;
    buffer = data_buffer;
    while (siz > 0) {
        if (cur_block == 8) {
            ret = func_80035240(pfs, &bank, &inode, &cur_page);
            if (ret != 0) {
                return ret;
            }
            cur_block = 0;
        }
        if (pfs->activebank != cur_page.inode_t.bank) {
            pfs->activebank = cur_page.inode_t.bank;
            ret = func_8003BFC0(pfs);
            if (ret != 0) {
                return ret;
            }
        }
        blockno = cur_page.inode_t.page * 8 + cur_block;
        if (flag == 0) {
            ret = func_8003C030(pfs->queue, pfs->channel, blockno, buffer);
        } else {
            ret = func_8003C3C0(pfs->queue, pfs->channel, blockno, buffer, 0);
        }
        if (ret != 0) {
            return ret;
        }
        buffer += 32;
        cur_block++;
        siz--;
    }
    if (flag == 1 && (dir.status & 2) == 0) {
        dir.status |= 2;
        pfs->activebank = 0;
        ret = func_8003BFC0(pfs);
        if (ret != 0) {
            return ret;
        }
        ret = func_8003C3C0(pfs->queue, pfs->channel, pfs->dir_table + file_no, (u8 *)&dir, 0);
        if (ret != 0) {
            return ret;
        }
    }
    return 0;
}

s32 func_80035690(T037Pfs *pfs, u16 company_code, u32 game_code, u8 *game_name, u8 *ext_name, s32 file_size_in_bytes, s32 *file_no) {
    s32 start_page;
    s32 decleared;
    s32 last_page;
    s32 old_last_page = 0;
    s32 ret = 0;
    s32 file_size_in_pages;
    u8 pad[4];
    T037Inode inode;
    T037Inode backup_inode;
    T037Dir dir;
    u8 bank;
    u8 old_bank = 0;
    s32 firsttime = 0;
    s32 bytes;
    T037InodeUnit fpage;
    s32 j;

    if (company_code == 0 || game_code == 0) {
        return 5;
    }
    file_size_in_pages = (file_size_in_bytes + 255) / 256;
    if ((pfs->status & 1) == 0) {
        return 5;
    }
    if (func_8003BC0C(pfs) == 2) {
        return 2;
    }
    ret = func_80034630(pfs, company_code, game_code, game_name, ext_name, file_no);
    if (ret != 0 && ret != 5) {
        return ret;
    }
    if (*file_no != -1) {
        return 9;
    }
    func_8003C750(pfs, &bytes);
    if (file_size_in_bytes > bytes) {
        return 7;
    }
    if (file_size_in_pages != 0) {
        ret = func_80034630(pfs, 0, 0, 0, 0, file_no);
        if (ret != 0 && ret != 5) {
            return ret;
        }
        if (*file_no == -1) {
            return 8;
        }
        for (bank = 0; bank < pfs->banks; bank++) {
            ret = func_8003BD24(pfs, &inode, 0, bank);
            if (ret != 0) {
                return ret;
            }
            ret = func_80035A84(pfs, &inode, file_size_in_pages, &start_page, bank, &decleared, &last_page);
            if (ret != 0) {
                return ret;
            }
            if (start_page != -1) {
                if (firsttime == 0) {
                    fpage.inode_t.page = start_page;
                    fpage.inode_t.bank = bank;
                } else {
                    backup_inode.inode_page[old_last_page].inode_t.bank = bank;
                    backup_inode.inode_page[old_last_page].inode_t.page = start_page;
                    ret = func_8003BD24(pfs, &backup_inode, 1, old_bank);
                    if (ret != 0) {
                        return ret;
                    }
                }
                for (j = 0; j < 128; j++) {
                    backup_inode.inode_page[j].ipage = inode.inode_page[j].ipage;
                }
                old_bank = bank;
                firsttime++;
                old_last_page = last_page;
                if (file_size_in_pages > decleared) {
                    file_size_in_pages -= decleared;
                } else {
                    file_size_in_pages = 0;
                    break;
                }
            }
        }
        if (file_size_in_pages > 0 || start_page == -1) {
            return 3;
        }
        backup_inode.inode_page[old_last_page].inode_t.bank = bank;
        backup_inode.inode_page[old_last_page].inode_t.page = start_page;
        ret = func_8003BD24(pfs, &backup_inode, 1, old_bank);
        if (ret != 0) {
            return ret;
        }
        dir.start_page = fpage;
        dir.company_code = company_code;
        dir.game_code = game_code;
        dir.data_sum = 0;
        for (j = 0; j < 16; j++) {
            dir.game_name[j] = *game_name++;
        }
        for (j = 0; j < 4; j++) {
            dir.ext_name[j] = *ext_name++;
        }
        ret = func_8003C3C0(pfs->queue, pfs->channel, pfs->dir_table + *file_no, (u8 *)&dir, 0);
        if (ret != 0) {
            return ret;
        }
        return ret;
    }
    return 5;
}

s32 func_80035A84(T037Pfs *pfs, T037Inode *inode, s32 file_size_in_pages, s32 *first_page, u8 bank, s32 *decleared, s32 *last_page) {
    s32 j;
    s32 spage;
    s32 ret = 0;
    u8 tmp_data[32];
    s32 old_page;
    s32 offset = (bank > 0) ? 1 : pfs->inode_start_page;
    s32 i;

    for (j = offset; j < 128; j++) {
        if (inode->inode_page[j].ipage == 3) {
            break;
        }
    }
    if (j == 128) {
        *first_page = -1;
        return ret;
    }
    for (i = 0; i < 32; i++) {
        tmp_data[i] = 0;
    }
    spage = j;
    *decleared = 1;
    old_page = j;
    j++;
    while (file_size_in_pages > *decleared && j < 128) {
        if (inode->inode_page[j].ipage == 3) {
            inode->inode_page[old_page].inode_t.bank = bank;
            inode->inode_page[old_page].inode_t.page = j;
            ret = func_80035C84(pfs, old_page, tmp_data, bank);
            if (ret != 0) {
                return ret;
            }
            old_page = j;
            (*decleared)++;
        }
        j++;
    }
    *first_page = spage;
    if (j == 128 && file_size_in_pages > *decleared) {
        *last_page = old_page;
        return ret;
    }
    inode->inode_page[old_page].ipage = 1;
    ret = func_80035C84(pfs, old_page, tmp_data, bank);
    *last_page = 0;
    return ret;
}

s32 func_80035C84(T037Pfs *pfs, s32 page_no, u8 *data, u8 bank) {
    s32 i;
    s32 ret = 0;

    pfs->activebank = bank;
    ret = func_8003BFC0(pfs);
    if (ret != 0) {
        return ret;
    }
    for (i = 0; i < 8; i++) {
        ret = func_8003C3C0(pfs->queue, pfs->channel, page_no * 8 + i, data, 0);
        if (ret != 0) {
            break;
        }
    }
    pfs->activebank = 0;
    ret = func_8003BFC0(pfs);
    return ret;
}
