/* T-087: nonmatching; 39 differing words, 204 compiled bytes. See T-087/REPORT.md. */
extern void osViBlack(s32);

extern s32 D_80000300, D_801CD4B8, D_801CD4BC;
typedef struct VideoMode { u8 data[0x50];
    } VideoMode;
extern VideoMode D_800066D0[];
extern void osViSetMode(), osViSetSpecialFeatures(u32);
void func_801ADA04(RenderState *arg0) {
    s32 mode = arg0->mode;
    s32 next, pending;
    if (mode < 14) {
        next = mode + 14;
        if (D_80000300 != 1) {
        arg0->mode = next;
        mode = next;
        }
    }
    if (D_801CD4B8 != mode) {
        pending = D_801CD4BC;
        if (pending == -1) { D_801CD4BC = mode;
    return;
    }
        D_801CD4BC = pending;
        osViSetMode(&D_800066D0[D_801CD4BC = pending]);
        osViBlack(1);
    osViSetSpecialFeatures(0xAA);
    osViBlack(1);
        D_801CD4B8 = arg0->mode;
        D_801CD4BC = -1;
    }
}
