/* T-139 draft: 189 differing words, 1812/1820 bytes in the full TU; literal ownership remains to be reconciled. */
#include "frontend.h"


typedef struct { s16 sound; u8 pad[0x8A]; } T030Sound23C0;
extern f32 cosf(f32), sinf(f32);
extern void func_80012B7C(FrontendGfxWords **,f32,f32,f32,f32,f32,f32);
extern void func_800131A4(FrontendGfxWords **,f32,f32,f32,f32,f32,f32);
extern void func_8001AA90(f32);
extern void func_8001C5A0(void),func_80028708(void),func_800287D4(void),func_8002B9B4(void);
extern void func_8002F6F4(s32, s32, void *);
extern void func_801C2D34(FrontendGfx **,s32,s32,s32,s32);
extern void func_801C2F5C(FrontendGfxWords **,s32,s32);
extern s32 func_801C317C(FrontendGfxWords **,s32,s32,s32);
extern s32 func_801C3524(FrontendGfxWords **,s32);
extern u8 D_8004A26C[];
extern void (*D_8004AA38)(void);
extern u8 D_8004AC88;
extern s32 D_8004AD00,D_80066C40,D_800698C4;
extern f32 D_800695CC,D_800695D0,D_800695D4,D_800695D8,D_800695DC,D_800695E0;
extern T030Sound23C0 D_801F2EB8[];
extern u8 D_80285570,D_80295718,D_802D3874,D_802D38C8;
extern f64 D_80293778,D_80293780,D_80293788,D_80293790,D_80293798;
extern f32 D_802937A0,D_802D3878;


u8 func_801C23C0(FrontendGfxWords **arg0, FrontendRenderContext *arg1) {
    f32 temp_f10;
    s32 var_v1;
    f32 velocity[3];
    u8 temp_v0_4;
    f32 temp_f14;
    u8 temp_v0_3;
    f32 temp_f12;
    f32 position[3];
    f32 sp4C;
    FrontendGfxWords *temp_v0;
    f32 temp_f12_2;
    f32 sp54;
    f32 sp50;
    f32 var_f0;
    u8 sp4B;
    f32 var_f14;    var_f0 = (f32)(arg1->frame - D_802D3890); sp4B = 0;
    if (D_80295718 == 2) {
        if (var_f0 > 120.0f) {
            func_801C2110(1.0f, D_802D3898[0], position, velocity);
            sp4C = var_f0;
            var_f14 = sp4C / 120.0f;
        } else {
            sp4C = var_f0;
            if (var_f0 > 90.0f) {
                if (var_f0 <= 120.0f) {
                    sp4C = (cosf((f32) ((f64) (var_f0 - 120.0f) * D_80293778 * 3.0)) * 30.0f) + 90.0f;
                } else {
                    sp4C = (cosf((f32) (((f64) (var_f0 - 120.0f) * (0.0174532925199432955)) / 3.0)) * 10.0f) + 110.0f;
                }
            }
            temp_f14 = sp4C / 120.0f;
            func_801C2110(temp_f14, D_802D3898[0], position, velocity);
            var_f14 = temp_f14;
        }
        temp_f12 = (f32) ((f64) var_f14 * D_80293788);
        sp54 = (((1.0f - cosf(temp_f12)) / 2) * (D_802D3880[1] - D_802D3880[0])) + D_802D3880[0];
        sp50 = (((1.0f - cosf(temp_f12)) / 2) * (D_802D3880[3] - D_802D3880[2])) + D_802D3880[2];
        if ((sp4C > 60.0f) && !(sp4C < 120.0f)) {
            sp50 = D_802D3880[3];
            sp54 = D_802D3880[1] - ((sp4C - 120.0f) / 35.0f);
            if (D_802D3874 != 0) {
                temp_f12_2 = (f32) ((f64) sp54 * (0.0174532925199432955));
                position[0] += D_802D3878 * sinf(temp_f12_2);
                position[2] += D_802D3878 * cosf(temp_f12_2);
                D_802D3878 = (f32) ((f64) D_802D3878 * D_80293798);
            } }
        D_802C9F70.yaw = sp54;
        D_802C9F70.pitch = sp50;
        D_802C9F70.x = position[0];
        D_802C9F70.y = position[1];
        D_802C9F70.z = position[2];
        func_8001C5A0();
        D_800695CC = position[0];
        D_800695D0 = position[1];
        D_800695D4 = position[2];
        D_800695D8 = sp50;
        D_800695DC = sp54;
        D_800695E0 = 0.0f;
        if (D_8004AC88 == 2) {
            D_800695D8 = 5.0f; }
        temp_v0 = (*arg0)++; temp_v0->w1 = 0xFF;
        temp_v0->w0 = 0xFB000000;
        temp_v0_2 = (*arg0)++;
        temp_v0_2->w1 = 0xFF;
        temp_v0_2->w0 = 0xFA000000;
        func_8002B9B4();
        func_8001AA90(sp54);
        func_8001AA90(sp54);
        func_8001AA90(sp54);
        func_80028708();
        func_800287D4();
        func_80028708();
        func_800287D4();
        func_80028708();
        func_800287D4();
        if (D_8004AC88 == 0) {
            D_8004AA38();
        }
        if (D_8004AD00 < 0xFD) { D_8004AD00 += 3;
        } else {
            D_8004AD00 = 0;
        }
        if (D_802D38C8 == 7) {
            D_800698C4 = 1;
        }
        func_80012B7C(arg0, position[0], position[1], position[2], sp50, sp54, 0.0f);
        func_800131A4(arg0, position[0], position[1], position[2], sp50, sp54, 0.0f);
        if (D_802D38C8 == 7) {
            D_800698C4 = 0;
        }
        if (sp4C > 90.0f) {
            sp3C = 0x15E;
            temp_f10 = sp4C - 120.0f;
            if (sp4C < 120.0f) {
                var_v1 = D_802D3894;
                sp3C = (s32) ((((temp_f10 + 30.0f) / 30.0f) * -280.0f) + D_802937A0);
            } else {
                var_v1 = D_802D3894;
                if (var_v1 == 0) {
                    func_8002F6F4(D_80066C40, D_801F2EB8[D_802D38C8].sound, &D_8004A26C); D_802D3894 = 1;
                    var_v1 = 1;
                }
            }
            temp_f16 = (s32) sp4C;
            func_801C2F5C(arg0, (var_v1 >> 2) + sp3C, temp_f16);
            if (D_802D3874 != 0) {
                temp_v0_3 = func_801C3524(arg0, D_802D3874);
                D_80285570 = 1;
                sp4B = temp_v0_3;
                D_802D3874 += 1;
            }
            func_801C2D34((FrontendGfx **)arg0, temp_f16, -0xFA, D_802D3894 - 0x4B0, temp_f16);
            if (func_801C317C(arg0, sp3C, D_802D3894, (s32) temp_f10) != 0) {
                D_80285570 = 1;
            }
            if (D_80285570 != 0)
    {
                D_802D3894 = (s32) D_802D3878;
                D_802D3874 += 1;
            }
        } else if (D_802D3874 != 0) {
            temp_v0_4 = func_801C3524(arg0, D_802D3874); D_80285570 = 1; sp4B = temp_v0_4;
            D_802D3874 += 1;
        } }
    return sp4B;
}
