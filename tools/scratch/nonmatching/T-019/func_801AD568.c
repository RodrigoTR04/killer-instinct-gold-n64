/* T-019 nonmatching draft. Remaining diff: Stack frame 0x28 versus target 0x40; display-command pointer lifetimes and scheduling differ.
 */
#include "common.h"
typedef struct RenderState {
    s32 index, unk4;
    u8 pad8[0xCC];
    f32 unkD4, unkD8, unkDC, unkE0, unkE4;
    s32 width, height, mode, height2;
    void *unkF8;
} RenderState;
typedef struct DisplayCommand { u32 w0, w1; } DisplayCommand;
extern u8 D_801CD454;

extern u8 D_80044A24;
extern DisplayCommand D_80068930[][200];
extern u32 D_8004A428[];
extern s32 D_802956F8, D_802956FC, D_80295700;
extern void func_801BBE88(DisplayCommand **, RenderState *);
void func_801AD568(DisplayCommand **arg0, s32 *arg1, RenderState *arg2) {
    DisplayCommand *p = D_80068930[D_80044A24];
    DisplayCommand *q;
    s32 color;
    *arg0 = p;
    q = p++; q->w0 = 0xE7000000; q->w1 = 0;
    q = p++; q->w0 = ((arg2->width - 1) & 0xFFF) | 0xFF100000;
    q->w1 = D_8004A428[D_80044A24];
    q = p++; q->w0 = 0xED000000; q->w1 = 0xA00780;
    if (D_801CD454 == 0 || arg2->height != arg2->height2) {
        q = p++; q->w1 = 0; q->w0 = 0xEF300000;
        q = p++; q->w0 = 0xF7000000;
        color = ((D_802956F8 << 8) & 0xF800) | ((D_802956FC * 8) & 0x7C0) | ((D_80295700 >> 2) & 0x3E) | 1;
        q->w1 = (color << 16) | color;
        q = p++; q->w1 = 0;
        q->w0 = (((arg2->width - 1) & 0x3FF) << 14) | 0xF6000000 | (((arg2->height2 - 1) & 0x3FF) * 4);
    }
    if (D_801CD454 != 0) func_801BBE88(&p, arg2);
    if (p == D_80068930[D_80044A24]) { *arg0 = 0; *arg1 = 0; return; }
    q = p++; q->w0 = 0xE9000000; q->w1 = 0;
    *arg1 = (p - *arg0) * 8;
}


