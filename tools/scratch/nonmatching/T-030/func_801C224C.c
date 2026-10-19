/* DRAFT. Remaining diff: Mode-cache saved register, frame (0x18 vs 0x20), and copy-loop scheduling differ. */
#include "common.h"

extern void func_80012950(s32);
extern void func_80012A8C(s32);
extern void func_8001CD50(void);
extern void osViBlack(s32);
extern void (*D_800451EC[])(void);
extern u8 D_8004AC88;
extern s32 D_800698C4;
extern s32 D_8028326C[];
extern f32 D_80285240[][3][4];
extern f32 D_80285420[][4];
extern s8 D_80285570;
extern s32 D_80285574, D_80285578;
extern s8 D_80295718, D_802D3874;
extern f32 D_802D3878;
extern f32 D_802D3880[4];
extern s32 D_802D3890, D_802D3894;
extern f32 D_802D3898[3][4];
extern u8 D_802D38C8;

void func_801C224C(u8 arg0, s32 arg1) {
    s32 i, j;
    s32 mode;
    D_802D38C8 = arg0;
    osViBlack(1);
    func_80012950(1);
    mode = D_802D38C8;
    D_8004AC88 = mode;
    func_80012A8C(mode & 255);
    D_800698C4 = 0;
    D_800451EC[D_802D38C8]();
    func_8001CD50();
    mode = D_802D38C8;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_802D3898[j][i] = D_80285240[mode][j][i];
        }
        D_802D3880[i] = D_80285420[mode][i];
    }
    D_80285574 = D_8028326C[mode];
    D_802D3890 = arg1;
    D_802D3874 = 0;
    D_802D3878 = 50.0f;
    D_80295718 = 2;
    D_80285578 = 0;
    D_80285570 = 0;
    D_802D3894 = 0;
}
