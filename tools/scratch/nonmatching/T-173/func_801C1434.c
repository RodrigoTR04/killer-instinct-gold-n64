#include "frontend.h"
extern void func_801C0610(s32);
extern void func_801C08F8(s32, s32, u8, s32, u64, s32);
extern void func_801C11F0(s32, s32, s32, s32);
extern void func_801C1C34(s32, s32, s32, s32);
extern u8 D_8004A404, D_8004A407, D_8004EA9B[], D_8004EA9C, D_8004EA9D[];
extern u8 D_802D37FC, D_802D37FD, D_802D3810;
extern u64 D_802D3800[];

void func_801C1434(s32 list, s32 matrix, s32 state) {
    s32 player;
    u64 value;
    s32 fd;

    func_801C0610(list);
    if (D_8004A407) {
        if (D_802D37FD) {
            func_801C1C34(list, matrix, state, 0);
            return;
        }
        player = D_802D37FC;
        if (!(D_802D3810 & player) && (player > 0)) {
            func_801C08F8(list, matrix, D_8004EA9B[player], 0, ((u64 *) &D_802D37F8)[player], player - 1);
            return;
        }
        if (player == 0) {
            func_801C11F0(list, matrix, 0, player);
            return;
        }
        func_801C11F0(list, matrix, 0, player - 1);
        return;
    }
    fd = D_802D37FD; player = D_802D37FC;
    if ((fd == player) && (fd == 0)) {
        if (!(D_802D3810 & 1)) {
            value = D_802D3800[0];
            if (value) {
                func_801C08F8(list, matrix, D_8004EA9C, -1, value, 0);
            }
        } else if (D_8004A404 != 2) {
            func_801C11F0(list, matrix, -1, 0);
        }
        if (!(D_802D3810 & 2)) {
            value = D_802D3800[1];
            if (value) {
                func_801C08F8(list, matrix, D_8004EA9D[0], 1, value, 1);
            }
        } else if (D_8004A404 != 2) {
            func_801C11F0(list, matrix, 1, 1);
        }
    } else {
        if (!(D_802D3810 & player)) {
            func_801C08F8(list, matrix, D_8004EA9B[player], player * 2 - 3, ((u64 *) &D_802D37F8)[player], player - 1);
        } else {
            func_801C11F0(list, matrix, player * 2 - 3, player - 1);
        }
        func_801C1C34(list, matrix, state, 3 - D_802D37FC * 2);
    }
}
