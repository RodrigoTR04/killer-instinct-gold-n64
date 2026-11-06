extern s32 D_80000300, D_801CD4B8, D_801CD4BC;
typedef struct VideoMode { u8 data[0x50]; } VideoMode;
extern VideoMode D_800066D0[];
extern void osViSetMode(), osViSetSpecialFeatures(u32);

void func_801ADA04(RenderState *arg0) {
    s32 *pendingp = &D_801CD4BC;

    if (arg0->mode < 14 && D_80000300 != 1) {
        arg0->mode += 14;
    }
    if (D_801CD4B8 != arg0->mode) {
        if (*pendingp == -1) {
            *pendingp = arg0->mode;
            return;
        }
        *pendingp = *pendingp;
        osViSetMode(&D_800066D0[*pendingp]);
        osViBlack(1);
        osViSetSpecialFeatures(0xAA);
        osViBlack(1);
        D_801CD4B8 = arg0->mode;
        do { *pendingp = -1; } while (0);
    }
}
