/* T-050: retained improvement; 225 differing words including size penalty, 940 compiled bytes. Full function remains nonmatching. */
/* DRAFT. Remaining diff: Text-position float temporaries, saved counters, stack slots and call scheduling differ. */
#include "frontend.h"



extern u8 ***D_80285574;
extern s32 D_80285578, D_802956F4, D_802D3830, D_802D3834;
extern f32 D_802937B8, D_802937BC;


s32 func_801C317C(FrontendGfxWords **arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_t5;
    u8 ***var_a1;
    s32 temp_a3;
    s32 var_s3;
    f32 temp_f22;
    s32 temp_t0;
    s32 var_v1;
    f32 temp_f20;
    s32 var_s0;
    s32 temp_t2;
    u8 *var_a2;
    s32 sp68;
    u8 **var_a0;
    f32 temp_f24;
    s32 var_s2;

    sp68 = 0;
    if (arg3 < 0) {
        D_80285578 = 0;
        D_802D3830 = 0x1F4;
        D_802D3834 = 0;
    }
    D_802956F4 += func_801BDF94(arg0, (D_802956F4 << 6) + D_802C9F70.matrices, **D_80285574, (f32) (((s32) (arg1 * -2) / 3) - 0x5A), 200.0f, (f32) (arg2 - 0x3E8), 1, 1.0f, ((f32) (arg3 + 0x1E) / 30.0f) * 360.0f);
    var_v1 = D_80285578;
    var_a1 = &D_80285574[var_v1];
    var_a0 = *var_a1;
    if ((var_a0 != 0) && (arg3 > 0)) {
        temp_a3 = var_v1 == 0;
        var_s2 = 0xB4;
        var_s0 = temp_a3 * 4;
        if (D_802D3830 < arg3) {
            D_802D3830 += 0x1F4;
            D_802D3834 = -1;
        }
        if ((D_802D3834 < 0x100) && (D_802D3834 >= 0)) {
            var_s3 = D_802D3834 + 0x10;
            if (var_s3 >= 0x100) {
                var_s3 = 0xFF;
            }
        } else {
            var_s3 = D_802D3834 - 0x10;
            temp_t2 = var_v1 + 1;
            if (var_s3 < -0xFF) {
                var_a1 = &D_80285574[temp_t2];
                D_80285578 = temp_t2;
                var_s3 = 0;
                var_a0 = *var_a1;
                var_v1 = temp_t2;
            }
        }
        if ((var_a0 == 0) || ((var_s3 < 0) && (var_a1[1] == 0))) {
            temp_t5 = var_v1 - 1;
            if (var_a0 == 0) {
                D_80285578 = temp_t5;
                var_a0 = D_80285574[temp_t5];
            }
            if (var_s3 == 0) {
                var_s3 = -0xFF;
            }
            sp68 = 1;
        }
        var_a2 = var_a0[temp_a3];
        D_802D3834 = var_s3;
        if (var_a2 != 0) {
            D_802D3834 = var_s3;
            temp_f22 = D_802937BC;
            temp_f24 = D_802937B8;
            temp_f20 = (f32) (arg2 - 0x5DC);
            do {
                temp_t0 = D_802956F4 + func_801BD640(arg0, (D_802956F4 << 6) + D_802C9F70.matrices, var_a2, temp_f22, (f32) (var_s2 - 5), temp_f20, 0, 0, 0, (s32) (D_802D3834 & 0xFF) >> 1);
                D_802956F4 = temp_t0;
                D_802956F4 += func_801BD640(arg0, (temp_t0 << 6) + D_802C9F70.matrices, *(u8 **)((u8 *)D_80285574[D_80285578] + var_s0), temp_f24, (f32) var_s2, temp_f20, 0xFF, 0xFF, 0xFF, D_802D3834);
                var_s0 += 4;
                var_s2 -= 0x37;
                var_a2 = *(u8 **)((u8 *)D_80285574[D_80285578] + var_s0);
            } while (var_a2 != 0);
        }
    }
    return sp68;
}
