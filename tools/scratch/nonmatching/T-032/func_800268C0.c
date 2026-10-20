/* T-095 DRAFT: remaining differences recorded in T-095/REPORT.md. */
typedef struct { s32 id; void *data; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite268;
typedef struct { s16 halfW,halfH,w,h; } T032Size268;
extern T032Sprite268 D_8004CED0[];
extern T032Size268 D_80061368[];
extern s32 D_800612D8[], D_8004EA78;
extern u8 D_80047C38[];
extern void func_800238C4(u8 *, void *);
void func_800268C0(u8 *base, s32 index, s32 id, s32 slot)
{
    u8 *entry;
    T032Sprite268 *p;
    T032Size268 *size;
    s16 hw;
    s16 hh;
    s16 w;
    u8 offsetHigh;
    s16 h;
    D_8004CED0[D_8004EA78].id = id;
    entry = base + (index * 4);
    offsetHigh = entry[11];
    func_800238C4(base + ((((offsetHigh << 24) + (entry[9] << 8)) + entry[8]) + (entry[10] << 16)), D_80047C38);
    p = &D_8004CED0[D_8004EA78];
    size = &D_80061368[slot];
    hw = p->halfW;
    hh = p->halfH;
    w = p->w2;
    h = p->h;
    size->halfW = hw;
    size->halfH = hh;
    size->w = w;
    size->h = h;
    D_800612D8[slot] = id;
}
