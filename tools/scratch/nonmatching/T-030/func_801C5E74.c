/* DRAFT. Remaining diff: Palette conversion loop unrolling, asset/coordinate pointer registers, frame and rendering scheduling differ. */
#include "common.h"

typedef struct { u32 w0,w1; } T030Cmd5E74;
typedef struct { s32 id,ticks; u8 pad8[0xF0]; u8 *matrices; } T030Render5E74;
typedef struct { u32 start,end; } T030Asset5E74;
typedef struct { u8 pad[12]; u8 *texture; u8 tail[0x7C]; } T030Sprite5E74;
extern void boot_dma(u32,void *,s32,void *);
extern void boot_inflate(void *,void *,void *,void *);
extern void func_8002AAEC();
extern void func_801ADB20(void);
extern void func_801BC1B0(T030Cmd5E74 **,void *,s32,s32,s32,s32,s32,s32,s32,s32,s32,f32,f32,s32,s32);
extern s32 func_801BDF94(T030Cmd5E74 **,void *,void *,f32,f32,f32,s32,f32,f32);
extern void func_801C0610(T030Cmd5E74 **);
extern void func_801C2D34(T030Cmd5E74 **,s32,s32,s32,s32);
extern void func_801C4D6C(void);
extern void func_801C5064(T030Cmd5E74 **,T030Render5E74 *,s32,s32);
extern void func_801C51F8(T030Cmd5E74 **);
extern u8 D_8004A422[],D_8004A430[],D_8007D900[],D_8007DC00[],D_800CA610[],D_800CC610[];
extern T030Sprite5E74 D_801F2EA8[];
extern T030Asset5E74 D_80291FE8[];
extern u8 D_80292050[],D_80294864[],D_80294870[],D_8029487C[];
extern s16 D_802920E0[];
extern s32 D_802956F4;
extern u8 D_80295720;
extern u8 *D_802CA068,*D_802D3980;
extern u8 D_802D3985,D_802D39BA;
extern s32 D_802D39B0;
extern u16 D_802D39B8;

