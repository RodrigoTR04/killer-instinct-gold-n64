/* DRAFT. Remaining diff: Camera-vector/temporary stack layout, interpolation loop and rendering-call scheduling differ. */
#include "common.h"

extern f32 D_802D3880, D_802D3898;
typedef struct { u32 w0,w1; } T030Cmd5298;
typedef struct { s32 id,ticks; u8 pad8[0xF0]; u8 *matrices; } T030Render5298;
typedef struct { u8 pad[0x7E]; u16 scale; u8 tail[0xC]; } T030Sprite5298;
extern f32 cosf(f32);
extern void func_80012B7C(T030Cmd5298 **,f32,f32,f32,f32,f32,f32);
extern void func_800131A4(T030Cmd5298 **,f32,f32,f32,f32,f32,f32);
extern void func_8001C5A0(void),func_80028708(void),func_800287D4(void),func_8002B9B4(void);
extern void func_8002DCC8(f32,f32,f32,s32 *);
extern void func_8002DDD4(f32,f32,f32,s32 *,s32 *);
extern void func_801B695C(void *,s32);
extern s32 func_801B6A68(T030Cmd5298 **,void *,s32);
extern void func_801BCB70(T030Cmd5298 **,s32,s32,s32,s32,s32,s32,s32,s32,s32,s32,f32,f32,u32,s32,void *);
extern s32 func_801BDF94(T030Cmd5298 **,void *,void *,f32,f32,f32,s32,f32,f32);
extern void func_801C2110(f32,f32 *,f32 *,f32 *);
extern void func_801C48E4();
extern void func_801C49A8(T030Cmd5298 **,s32,s32,s32,s32,s32,s32);
extern void func_801C4D6C(void);
extern void func_801C5064(T030Cmd5298 **,T030Render5298 *,s32,s32);
extern void func_801C51F8(T030Cmd5298 **);
extern s32 func_801C5E74(T030Cmd5298 **,T030Render5298 *,s32);
extern void guRotate(void *,f32,f32,f32,f32);
extern void guTranslate(void *,f32,f32,f32);
extern u8 D_4AC40[],D_801F3164[],D_801F3176[],D_801F3308[],D_801F331A[];
extern u8 D_8004A407,D_8004AC88;
extern void (*D_8004AA38)(void);
extern s32 D_8004AD00;
extern f32 D_800695CC,D_800695D0,D_800695D4,D_800695D8,D_800695DC,D_800695E0;
extern T030Sprite5298 D_801F2EA8[];
extern s32 D_801F3168,D_801F330C;
extern u16 D_801F31E2,D_801F3386;
extern s16 D_801F31E4,D_801F3388;
extern void (*D_801F3390)(T030Cmd5298 **,s32,s32,s32,void *,s32);
extern f32 D_80291F50[];
extern u8 D_80291F80[],D_80291FDC[],D_8029484C[],D_80294858[],D_802AAAC0[];
extern u32 (*D_80291FB0[])(T030Render5298 *,u32);
extern f64 D_80294898;
extern s32 D_802956F4;
extern u8 *D_802CA068;
extern f32 D_802D3990[];
extern u8 D_802D3985,D_802D399C,D_802D399F,D_802D39B4,D_802D39B6,D_802D39BA;
extern s8 D_802D39B5;
extern s32 D_802D39B0;

