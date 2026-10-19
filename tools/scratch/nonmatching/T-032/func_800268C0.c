/* DRAFT. Remaining diff: 40 positional words differ; 236/236 bytes */
typedef struct { s32 id; void *data; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite268;
typedef struct { s16 halfW,halfH,w,h; } T032Size268;
extern T032Sprite268 D_8004CED0[];
extern T032Size268 D_80061368[];
extern s32 D_800612D8[], D_8004EA78;
extern u8 D_80047C38[];
extern void func_800238C4(u8 *, void *);
void func_800268C0(u8 *base, s32 index, s32 id, s32 slot) {
    u8 *entry;
    T032Sprite268 *p;
    T032Size268 *size;
    D_8004CED0[D_8004EA78].id = id;
    entry = base + index * 4;
    func_800238C4(base + (entry[11] << 24) + entry[8] + (entry[9] << 8) + (entry[10] << 16), D_80047C38);
    p = &D_8004CED0[D_8004EA78]; size = &D_80061368[slot];
    size->halfW = p->halfW; size->halfH = p->halfH;
    size->w = p->w2; size->h = p->h;
    D_800612D8[slot] = id;
}
