/* DRAFT. Remaining diff: ~130 lines; same logic. Target keeps the message pointer address in s0 and caches *msg in a0, keeps gfxStart on the stack (sp5C) rather than s0, frame is 0x60 (here 0x68), and display-list writes are scheduled differently. Must return int to stay compatible with the later 'extern int func_801ACB1C(Callback, ...)' in ovl_7DF8.c. Fill-rectangle words are hand-encoded G_FILLRECT (no gbi.h in include/). */
typedef struct {
    u32 w0;
    u32 w1;
} T034Gfx;

typedef struct {
    s32 unk0;
    s32 unk4;
} T034GameState;

extern s32 osRecvMesg(void *, void *, s32);
extern void bzero(void *, s32);
extern void func_8002AA98(s32, s32);
extern void func_8002F9FC(void);
extern void func_801AD3BC(T034Gfx **, T034GameState *);
extern void func_801AD7D8(T034Gfx *, T034Gfx **, s32, s32, T034GameState *);
extern void func_801ADA04(T034GameState *);
extern void func_801AF424(T034Gfx **, T034GameState *);
extern s64 func_801BD270(s32);
extern u8 D_80044A24;
extern u8 D_8004A298[];
extern s32 D_8004A414;
extern T034Gfx D_8006F1C0[];
extern T034Gfx D_80076240[];
extern s16 *D_801CD458;
extern s32 D_801CD45C;
extern T034Gfx D_801CD460[];
extern s32 D_80282A60;
extern s32 D_802956F0;
extern s32 D_80295704;
extern s32 D_8029571C;
extern u8 D_80295722;
extern T034GameState D_802C9F70;

int func_801ACB1C(void (*arg0)(), void (*arg1)(), void (*arg2)()) {
    T034Gfx *gfxStart;
    T034Gfx *gfx;
    s32 sp48;
    s32 sp44;
    u32 diff;
    s32 h;
    s32 i;

    osRecvMesg(D_8004A298, &D_801CD458, 1);
    if (*D_801CD458 == 1) {
        if (D_8004A414 < 2 && D_801CD45C <= 0) {
            D_80044A24 = D_802C9F70.unk0;
            gfxStart = gfx = D_802C9F70.unk0 ? D_80076240 : D_8006F1C0;
            D_801CD45C = D_8029571C;
            func_801AD3BC(&gfx, &D_802C9F70);
            if (arg0 != 0) {
                arg0(&sp48, &sp44, &D_802C9F70);
            }
            func_801AF424(&gfx, &D_802C9F70);
            arg1(&gfx, &D_802C9F70);
            if (D_80295722) {
                if (D_802956F0 == 0) {
                    D_802956F0 = D_802C9F70.unk4 - 1;
                }
                diff = D_802C9F70.unk4 - D_802956F0;
                if (diff >= 16) {
                    func_8002F9FC();
                    while (1) {
                        bzero((void *)0x802D4000, 0x12C000);
                    }
                }
                {
                    T034Gfx *g = gfx++;

                    g->w0 = 0x06000000;
                    g->w1 = (u32)D_801CD460;
                }
                h = diff * 17;
                {
                    T034Gfx *g = gfx++;

                    g->w0 = 0xF69FC000 | (((h + 1) & 0x3FF) << 2);
                    g->w1 = 0;
                }
                {
                    T034Gfx *g = gfx++;

                    g->w0 = 0xF69FC77C;
                    g->w1 = ((478 - h) & 0x3FF) << 2;
                }
                func_8002AA98(0x8000 - diff * 2100, h);
            }
            func_801AD7D8(gfxStart, &gfx, sp48, sp44, &D_802C9F70);
        }
        D_802C9F70.unk4++;
        D_80295704 = D_802C9F70.unk4;
        D_801CD45C--;
        if (D_80282A60 != 0) {
            for (i = 0; i < D_80282A60; i++) {
                arg2(i, func_801BD270(i), &D_802C9F70);
            }
        } else {
            func_801BD270(0);
        }
        func_801ADA04(&D_802C9F70);
    } else if (*D_801CD458 == 2) {
        D_8004A414--;
    }
}