s32 func_801C5E74(T030Cmd5E74 **arg0, T030Render5E74 *arg1, s32 arg2) {
    u8 *spDC;
    s32 spD4;
    s32 spA0;
    s32 sp9C;
    u8 *sp98;
    u8 *sp50;
    u8 *var_a0;
    u8 *var_t0_2;
    u8 *var_v1_2;
    s16 var_v0;
    s32 temp_a0;
    s32 temp_t6;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_a3;
    s32 var_t0;
    s32 var_t2;
    u8 temp_t7;
    u8 temp_t8;
    u8 temp_v1;
    u8 temp_v1_2;
    u8 var_v1;
    T030Cmd5E74 *temp_v0;
    T030Cmd5E74 *temp_v1_10;
    u8 *temp_v1_11;
    T030Cmd5E74 *temp_v1_12;
    T030Cmd5E74 *temp_v1_13;
    T030Cmd5E74 *temp_v1_14;
    T030Cmd5E74 *temp_v1_15;
    T030Cmd5E74 *temp_v1_16;
    T030Cmd5E74 *temp_v1_17;
    T030Cmd5E74 *temp_v1_18;
    T030Cmd5E74 *temp_v1_19;
    T030Cmd5E74 *temp_v1_20;
    T030Cmd5E74 *temp_v1_21;
    T030Cmd5E74 *temp_v1_22;
    T030Cmd5E74 *temp_v1_23;
    T030Cmd5E74 *temp_v1_24;
    T030Cmd5E74 *temp_v1_25;
    T030Cmd5E74 *temp_v1_26;
    T030Cmd5E74 *temp_v1_27;
    T030Cmd5E74 *temp_v1_3;
    T030Cmd5E74 *temp_v1_4;
    T030Cmd5E74 *temp_v1_5;
    T030Cmd5E74 *temp_v1_6;
    T030Cmd5E74 *temp_v1_7;
    T030Cmd5E74 *temp_v1_8;
    T030Cmd5E74 *temp_v1_9;
    s16 *var_t3;

    temp_v1 = D_802D3985;
    var_t0 = 0xFF;
    if (((temp_v1 == 5) || (temp_v1 == 1)) && ((s32) D_802D39B8 < 0x7918)) {
        spD4 = 0xFF;
        func_8002AAEC(0x7FFF - D_802D39B8, &D_802D39B8);
        var_t0 = 0xFF;
        D_802D39B8 += 0x300;
    }
    if (D_80291FE8[temp_v1].start == 0) {
        spD4 = 0xFF;
        D_802D39BA &= 0xFD;
        func_801C4D6C();
        var_t0 = 0xFF;
    }
    if ((D_802D3980 == 0) && (D_802D39BA & 2)) {
        temp_v0 = &D_80291FE8[D_802D3985];
        temp_a0 = temp_v0->w0;
        D_802D3980 = D_800CA610;
        spD4 = var_t0;
        boot_dma(temp_a0, D_800CC610, temp_v0->w1 - temp_a0, D_800CA610);
        func_801ADB20();
        boot_inflate(D_802D3980 + 0x2000, D_8007D900, D_802D3980, &D_802D3980);
        {
            u8 *rgb = D_8007D900;
            u16 *palette = (u16 *)D_8007D900;
            s32 i;
            for (i = 0; i < 256; i++) {
                palette[i] = ((rgb[i*3] << 8)&0xF800) | ((rgb[i*3+1]*8)&0x7C0) | ((rgb[i*3+2]>>2)&0x3E) | 1;
            }
        }
    }
    temp_v1_2 = D_802D39BA;
    temp_v0_2 = temp_v1_2 & 2;
    if (temp_v1_2 & 6) {
        if (temp_v0_2 != 0) {
            var_t0 = (0x1F4 - arg2) * 4;
        } else {
            var_t0 = (0x2BC - arg2) * 4;
        }
        if (var_t0 < 0xFF) {
            if (var_t0 < 0) {
                var_t0 = 0;
            }
        } else {
            var_t0 = 0xFE;
        }
    }
    if (arg2 < 0x40) {
        var_t0 = arg2 * 4;
    }
    if (temp_v0_2 != 0) {
        spDC = D_8007DC00;
        spD4 = var_t0;
        func_801C51F8(arg0);
        temp_v1_3 = *arg0;
        *arg0 = temp_v1_3 + 1;
        temp_v1_3->w0 = 0xFD100000;
        temp_v1_3->w1 = (u32)D_8007D900;
        temp_v1_4 = *arg0;
        *arg0 = temp_v1_4 + 1;
        temp_v1_4->w1 = 0;
        temp_v1_4->w0 = 0xE8000000;
        temp_v1_5 = *arg0;
        *arg0 = temp_v1_5 + 1;
        temp_v1_5->w1 = (u32)0x07000000;
        temp_v1_5->w0 = 0xF5000100;
        temp_v1_6 = *arg0;
        *arg0 = temp_v1_6 + 1;
        temp_v1_6->w1 = 0;
        temp_v1_6->w0 = 0xE6000000;
        temp_v1_7 = *arg0;
        *arg0 = temp_v1_7 + 1;
        temp_v1_7->w1 = (u32)0x073FC000;
        temp_v1_7->w0 = 0xF0000000;
        temp_v1_8 = *arg0;
        *arg0 = temp_v1_8 + 1;
        temp_v1_8->w1 = 0;
        temp_v1_8->w0 = 0xE7000000;
        temp_v1_9 = *arg0;
        *arg0 = temp_v1_9 + 1;
        temp_v1_9->w1 = (u32)D_80292050;
        temp_v1_9->w0 = 0x06000000;
        if (var_t0 < 0xFF) {
            temp_v1_10 = *arg0;
            temp_v0_3 = var_t0 & 0xFF;
            *arg0 = temp_v1_10 + 1;
            temp_v1_10->w0 = 0xFB000000;
            temp_v1_10->w1 = (u32) ((temp_v0_3 << 0x18) | (temp_v0_3 << 0x10) | (temp_v0_3 << 8) | 0xFF);
        }
        spD4 = var_t0;
        func_801BC1B0(arg0, spDC, 2, 0x100, 0x96, 0x20, 0x1E, 0, 0, 0xFF, 0x95, 0.0f, 0.0f, 0xA00, 0);
    }
    if (temp_v1_2 & 0xC) {
        spD4 = var_t0;
        func_801C0610(arg0);
    }
    if (temp_v1_2 & 6) {
        func_801C5064(arg0, arg1, var_t0 & 0xFF, (temp_v1_2 & 2) == 0);
    }
    if ((temp_v1_2 & 8) && (D_80295720 != 0)) {
        temp_v1_11 = D_8004A430 + D_80295720 * 16;
        var_t0_2 = D_80294864;
        sp50 = D_80292050;
        spA0 = (s32) temp_v1_11[-15];
        sp9C = (s32) temp_v1_11[-16];
        if (D_80295720 == 2) {
            var_t0_2 = D_80294870;
        }
        temp_v1_12 = *arg0;
        *arg0 = temp_v1_12 + 1;
        temp_v1_12->w1 = (u32)0x80000;
        temp_v1_12->w0 = 0xBA001301;
        sp98 = var_t0_2;
        func_801C2D34(arg0, 0x3E8, -0xFA, -0x258, arg1->ticks);
        temp_t6 = D_802956F4 + func_801BDF94(arg0, (D_802956F4 << 6) + D_802CA068, sp98, -320.0f, 210.0f, -500.0f, 0, 1.0f, 0.0f);
        D_802956F4 = temp_t6;
        D_802956F4 += func_801BDF94(arg0, (temp_t6 << 6) + D_802CA068, D_8029487C, -360.0f, 150.0f, -500.0f, 0, 1.0f, 0.0f);
        temp_v1_13 = *arg0;
        var_t2 = 0;
        *arg0 = temp_v1_13 + 1;
        temp_v1_13->w0 = 0x06000000;
        temp_v1_13->w1 = (u32)sp50;
        temp_v1_14 = *arg0;
        *arg0 = temp_v1_14 + 1;
        temp_v1_14->w1 = 0;
        temp_v1_14->w0 = 0xBA000E02;
        if (spA0 > 0) {
            var_t3 = D_802920E0 + spA0*11;
            do {
                temp_v1_15 = *arg0;
                var_a3 = -0x32;
                *arg0 = temp_v1_15 + 1;
                temp_v1_15->w1 = 0;
                temp_v1_15->w0 = 0xE7000000;
                if (var_t2 < sp9C) {
                    temp_v1_16 = *arg0;
                    *arg0 = temp_v1_16 + 1;
                    temp_v1_16->w1 = (u32)-0x805;
                    temp_v1_16->w0 = 0xFC11FE23;
                } else {
                    temp_v1_17 = *arg0;
                    *arg0 = temp_v1_17 + 1;
                    temp_v1_17->w1 = (u32)0xFFFCF279;
                    temp_v1_17->w0 = 0xFCFFFFFF;
                }
                var_v0 = var_t3[-11];
                if (var_v0 >= 0x1F5) {
                    var_v0 -= 0x3E8;
                    var_a3 = 0x32;
                }
                if (var_v0 >= 0x1F5) {
                    var_v0 -= 0x3E8;
                    var_a3 = 0x96;
                }
                temp_v1_18 = *arg0;
                *arg0 = temp_v1_18 + 1;
                temp_v1_18->w1 = (u32) D_801F2EA8[D_8004A422[var_t2 + D_80295720*16]].texture;
                temp_v1_18->w0 = 0xFD100000;
                temp_v1_19 = *arg0;
                *arg0 = temp_v1_19 + 1;
                temp_v1_19->w1 = (u32)0x07080200;
                temp_v1_19->w0 = 0xF5100000;
                temp_v1_20 = *arg0;
                *arg0 = temp_v1_20 + 1;
                temp_v1_20->w1 = 0;
                temp_v1_20->w0 = 0xE6000000;
                temp_v1_21 = *arg0;
                *arg0 = temp_v1_21 + 1;
                temp_v1_21->w1 = (u32)0x0778F0BB;
                temp_v1_21->w0 = 0xF3000000;
                temp_v1_22 = *arg0;
                *arg0 = temp_v1_22 + 1;
                temp_v1_22->w1 = 0;
                temp_v1_22->w0 = 0xE7000000;
                temp_v1_23 = *arg0;
                *arg0 = temp_v1_23 + 1;
                temp_v1_23->w0 = 0xF5101600;
                temp_v1_23->w1 = (u32)0x80200;
                temp_v1_24 = *arg0;
                *arg0 = temp_v1_24 + 1;
                temp_v1_24->w0 = 0xF2000000;
                temp_v1_24->w1 = (u32)0xAC0AC;
                temp_v1_25 = *arg0;
                *arg0 = temp_v1_25 + 1;
                temp_v1_25->w0 = (s32) (((((var_v0 + 0x182) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((var_a3 + 0x132) * 4) & 0xFFF));
                temp_v1_25->w1 = (u32) (((((var_v0 + 0x140) * 4) & 0xFFF) << 0xC) | (((var_a3 + 0xF0) * 4) & 0xFFF));
                temp_v1_26 = *arg0;
                *arg0 = temp_v1_26 + 1;
                temp_v1_26->w1 = (u32)0x560;
                temp_v1_26->w0 = 0xB3000000;
                temp_v1_27 = *arg0;
                *arg0 = temp_v1_27 + 1;
                temp_v1_27->w0 = 0xB2000000;
                temp_v1_27->w1 = (u32)0x02AAFD56;
                var_t2 += 1;
                var_t3++;
            } while (var_t2 != spA0);
        }
    }
    var_v1 = D_802D39BA;
    if (var_v1 & 2) {
        if (arg2 >= 0x1F5) {
            D_802D39BA = var_v1 & 0xFC;
            D_802D39B0 = arg1->ticks;
            func_801C4D6C();
            var_v1 = D_802D39BA;
        }
    } else if (var_v1 & 4) {
        if (arg2 >= 0x2BD) {
            D_802D39BA = 0;
            goto block_51;
        }
    } else if ((var_v1 & 8) && (arg2 >= 0x2BD)) {
        D_802D39BA = 0;
block_51:
        var_v1 = 0;
    }
    return (var_v1 == 0) & 0xFF;
}
