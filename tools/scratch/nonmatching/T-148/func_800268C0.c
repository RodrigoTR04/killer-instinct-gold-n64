/* T-140 DRAFT: 28 differing words, 236/236 bytes in the full owning unit. */
typedef struct { s16 halfW,halfH,w,h; } T032Size268;
extern T032Size268 D_80061368[];
extern s32 D_800612D8[], D_8004EA78;
extern u8 D_80047C38[];
extern void func_800238C4(u8 *, void *);
void func_800268C0(u8 *base, s32 index, s32 id, s32 slot)
{
    u8 *entry;
    T032Sprite25D *p;
    T032Size268 *size;
    s16 hw;
    s16 hh;
    s16 w;
    u8 offsetHigh;
    s16 h;
    s32 offset;
    D_8004CED0[D_8004EA78].pixels = (u16 *)id;
    entry = base + (index * 4);
    offsetHigh = entry[11];
    func_800238C4(base + ((((offsetHigh << 24) + (entry[9] << 8)) + entry[8]) + (entry[10] << 16)), D_80047C38);
    p = &D_8004CED0[D_8004EA78];
    offset = slot * 4;
    size = (T032Size268 *)((u8 *)D_80061368 + offset * 2);
    hw = p->halfW;
    hh = p->halfH;
    w = p->w2;
    h = p->h;
    size->halfW = hw;
    size->halfH = hh;
    size->w = w;
    size->h = h;
    *(s32 *)((u8 *)D_800612D8 + offset) = id;
}
