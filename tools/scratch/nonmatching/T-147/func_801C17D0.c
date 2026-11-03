#include "frontend.h"
/* T-074 DRAFT: 103 differing words; 436 bytes. Not matching. */
extern u64 func_801BEA74(s32, s32, s32, u8 *, u8 *, s32, s32);
extern void func_801C1704(u8);
extern u8 D_8004EA9C[];
extern s32 D_80127C30[];

extern u64 D_802D3800[];
s32 func_801C17D0(u32 *stats, u8 player) {    u8 character = D_8004EA9C[player];
    u32 value;
    u64 *out;
    if (player == 0) {
        value = stats[3];
        if (D_80128328[player][character] < value) D_80128328[player][character] = value;
        value = stats[1];
        if (D_80128310[player][character] < value) D_80128310[player][character] = value;
    }
    else {
        value = stats[4];
        if (D_80128328[player][character] < value) D_80128328[player][character] = value;
        value = stats[2];
        if (D_80128310[player][character] < value) D_80128310[player][character] = value;
    }
    out = &D_802D3800[player];
    *out = func_801BEA74(D_8012830A[player], D_80128308[player], D_80127C30[player], D_80128310[player], D_80128328[player], ((s32 *)&D_80128300)[player], character);
    func_801C1704(player);
    return *out != 0;
}
