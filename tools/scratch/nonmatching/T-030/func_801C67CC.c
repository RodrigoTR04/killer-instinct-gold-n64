/* DRAFT. Remaining diff: Frame (0x60 vs 0x28), double lifetime/spills and unsigned-result conversion registers differ. */
#include "common.h"

extern void func_801C4C64(f32 *, f32 *);
extern void func_801C4BD0();
extern f32 D_80291E8C[], D_80291F10[], D_80291F40[];
extern f64 D_802948A0, D_802948A8, D_802948B0;
extern f32 D_802D3990[];
extern u8 D_802D399C, D_802D399D, D_802D399E, D_802D39B4;

s32 func_801C67CC(s32 arg0, u32 arg1) {
    f64 sp18;
    f32 temp_f0;
    f64 temp_f8;
    f64 var_f0;
    f64 var_f2;
    s32 temp_f10;
    s32 temp_v0;
    s32 temp_v0_2;
    u32 var_a1;
    u8 temp_t3;
    u8 temp_t9;

    var_a1 = arg1;
    if (var_a1 >= 0xF1U) {
        var_f0 = D_802948A0;
        var_f2 = (f64) var_a1;
        if (var_f0 < var_f2) {
            if (D_802D39B4 != 0xFF) {
                sp18 = var_f2;
                func_801C4C64(D_80291F10, D_80291F40);
                var_f0 = D_802948A8;
                D_802D39B4 = 0xFF;
            }
            return (u32)(var_f2 - var_f0);
        }
        if (D_802D399E == 0) {
            sp18 = var_f2;
            func_801C4BD0(0xD);
            D_802D399D = 2;
        }
        temp_t3 = D_802D399C + D_802D399D;
        temp_v0 = temp_t3 & 0xFF;
        D_802D399C = temp_t3;
        if (temp_v0 >= 8) {
            if (temp_v0 >= 0x22) {
                D_802D399C = 0xD;
            } else if (temp_v0 >= 0xC) {
                D_802D399D = 3;
            }
            D_802D3990[0] = (f32) (D_80291E8C[0] - (((f32) var_a1 - 240.0f) * 3.0f));
            temp_f0 = (f32) (var_f2 - D_802948B0) / 120.0f;
            D_802D3990[1] = (f32) (D_80291E8C[1] + ((-temp_f0 * temp_f0 * 200.0f) + 200.0f));
        }
        var_a1 = 0x1E0 - var_a1;
        goto block_25;
    }
    temp_t9 = D_802D399C + D_802D399D;
    temp_v0_2 = temp_t9 & 0xFF;
    D_802D399C = temp_t9;
    if (temp_v0_2 >= 0x15) {
        D_802D399D = 0xFF;
    } else if (temp_v0_2 < 2) {
        D_802D399D = 1;
    }
block_25:
    D_802D39B4 = 1;
    return (s32) var_a1;
}
