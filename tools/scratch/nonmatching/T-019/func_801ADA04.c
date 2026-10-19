/* T-019 nonmatching draft. Remaining diff: 204-byte reconstruction versus 208-byte target; pending-mode global-address reuse and register allocation differ.
 */
#include "common.h"
typedef struct RenderState {
    s32 index, unk4;
    u8 pad8[0xCC];
    f32 unkD4, unkD8, unkDC, unkE0, unkE4;
    s32 width, height, mode, height2;
    void *unkF8;
} RenderState;
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
        osViSetMode(&D_800066D0[pending], arg0);
        osViBlack(1);
    osViSetSpecialFeatures(0xAA);
    osViBlack(1);
        D_801CD4B8 = arg0->mode;
        D_801CD4BC = -1;
    }
}




