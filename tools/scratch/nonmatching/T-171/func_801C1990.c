#include "frontend.h"
extern s32 func_801C17D0(u32 *, u8);
extern u8 D_8004A407, D_8004EA9B[], D_802D37FC, D_802D37FD;
extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u64 D_802D3800[];
u8 func_801C1990(s32 *stats) {
    s32 result;
    s32 mask;
    s32 player;
    u32 value;
    s32 pending;
    u8 character;
 D_802D3800[0] = 0;
    D_802D3800[1] = 0;
    if (!stats[6]) stats[6] = 100;
    mask = D_8004A407 ^ 3;
    D_802D37FD = stats[0] & mask;
    value = (3 - stats[0]) & mask;
    pending = D_802D37FC = value;
    if (pending == 3) {
        result = func_801C17D0((u32 *)stats, 0);
        result |= func_801C17D0((u32 *)stats, 1) * 2;
        D_802D37FC = 0;
        return result & 255;
    }
    if (pending > 0) {
        func_801C17D0((u32 *)stats, (pending - 1) & 255);
        pending = D_802D37FC;
    }
    if (D_802D37FD > 0) {
        character = D_8004EA9B[D_802D37FD];
        D_802D37FD -= 1;
        player = D_802D37FD;
        value = stats[6];
        if (D_80127C30[player] > value) D_80127C30[player] = value;
        if (player == 0) {
            if (D_80128328[player][character] < (u32) stats[3]) D_80128328[player][character] = stats[3];
            if (D_80128310[player][character] < (u32) stats[1]) D_80128310[player][character] = stats[1];
        } else {
            if (D_80128328[player][character] < (u32) stats[4]) D_80128328[player][character] = stats[4];
            if (D_80128310[player][character] < (u32) stats[2]) D_80128310[player][character] = stats[2];
        }
        D_8012830A[player]++;
        if (stats[5]) D_80128308[player]++;
        D_802D37FD = player + 1;
    }
    if (pending > 0 && D_802D3800[pending - 1] != 0) return pending;
    return 0;
}
