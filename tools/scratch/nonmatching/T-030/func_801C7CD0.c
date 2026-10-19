/* DRAFT. Remaining diff: Narrow mode argument, global-base registers, initialization and call scheduling differ. */
#include "common.h"

extern void func_801ADAD4(s32, s32 *, s32 *, u8 *);
extern void func_801C7A98();
extern void func_801CD038(void *, s32, s32 *, u8 *);
extern u8 D_800F4070[];
extern s8 D_801CD454, D_802923F5;
extern void *D_802925AC, *D_802926AC;
extern u8 D_802952E0[], D_802952FC[];
extern s32 D_802956F8, D_802956FC, D_80295700, D_802CA064;
extern s32 D_802D3678[4];
extern f32 D_802D39F8;
extern s8 D_802D39FC, D_802D3A01, D_802D3A02, D_802D3A07;
extern u8 D_802D3A00, D_802D3A06, D_802D3E15;

void func_801C7CD0(u8 arg0) {
    u8 mode;
    u8 replay;
    mode = arg0;
    if (D_802D3E15) mode = 5;
    arg0 = mode;
    func_801C7A98(mode);
    mode = arg0;
    D_802D39F8 = 0.0f;
    if (D_802D3A06) {
        mode = 3;
        D_802925AC = D_802952E0;
    } else D_802925AC = D_802952FC;
    D_802D39FC = 0;
    D_80295700 = 0;
    D_802956FC = 0;
    D_802956F8 = 0;
    D_802CA064 = 480;
    D_801CD454 = 0;
    D_802D3A00 = mode;
    if (mode == 5) {
        replay = D_802D3E15;
        if (!replay) {
            D_802D3E15 = 1;
            replay = 1;
        }
        D_802D3678[1] = 0x1000;
        D_802D3678[0] = 0;
        D_802D3678[3] = 0x1000;
        D_802D3678[2] = 0;
        D_802923F5 = 0;
        func_801CD038(D_800F4070, replay - 1, &D_802956FC, &D_802D3A00);
        D_802926AC = D_800F4070;
    } else if (mode != 4 && D_802D3A06 == 0) {
        func_801ADAD4(40, &D_80295700, &D_802956FC, &D_802D3A00);
    }
    D_802D3A01 = 0;
    D_802D3A02 = 65;
    D_802D3A07 = 0;
}
