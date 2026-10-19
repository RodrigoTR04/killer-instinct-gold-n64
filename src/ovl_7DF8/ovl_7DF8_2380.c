#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801ADEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AF424.s")

typedef struct { u8 pad[0xC8]; f32 x, y, z; } T025Position;
void func_801AF5B8(T025Position *arg0) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = -600.0f;
}

extern s32 D_802A2178;

void func_801AF5D4(s32 arg0) {
    D_802A2178 |= arg0;
}

typedef struct { s32 pad0[2]; s32 flags; s32 padC; s32 state; u8 pad14[0x54]; } T025Effect;
extern T025Effect D_801D18B8[];
extern T025Effect D_801D2DD8[];
extern s32 D_802A2178;
void func_801AF5EC(s32 arg0) {
    s32 i;
    D_802A2178 &= -1 ^ arg0;
    for (i = 0; i < 52; i++) {
        if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
    }
}

extern s32 D_802A2178;

s32 func_801AF67C(s32 arg0) {
    return D_802A2178 & arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AF68C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AFA48.s")

f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    return ((arg1 - arg0) * ((f32) arg2 / (f32) arg3)) + arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AFAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AFFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B01EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B0520.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B0668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B0A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B0CDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B1210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B132C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B17BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B18BC.s")

f32 func_801B19F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    return ((arg1 - arg0) * ((f32) arg2 / (f32) arg3)) + arg0;
}

extern f32 sqrtf(f32);                             /* extern */

