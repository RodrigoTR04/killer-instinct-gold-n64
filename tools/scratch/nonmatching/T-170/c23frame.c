/* func_801C23C0 — rebuilt from the target's arithmetic order.
 *
 * The original computes `angle - 120.0f` as a float ONCE (sub.s into f10/f18)
 * and feeds that same float into each cosf argument, converting to double only
 * at the multiplication. Declaring the difference as a named float local is what
 * keeps IDO from spilling an f64 to the stack (the frame's 0x20 sdc1 slot).
 */
#include "frontend.h"

typedef struct { s16 sound; u8 pad[0x8A]; } T030Sound23C0;
extern f32 cosf(f32), sinf(f32);
extern void func_80012B7C(FrontendGfxWords **, f32, f32, f32, f32, f32, f32);
extern void func_800131A4(FrontendGfxWords **, f32, f32, f32, f32, f32, f32);
extern void func_8001AA90(f32);
extern void func_8001C5A0(void), func_80028708(void), func_800287D4(void), func_8002B9B4(void);
extern void func_8002F6F4(s32, s32, void *);
extern void func_801C2D34(FrontendGfx **, s32, s32, s32, s32);
extern void func_801C2F5C(FrontendGfxWords **, s32, s32);
extern s32 func_801C317C(FrontendGfxWords **, s32, s32, s32);
extern s32 func_801C3524(FrontendGfxWords **, s32);
extern u8 D_8004A26C[];
extern void (*D_8004AA38)(void);
extern s32 D_8004AD00, D_80066C40, D_800698C4;
extern f32 D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0;
extern T030Sound23C0 D_801F2EB8[];
extern u8 D_80285570, D_80295718, D_802D3874, D_802D38C8;
extern f64 D_80293778, D_80293780, D_80293788, D_80293790, D_80293798;
extern f32 D_802937A0, D_802D3878;

u8 func_801C23C0(FrontendGfxWords **arg0, FrontendRenderContext *arg1) {
    f32 position[3];
    f32 velocity[3];
    f32 angle;
    f32 pitch;
    f32 fade;
    f32 yaw;
    u8 result;
    FrontendGfxWords *g;

    angle = (f32) (arg1->frame - D_802D3890);
    result = 0;
    if (D_80295718 == 2) {
        if (angle > 120.0f) {
            func_801C2110(1.0f, D_802D3898[0], position, velocity);
            fade = angle / 120.0f;
        } else {
            fade = angle - 120.0f;
            if (angle > 90.0f) {
                if (angle <= 120.0f) {
                    fade = (cosf((f32) ((f64) fade * D_80293778 * 3.0)) * 30.0f) + 90.0f;
                } else {
                    fade = (cosf((f32) ((f64) fade * D_80293780 / 3.0)) * 10.0f) + 110.0f;
                }
            } else {
                fade = angle;
            }
            fade /= 120.0f;
            func_801C2110(fade, D_802D3898[0], position, velocity);
        }
        angle = (f32) ((f64) fade * D_80293788);
        yaw = (((1.0f - cosf(angle)) / 2) * (D_802D3880[1] - D_802D3880[0])) + D_802D3880[0];
        pitch = (((1.0f - cosf(angle)) / 2) * (D_802D3880[3] - D_802D3880[2])) + D_802D3880[2];
        if ((fade > 60.0f) && !(fade < 120.0f)) {
            pitch = D_802D3880[3];
            yaw = D_802D3880[1] - ((fade - 120.0f) / 35.0f);
            if (D_802D3874 != 0) {
                fade = (f32) ((f64) yaw * D_80293790);
                position[0] += D_802D3878 * sinf(fade);
                position[2] += D_802D3878 * cosf(angle);
                D_802D3878 = (f32) ((f64) D_802D3878 * D_80293798);
            }
        }
        D_802C9F70.yaw = yaw;
        D_802C9F70.pitch = pitch;
        D_802C9F70.x = position[0];
        D_802C9F70.y = position[1];
        D_802C9F70.z = position[2];
        func_8001C5A0();
        D_800695CC = position[0];
        D_800695D0 = position[1];
        D_800695D4 = position[2];
        D_800695D8 = pitch;
        D_800695DC = yaw;
        D_800695E0 = 0.0f;
        if (D_8004AC88 == 2) {
            D_800695D8 = 5.0f;
        }
        g = (*arg0)++;
        g->w1 = 0xFF;
        g->w0 = 0xFB000000;
        g = (*arg0)++;
        g->w1 = 0xFF;
        g->w0 = 0xFA000000;
        func_8002B9B4();
        func_8001AA90(yaw);
        func_8001AA90(yaw);
        func_8001AA90(yaw);
        func_80028708();
        func_800287D4();
        func_80028708();
        func_800287D4();
        func_80028708();
        func_800287D4();
        if (D_8004AC88 == 0) {
            D_8004AA38();
        }
        if (D_8004AD00 < 0xFD) {
            D_8004AD00 += 3;
        } else {
            D_8004AD00 = 0;
        }
        if (D_802D38C8 == 7) {
            D_800698C4 = 1;
        }
        func_80012B7C(arg0, position[0], position[1], position[2], pitch, yaw, 0.0f);
        func_800131A4(arg0, position[0], position[1], position[2], pitch, yaw, 0.0f);
        if (D_802D38C8 == 7) {
            D_800698C4 = 0;
        }
        if (fade > 90.0f) {
            s32 shade;

            shade = 0x15E;
            angle = fade - 120.0f;
            if (fade < 120.0f) {
                shade = (s32) ((((angle + 30.0f) / 30.0f) * -280.0f) + D_802937A0);
            } else if (D_802D3894 == 0) {
                func_8002F6F4(D_80066C40, D_801F2EB8[D_802D38C8].sound, &D_8004A26C);
                D_802D3894 = 1;
            }
            func_801C2F5C(arg0, (D_802D3894 >> 2) + shade, (s32) fade);
            if (D_802D3874 != 0) {
                D_80285570 = 1;
                result = func_801C3524(arg0, D_802D3874);
                D_802D3874 += 1;
            }
            func_801C2D34((FrontendGfx **) arg0, (s32) fade, -0xFA, D_802D3894 - 0x4B0, (s32) fade);
            if (func_801C317C(arg0, shade, D_802D3894, (s32) angle) != 0) {
                D_80285570 = 1;
            }
            if (D_80285570 != 0) {
                D_802D3894 = (s32) D_802D3878;
                D_802D3874 += 1;
            }
        } else if (D_802D3874 != 0) {
            D_80285570 = 1;
            result = func_801C3524(arg0, D_802D3874);
            D_802D3874 += 1;
        }
    }
    return result;
}