u8 func_801C5298(T030Cmd5298 **arg0, T030Render5298 *arg1) {
    s32 spEC;
    s32 spE8;
    s32 spE4;
    u32 spE0;
    f32 spDC;
    f32 spD8;
    f32 position[3];
    f32 velocity[3];
    s32 axis;
    s32 spB0;
    void *sp64;                                        /* compiler-managed */
    f32 sp5C;
    f32 *var_v1;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f14;
    f32 var_f16;
    f32 var_f18;
    s32 temp_hi;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    u16 temp_s0;
    u32 var_t0;
    u8 temp_a0;
    u8 temp_a1;
    T030Cmd5298 *temp_v1;
    T030Cmd5298 *temp_v1_10;
    T030Cmd5298 *temp_v1_11;
    T030Cmd5298 *temp_v1_12;
    T030Cmd5298 *temp_v1_13;
    T030Cmd5298 *temp_v1_14;
    T030Cmd5298 *temp_v1_2;
    T030Cmd5298 *temp_v1_3;
    T030Cmd5298 *temp_v1_4;
    T030Cmd5298 *temp_v1_5;
    T030Cmd5298 *temp_v1_6;
    T030Cmd5298 *temp_v1_7;
    T030Cmd5298 *temp_v1_8;
    T030Cmd5298 *temp_v1_9;
    void *var_v0;

    temp_f0 = (f32) (arg1->ticks - D_802D39B0);
    spD8 = temp_f0;
    if (!(D_802D39BA & 1)) {
        return 2 - func_801C5E74(arg0, arg1, (s32) temp_f0);
    }
    if (D_802D3985 == 5) {
        var_s2 = 0;
        temp_hi = (s32) temp_f0 % 213;
        var_s0 = temp_hi;
        if (temp_hi < 0x26C) {
            var_s1 = temp_hi * 0xFF;
            sp64 = &D_4AC40;
loop_5:
            spB0 = D_801F31E4 - (var_s0 >> 2);
            var_t0 = D_801F31E2 * ((var_s0 / 6) + 0x110);
            if (var_t0 >= 0x1D881U) {
                var_t0 = 0x90480;
            }
            temp_v1 = *arg0;
            *arg0 = temp_v1 + 1;
            temp_v1->w0 = 0x01030040;
            temp_v1->w1 = (u32)sp64;
            spE0 = var_t0;
            func_801B695C(&D_801F3164, 2 - D_8004A407);
            func_801BCB70(arg0, D_801F3168, func_801B6A68(arg0, &D_801F3164, 2 - D_8004A407), 0xC0, 0x110, 0x10, 0x10, 0, 0, 0xBF, 0x10F, (f32) var_s0, (f32) spB0, var_t0 >> 8, var_s1 / 640, &D_801F3176);
            var_s2 += 1;
            var_s1 += 0xD42B;
            var_s0 += 0xD5;
            if (var_s2 < 3) {
                if (var_s0 >= 0x26C) {

                } else {
                    goto loop_5;
                }
            }
        }
    } else {
        temp_f0_2 = (f32) D_80291FB0[D_802D3985](arg1, (u32)temp_f0);
        var_f16 = temp_f0_2;
        var_v1 = position;
        if (temp_f0_2 >= 240.0f) {
            var_f16 = 240.0f;
        }
        if ((D_802D3985 == 4) || (D_802D3985 == 0xA) || (D_802D3985 == 8) || (D_802D3985 == 1)) {
            var_f14 = var_f16 / 240.0f;
            for (axis = 0; axis < 3; axis++) {
                position[axis] = ((&D_802D3898)[axis+4] - (&D_802D3898)[axis])*var_f14 + (&D_802D3898)[axis];
            }
            spDC = var_f16;
        } else {
            temp_f14 = var_f16 / 240.0f;
            spDC = var_f16;
            sp5C = temp_f14;
            func_801C2110(temp_f14, &D_802D3898, position, velocity);
            var_f14 = sp5C;
        }
        D_800695CC = position[0];
        D_800695D0 = position[1];
        D_800695D4 = position[2];
        temp_f12 = (f32) ((f64) var_f14 * D_80294898);
        
        D_800695DC = (((1.0f - cosf(temp_f12)) / 2.0f) * ((&D_802D3880)[1] - (&D_802D3880)[0])) + (&D_802D3880)[0];
        D_800695D8 = (((1.0f - cosf(temp_f12)) / 2.0f) * ((&D_802D3880)[3] - (&D_802D3880)[2])) + (&D_802D3880)[2];
        D_800695E0 = 0.0f;
        func_8002B9B4();
        func_8002DDD4(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spEC, &spE8);
        func_8002DCC8(D_802D3990[0], D_802D3990[1], D_802D3990[2], &spE4);
        if (D_802D3985 == 1) {
            func_801C51F8(arg0);
            guRotate(arg1->matrices + (D_802956F4 << 6), D_800695DC, 0.0f, 1.0f, 0.0f);
            guTranslate(arg1->matrices + ((D_802956F4 + 1) << 6), -D_800695CC, -D_800695D0, -D_800695D4);
            temp_v1_2 = *arg0;
            *arg0 = temp_v1_2 + 1;
            temp_v1_2->w0 = 0x01020040;
            temp_v1_2->w1 = (u32) (arg1->matrices + (D_802956F4 << 6));
            temp_v1_3 = *arg0;
            *arg0 = temp_v1_3 + 1;
            temp_v1_3->w0 = 0x01000040;
            temp_v1_3->w1 = (u32) (arg1->matrices + ((D_802956F4 + 1) << 6));
            temp_v1_4 = *arg0;
            *arg0 = temp_v1_4 + 1;
            temp_v1_4->w0 = 0x06000000;
            temp_v1_4->w1 = (u32)&D_802AAAC0;
            temp_t5 = D_802956F4 + 2;
            D_802956F4 = temp_t5;
            temp_t5_2 = D_802956F4 + func_801BDF94(arg0, (temp_t5 << 6) + D_802CA068, &D_8029484C, -D_800695CC, -D_800695D0, -D_800695D4, 2, 5.0f, D_800695DC);
            D_802956F4 = temp_t5_2;
            D_802956F4 += func_801BDF94(arg0, (temp_t5_2 << 6) + D_802CA068, &D_80294858, -D_800695CC, -D_800695D0 - 200.0f, -D_800695D4, 2, 5.0f, D_800695DC);
        } else {
            func_8001C5A0();
            func_80028708();
            func_800287D4();
            func_80028708();
            func_800287D4();
            func_80028708();
            func_800287D4();
            temp_v1_5 = *arg0;
            *arg0 = temp_v1_5 + 1;
            temp_v1_5->w1 = 0;
            temp_v1_5->w0 = 0xE7000000;
            temp_v1_6 = *arg0;
            *arg0 = temp_v1_6 + 1;
            temp_v1_6->w0 = 0xFB000000;
            temp_v1_6->w1 = (u32) (((u8)D_802D39B5 << 0x18) | ((u8)D_802D39B5 << 0x10) | ((u8)D_802D39B5 << 8) | 0xFF);
            temp_v1_7 = *arg0;
            *arg0 = temp_v1_7 + 1;
            temp_v1_7->w1 = (u32)0xFF;
            temp_v1_7->w0 = 0xFA000000;
            func_80012B7C(arg0, D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0);
        }
        temp_v1_8 = *arg0;
        *arg0 = temp_v1_8 + 1;
        temp_v1_8->w1 = 0;
        temp_v1_8->w0 = 0xE7000000;
        if (D_802D39B4 != 0xFF) {
            temp_a1 = D_80291FDC[D_802D3985];
            if (temp_a1 != 0xC8) {
                func_801C48E4(arg1->id, temp_a1, D_802D399C, D_802D3985);
            } else {
                func_801C48E4(arg1->id, D_802D3985 & 0xFFFF, D_802D399C, D_802D3985);
            }
            func_801C49A8(arg0, arg1->id, spEC >> 3, spE8 >> 3, spE4 * 2, (s32) D_802D39B4, 0);
        }
        temp_v1_9 = *arg0;
        *arg0 = temp_v1_9 + 1;
        temp_v1_9->w1 = 0;
        temp_v1_9->w0 = 0xE7000000;
        temp_a0 = D_802D3985;
        if ((temp_a0 != 0) && (temp_a0 != 1)) {
            temp_v1_10 = *arg0;
            *arg0 = temp_v1_10 + 1;
            temp_v1_10->w0 = 0xFB000000;
            temp_v1_10->w1 = (u32) (((u8)D_802D39B5 << 0x18) | ((u8)D_802D39B5 << 0x10) | ((u8)D_802D39B5 << 8) | 0xFF);
            temp_v1_11 = *arg0;
            *arg0 = temp_v1_11 + 1;
            temp_v1_11->w1 = (u32)0xFF;
            temp_v1_11->w0 = 0xFA000000;
            func_800131A4(arg0, D_800695CC, D_800695D0, D_800695D4, D_800695D8, D_800695DC, D_800695E0);
            D_8004AA38();
        }
        if (D_8004AD00 < 0x100) {
            D_8004AD00 += 1;
        } else {
            D_8004AD00 = 0;
        }
        if (temp_a0 == 8) {
            temp_s0 = D_801F2EA8[8].scale;
            D_801F2EA8[8].scale = (u16) ((s32) (temp_s0 * 0x133) >> 8);
            func_801B695C(&D_801F3308, 0);
            func_801BCB70(arg0, D_801F330C, func_801B6A68(arg0, &D_801F3308, 0), 0xC0, 0x110, -0x10, 0x10, 0, 0, 0xBF, 0x10F, 580.0f, (f32) (D_801F3388 - 0x28), (u32) D_801F3386, 0xFF, &D_801F331A);
            D_801F3390(arg0, 0x28, -0x28, (s32) spDC, &D_801F3308, 1);
            D_801F3386 = temp_s0;
        }
    }
    temp_v1_12 = *arg0;
    *arg0 = temp_v1_12 + 1;
    temp_v1_12->w0 = 0x06000000;
    temp_v1_12->w1 = (u32)&D_80291F80;
    temp_v1_13 = *arg0;
    *arg0 = temp_v1_13 + 1;
    temp_v1_13->w0 = 0xF6A0077C;
    temp_v1_13->w1 = (u32) (((0x1EA - (D_802D399F * 0x1E)) & 0x3FF) * 4);
    temp_v1_14 = *arg0;
    *arg0 = temp_v1_14 + 1;
    temp_v1_14->w1 = 0;
    temp_v1_14->w0 = 0xE7000000;
    func_801C5064(arg0, arg1, 0xFF, 0);
    if (D_8004AC88 == 2) {
        D_800695D8 = 5.0f;
    }
    if (D_80291F50[D_802D3985] < spD8) {
        D_802D39BA &= 0xFE;
        D_802D39B0 = arg1->ticks;
        func_801C4D6C();
    }
    return D_802D39B6;
}