f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_f0;

    temp_f0 = sqrtf((arg1 * arg1) + (arg0 * arg0));
    arg1 = ((arg2 - temp_f0) * arg1) / temp_f0;
    if (arg1 < 0.0f) {
        return 0.0f;
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B1A7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B1DE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B2010.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B21B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B2358.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B24FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B26A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B2844.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B29E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B2B8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B2EF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B310C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B3324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B353C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B3754.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B396C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B3B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B3DB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B4300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B4324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B43A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B446C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B4590.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B465C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B47A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B5534.s")

s32 func_801B55DC(u8 arg0) {
    s32 temp_t6;

    temp_t6 = arg0;
    if (temp_t6 < 0xA) {
        return (temp_t6 + 0x30) << 0x18;
    }
    return (((temp_t6 / 10) + 0x30) << 0x18) + (((temp_t6 % 10) + 0x30) << 0x10);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B5650.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B5DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B6528.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B677C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B695C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B6A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B6BD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B6E4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B849C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B994C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801B9A04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BA088.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BA280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BA470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BA674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BA884.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BAA78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BADEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BB024.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BB258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BB464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BB594.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BB7B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BBB60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BBC84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BBE88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BC1B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BCB70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BD200.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BD270.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BD3FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BD640.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BDA6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BDF94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BE540.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BE660.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BE790.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BE910.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BEA74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BED0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BEEA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BEFFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF0E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF190.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF678.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF720.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF788.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF914.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BF988.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BFA40.s")

extern void func_801CC784(void);
extern void func_801CC878(void);
extern void func_801BEFFC(void);
void func_801BFB10(void) {
    func_801CC784();
    func_801CC878();
    func_801BEFFC();
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BFB40.s")

extern void func_801ADC64(s32);
extern void func_801AF5D4(s32);
extern void func_801AF5EC(s32);
extern s32 D_802D37D0;
extern s32 D_802D37F8;
void func_801BFC08(s32 arg0) {
    if (arg0 == 0) D_802D37F8 += 0x280;
    else D_802D37F8 = arg0 + 0xA0;
    if (D_802D37F8 != 0xA0) {
        if (++D_802D37D0 >= 14) {
            func_801ADC64(0);
            func_801AF5EC(0xFFFF);
            func_801AF5D4(16);
        }
    }
}


extern s32 D_802D37D0, D_802D37F8;
void func_801BFC8C(void) {
    if (D_802D37D0-- <= 0) D_802D37D0 = 13;
    D_802D37F8 = 160;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801BFCBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C0610.s")

extern void func_801BF190(s32, s32, s32);
extern void func_801BFC08(s32);
extern void func_801C0610(s32, u32);
extern s8 D_801CD454;
extern s32 D_802CA068, D_802D37D0;
extern s32 D_802D37F8;
void func_801C0784(s32 arg0, u32 arg1) {
    if ((u32)D_802D37F8 < arg1) func_801BFC08(arg1);
    if (arg1 + 0x280 < (u32)D_802D37F8) D_802D37F8 = arg1 + 0x280;
    func_801C0610(arg0, arg1);
    func_801BF190(arg0, D_802CA068, D_802D37D0);
    D_801CD454 = 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C0800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C08F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C11F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C1434.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C1704.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C17D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C1C34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C2110.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C224C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C23C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C2ADC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C2D34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C2F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C317C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3524.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3580.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C35AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C35D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3758.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C3E40.s")

extern u8 D_8004EA9B[], D_8004EA9D[], D_802D3959, D_802D395A;
void func_801C4040(u8 arg0) {
    if (arg0 != 0) {
        D_802D3959 = D_8004EA9B[arg0];
        D_802D395A = D_8004EA9D[arg0];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C407C.s")

void func_801C4238(void) {}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4240.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C47E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C48E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C49A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4BD0.s")

extern f32 D_802D3880;
extern f32 D_802D3884;
extern f32 D_802D3888;
extern f32 D_802D388C;
extern f32 D_802D3898;
extern f32 D_802D389C;
extern f32 D_802D38A0;
extern f32 D_802D38A4;
extern f32 D_802D38A8;
extern f32 D_802D38AC;
extern f32 D_802D38B0;
extern f32 D_802D38B4;
extern f32 D_802D38B8;
extern f32 D_802D38BC;
extern f32 D_802D38C0;
extern f32 D_802D38C4;

void func_801C4C64(f32 *arg0, f32 *arg1) {
    D_802D3898 = arg0[0];
    D_802D38A8 = arg0[4];
    D_802D38B8 = arg0[8];
    D_802D3880 = arg1[0];
    D_802D389C = arg0[1];
    D_802D38AC = arg0[5];
    D_802D38BC = arg0[9];
    D_802D3884 = arg1[1];
    D_802D38A0 = arg0[2];
    D_802D38B0 = arg0[6];
    D_802D38C0 = arg0[10];
    D_802D3888 = arg1[2];
    D_802D38A4 = arg0[3];
    D_802D38B4 = arg0[7];
    D_802D38C4 = arg0[11];
    D_802D388C = arg1[3];
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4D28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C4E38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C5064.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C51F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C5298.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C5E74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C67CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C6A80.s")

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C6BA4(s32 arg0, u32 arg1) {
    u8 temp_t2;

    if (arg1 >= 0xCEU) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x75);
            D_802D399C = 0x29;
            func_8002F6F4(D_80066C40, 0xE0, &D_8004A258, &D_802D399C);
        }
        if (D_802D399C-- < 0x1B) {
            D_802D399C = 0x1B;
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
            func_8002F6F4(D_80066C40, 0xDC, &D_8004A258, &D_802D399C);
        }
    }
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;
extern s8 D_802D39B5;

u32 func_801C6C78(s32 arg0, u32 arg1) {
    s32 var_v1;
    u8 temp_t2;
    u8 temp_t9;

    if (arg1 >= 0xD3U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x83);
        }
        var_v1 = (D_802D399C += 2);
        if (var_v1 >= 0x2A) {
            var_v1 = (D_802D399C = 0x29);
        }
        if (var_v1 == 0x18) {
            func_8002F6F4(D_80066C40, 0xC2, &D_8004A258);
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
        }
    }
    D_802D39B5 = 0x40;
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C6D40.s")

extern u8 D_802D399C;

s32 func_801C6E6C(s32 arg0, s32 arg1) {
    D_802D399C = 1;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern s32 D_800698C4;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C6E84(s32 arg0, u32 arg1) {
    u8 temp_t9;

    if (arg1 >= 0xF1U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x82);
            func_8002F6F4(D_80066C40, 0xED, &D_8004A258);
        }
        D_802D399C += 2;
        if (D_802D399C >= 0x2C) {
            D_802D399C = 0x2B;
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
        }
    }
    D_800698C4 = 1;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;
extern u8 D_802D39B4;

u32 func_801C6F3C(s32 arg0, u32 arg1) {
    s32 temp_v1;
    u8 temp_t2;
    u8 temp_t9;

    if (arg1 >= 0xD3U) {
        if (D_802D399E == 0) {
            func_801C4BD0(0x84);
        }
        temp_v1 = (D_802D399C += 2);
        if (temp_v1 >= 0x28) {
            D_802D399C = 0x27;
        } else if (temp_v1 == 0x10) {
            func_8002F6F4(D_80066C40, 0xF8, &D_8004A258);
        }
    } else {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 2;
            func_8002F6F4(D_80066C40, 0xF0, &D_8004A258);
        }
    }
    D_802D39B4 = 1;
    return arg1;
}

extern u8 D_802D39B4;

s32 func_801C701C(s32 arg0, s32 arg1) {
    D_802D39B4 = 0xFF;
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern f32 D_8004AC84;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399E;

u32 func_801C7034(s32 arg0, u32 arg1) {
    s32 var_v1;

    u8 temp_t2;

    if (arg1 < 0xF0U) {
        D_8004AC84 = 390.0f;
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
        }
    } else {
        if (D_802D399E == 0) {
            func_801C4BD0(0xAB);
        }
        var_v1 = (D_802D399C += 2);
        if (var_v1 >= 0x47) {
            var_v1 = (D_802D399C = 0x47);
        }
        if (var_v1 == 0x1C) {
            func_8002F6F4(D_80066C40, 0x103, &D_8004A258);
        }
        arg1 = 0xF0;
    }
    return arg1;
}

extern s32 func_8002F6F4();
extern void func_801C4BD0();
extern u8 D_8004A258;
extern s32 D_80066C40;
extern u8 D_802D399C;
extern u8 D_802D399D;
extern u8 D_802D399E;

u32 func_801C7100(s32 arg0, u32 arg1) {
    s32 temp_v1;
    u8 temp_t2;

    if (arg1 < 0x78U) {
        D_802D399C += 1;
        if (D_802D399C >= 0x15) {
            D_802D399C = 1;
        }
    } else {
        if (D_802D399E == 0) {
            func_801C4BD0(0xA0);
            D_802D399D = 0;
            func_8002F6F4(D_80066C40, 0x8B, &D_8004A258);
        }
        if (D_802D399E == 0xA0) {
            temp_v1 = (D_802D399C += 2);
            if (temp_v1 >= 0xC) {
                D_802D399D += 1;
                if (D_802D399D < 0xA) {
                    D_802D399C = 0xC;
                } else if (temp_v1 >= 0x1D) {
                    D_802D399C = 0x1D;
                }
            }
        }
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C71FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C72B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7310.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C780C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C78B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7A98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7CD0.s")

typedef struct {
    u8 b[6];
} T021Six;
extern T021Six D_80127C68[];
void func_801C7E4C(u8 arg0) {
    T021Six *p;

    p = &D_80127C68[arg0];
    p->b[0] = 6;
    p->b[1] = 1;
    p->b[2] = 3;
    p->b[3] = 7;
    p->b[4] = 2;
    p->b[5] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7E98.s")

extern void func_801C78B0();

void func_801C7F10(void) {
    func_801C78B0(0, 0);
    func_801C78B0(1, 1);
}

extern void func_801C78B0();
extern u8 D_80127D30;
extern u8 D_80127D31;

void func_801C7F40(void) {
    func_801C78B0(0, (D_80127D30 + 1) & 0xFF);
    func_801C78B0(1, (D_80127D31 + 1) & 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C7F90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8004.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C80F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C85C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C86A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8868.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8AE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8C24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8DBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C8F28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C90D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C9584.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C9698.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801C9B14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CA784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CA7E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CA91C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CAA00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CB998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CBA2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CBBE0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CBCCC.s")

extern s32 osCreateMesgQueue();
extern s32 osCreateThread();
extern s32 osSetEventMesg();
extern s32 osStartThread();
extern u8 D_8011E650;
extern u8 D_802D3E18;
extern u8 D_802D3FC8;
extern u8 D_802D3FE0;
extern void func_801CBCCC();

void func_801CBED0(void) {
    osCreateThread(&D_802D3E18, 0x49, &func_801CBCCC, 0, &D_8011E650, 2);
    osCreateMesgQueue(&D_802D3FC8, &D_802D3FE0, 2);
    osSetEventMesg(0xE, &D_802D3FC8, 8);
    osStartThread(&D_802D3E18);
}

extern s32 osSendMesg();
extern s32 osSetThreadPri();
extern u8 D_802D3E18;
extern u8 D_802D3FC8;

void func_801CBF50(void) {
    osSendMesg(&D_802D3FC8, 1, 1);
    osSetThreadPri(&D_802D3E18, 0x7F);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CBF8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC1A4.s")

s32 __osContDataCrc();
extern s32 osEepromLongWrite();
s32 osEepromProbe();
extern u8 D_800684E0;
extern u8 D_802D3E16;

void func_801CC264(u8 *arg0) {
    D_802D3E16 = osEepromProbe(&D_800684E0);
    arg0[0x1FF] = __osContDataCrc(arg0);
    if (D_802D3E16 != 0) {
        osEepromLongWrite(&D_800684E0, 0, arg0, 0x200);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC2C8.s")

extern s32 func_80034630();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

void func_801CC350(s32 arg0, s32 arg1) {
    func_80034630((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC3BC.s")

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

void func_801CC524(s32 arg0, s32 arg1) {
    func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 0, 0, 0x300, &D_802D3A30);
}

extern s32 func_80035690();
extern u8 D_80292790;
extern u8 D_80292794;
extern u8 D_802D3D30;

void func_801CC58C(s32 arg0, s32 arg1) {
    func_80035690((arg1 * 0x68) + &D_802D3D30, 0x3031, 0x4E4B4945, &D_80292794, &D_80292790, 0x300, arg0);
}

extern s32 func_80035320();
extern u8 D_802D3A30;
extern u8 D_802D3D30;

void func_801CC600(s32 arg0, s32 arg1) {
    func_80035320((arg1 * 0x68) + &D_802D3D30, arg0, 1, 0, 0x300, &D_802D3A30);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC784.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC878.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CC908.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CCAB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CCBCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CCD74.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CCDE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CCEAC.s")

extern s32 osSendMesg();
extern s32 D_802D3E00;
extern u8 D_802D3E0E;
extern u8 D_802D3FC8;

u8 func_801CD038(s32 arg0, s32 arg1) {
    D_802D3E00 = arg0;
    osSendMesg(&D_802D3FC8, (arg1 << 8) + 4, 1);
    return D_802D3E0E;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CD078.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CD100.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CD174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801CD1F0.s")

s32 func_801BE540(s32, s32, s32, s32, f32, f32, s32, s32, s32, s32, f32); /* extern */
s32 func_801CCD74(s32 *);                           /* extern */

s32 func_801CD3BC(s32 arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 sp3C;

    if (func_801CCD74(&sp3C) != 0) {
        return func_801BE540(arg0, arg1, sp3C, arg2, arg3, -1800.0f, 0xFF, 0, 0, 0xFF, 1.0f);
    }
    return 0;
}
