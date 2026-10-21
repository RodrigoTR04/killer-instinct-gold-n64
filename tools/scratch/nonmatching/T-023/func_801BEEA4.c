/* T-116 DRAFT: see T-116/REPORT.md for remaining instructions. */
typedef struct { s32 data; u16 score; u16 pad; } T023EntryEA4;
typedef struct { T023EntryEA4 *entries; u8 count, descending; u16 pad; } T023TableEA4;


s32 func_801BEEA4(s32 table, s32 score, s32 data)
{
  T023EntryEA4 *entry;
  T023EntryEA4 *entries;
  T023TableEA4 *header;
  s32 last;
  s32 index;
  s32 slot;
  s32 next;
  s32 count;
  s32 i;
  s32 entryBytes;
  header = &((T023TableEA4 *) D_80127D80)[table];
  count = header->count;
  last = count - 1;
  entries = header->entries;
  index = last;
  if (header->descending)
  {
    if ((last >= 0) && (entries[last].score < score))
    {
      do
      {
        index--;
        if (index < 0)
        {
          break;
        }
      }
      while (entries[index].score < score);
    }
  }
  else
    if ((last >= 0) && (score < entries[last].score))
  {
    do
    {
      index--;
      if (index < 0)
      {
        break;
      }
    }
    while (score < entries[index].score);
  }
  slot = index + 1;
  i = count;
  if (slot == count)
  {
    return 0;
  }
  entry = &entries[slot];
  next = ++slot;
  if (next < count)
  {
    do
    {
      entryBytes = sizeof(T023EntryEA4);
      last = i - 1;
      memcpy(&entries[last], &entries[i - 2], entryBytes);
      i = last;
    }
    while (next < last);
  }
  entry->score = score;
  entry->data = data;
  return next;
}
