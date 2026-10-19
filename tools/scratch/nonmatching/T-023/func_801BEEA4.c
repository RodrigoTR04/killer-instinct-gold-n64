/* DRAFT. Remaining diff: Score signedness, stack frame, insertion-loop registers and control flow differ. */
typedef struct { s32 data; s16 score; u16 pad; } T023EntryEA4;
typedef struct { T023EntryEA4 *entries; u8 count, descending; u16 pad; } T023TableEA4;
extern T023TableEA4 D_80127D80[];
extern void *memcpy(void *, const void *, u32);
s32 func_801BEEA4(s32 table, s16 score, s32 data) {
    T023EntryEA4 *entry;
    T023EntryEA4 *entries;
    T023TableEA4 *header;
    s32 last, index, slot, next;
    u8 count, i;
    header = &D_80127D80[table];
    count = header->count;
    last = count - 1;
    entries = header->entries;
    index = last;
    if (header->descending) {
        if (last >= 0 && entries[last].score < score) {
            do { index--; if (index < 0) break; } while (entries[index].score < score);
        }
    } else if (last >= 0 && score < entries[last].score) {
        do { index--; if (index < 0) break; } while (score < entries[index].score);
    }
    slot = index + 1;
    i = count;
    if (slot == count) return 0;
    next = slot + 1;
    entry = &entries[slot];
    if (next < count) {
        do {
            index = i - 1;
            memcpy(&entries[index], &entries[i - 2], 8);
            i = index;
        } while (next < index);
    }
    entry->score = score;
    entry->data = data;
    return next;
}
