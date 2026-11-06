typedef struct VideoState { s32 current, pending; } VideoState;
extern VideoState D_801CD4B8;
typedef struct VideoMode { u8 data[0x50]; } VideoMode;
extern VideoMode D_800066D0[];
extern s32 D_80000300;
extern void osViSetMode(), osViSetSpecialFeatures(u32);

void func_801ADA04(RenderState *arg0) {
    VideoState *state = &D_801CD4B8;

    if (arg0->mode < 14 && D_80000300 != 1) {
        arg0->mode += 14;
    }
    if (arg0->mode != state->current) {
        if (state->pending == -1) {
            state->pending = arg0->mode;
            return;
        }
        osViSetMode(&D_800066D0[state->pending]);
        osViBlack(1);
        osViSetSpecialFeatures(0xAA);
        osViBlack(1);
        state->current = arg0->mode;
        do { state->pending = -1; } while (0);
    }
}
