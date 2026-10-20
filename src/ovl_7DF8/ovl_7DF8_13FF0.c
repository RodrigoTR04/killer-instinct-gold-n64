#include "common.h"

extern void func_801CC784(void);
extern void func_801CC878(void);
extern void func_801BEFFC(void);

void func_801BFB10(void) {
    func_801CC784();
    func_801CC878();
    func_801BEFFC();
}

typedef struct { s32 x, y; } T023PairB40;
extern void func_801ADAD4(s32);
extern T023PairB40 D_80128300, D_802D37D8, D_802D37E0, D_802D37F0;
extern s32 D_80295700, D_802956FC, D_802956F8;
extern s32 D_802D37D0, D_802D37F8, D_802D3820, D_802D3824;
extern u8 D_802D37EA[];
void func_801BFB40(u8 arg0) {
    D_802D37D0 = -1;
    D_802D37F0.x = D_80128300.x;
    D_802D37F0.y = D_80128300.y;
    D_802D37EA[0] = D_802D37EA[1] = 0;
    D_802D37D8.x = D_802D37D8.y = 40;
    D_802D37E0.x = D_802D37E0.y = 32;
    D_802D37F8 = 0;
    D_802D3820 = 2560;
    D_802D3824 = 2560;
    if (arg0) func_801ADAD4(42);
    D_802956F8 = D_802956FC = D_80295700 = 0;
}

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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801BFCBC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C0610.s")

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

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C0800.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C08F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C11F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1434.s")

extern s32 D_80127C30[];
extern u8 D_80128308[], D_8012830A[];
extern u8 D_80128310[][11], D_80128328[][11];
void func_801C1704(u8 player) {
    s32 i;


    D_80128308[player] = 0;
    D_8012830A[player] = 0;
    for (i = 0; i < 11; i++) {
        D_80128310[player][i] = 0;
        D_80128328[player][i] = 0;
    }
    D_80127C30[player] = 100;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C17D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1990.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C1C34.s")

void func_801C2110(f32 t, f32 *coef, f32 *position, f32 *velocity) {
    f32 two = 2.0f;
    f32 three = 3.0f;
    f32 t2;
    f32 t3;

    t2 = t * t;
    t3 = t2 * t;
    position[0] = coef[0] * t3 + coef[1] * t2 + coef[2] * t + coef[3];
    position[1] = coef[4] * t3 + coef[5] * t2 + coef[6] * t + coef[7];
    position[2] = coef[8] * t3 + coef[9] * t2 + coef[10] * t + coef[11];
    velocity[0] = three * coef[0] * t2 + two * coef[1] * t + coef[2];
    velocity[1] = three * coef[4] * t2 + two * coef[5] * t + coef[6];
    velocity[2] = three * coef[8] * t2 + two * coef[9] * t + coef[10];
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C224C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C23C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2ADC.s")

typedef union { struct { u32 w0, w1; } words; u64 full; } T030Cmd2D34;
typedef struct { u8 pad[0xF8]; u8 *matrices; } T030Render2D34;
extern void guRotate(void *, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80285168[];
extern s32 D_802956F4;
extern T030Render2D34 D_802C9F70;

void func_801C2D34(T030Cmd2D34 **arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
    T030Cmd2D34 *temp_v0;
    T030Cmd2D34 *temp_v0_2;
    T030Cmd2D34 *temp_v0_3;
    T030Cmd2D34 *temp_v0_4;
    T030Cmd2D34 *temp_v0_5;
    T030Cmd2D34 *temp_v0_6;
    T030Cmd2D34 *temp_v0_7;
    temp_v0 = (*arg0)++;
    temp_v0->words.w0 = 0xBA001301; temp_v0->words.w1 = 0x80000;
    temp_v0_2 = (*arg0)++;
    temp_v0_2->words.w1 = 0;
    temp_v0_2->words.w0 = 0xBA000E02;
    temp_v0_3 = (*arg0)++;
    temp_v0_3->full = 0xB600000000060004ULL;
    guRotate(((D_802956F4 + 2) << 6) + D_802C9F70.matrices, (f32) (arg4 * 2), 0.0f, 1.0f, 0.0f);
    guRotate(((D_802956F4 + 1) << 6) + D_802C9F70.matrices, -8.0f, 1.0f, 0.0f, 0.0f);
    if (arg1 >= 0x77)
    {
        arg1 = -0x163;
    }
    else
    {
        arg1 = (arg1 * 3) - 0x2C6;
    }
    guTranslate((D_802956F4 << 6) + D_802C9F70.matrices, (f32) arg1, (f32) arg2, (f32) arg3);
    temp_v0_4 = (*arg0)++;
    temp_v0_4->words.w0 = 0x01020040;
    temp_v0_4->words.w1 = (u32) ((D_802956F4 << 6) + D_802C9F70.matrices);
    temp_v0_5 = (*arg0)++;
    temp_v0_5->words.w0 = 0x01000040;
    temp_v0_5->words.w1 = (u32) (((D_802956F4 + 1) << 6) + D_802C9F70.matrices);
    temp_v0_6 = (*arg0)++;
    temp_v0_6->words.w0 = 0x01000040;
    temp_v0_6->words.w1 = (u32) (((D_802956F4 + 2) << 6) + D_802C9F70.matrices);
    D_802956F4 += 3;
    temp_v0_7 = (*arg0)++;
    temp_v0_7->words.w0 = 0x06000000; temp_v0_7->words.w1 = (u32)&D_80285168;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C2F5C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C317C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C3524.s")

extern void func_801C35D8();
extern u8 D_80290DF8;
void func_801C3580(s32 arg0, s32 arg1)
{
  func_801C35D8(arg0, &D_80290DF8, 0x17, arg1);
}

extern void func_801C35D8();
extern u8 D_80290F0C;
void func_801C35AC(s32 arg0, s32 arg1)
{
  func_801C35D8(arg0, &D_80290F0C, 0xB, arg1);
}

typedef struct { u32 w0,w1; } CloudCmd;

typedef struct {
    s16 x, y, z, angle, width;
    u8 padA;
    s8 alpha;
} T030Cloud;
extern void func_801C3758(CloudCmd **, T030Cloud *, s32);
extern u8 D_800F4070[];
extern s32 D_80290D88;
extern u32 D_80290F90[];
extern u8 *D_802D38E0;

void func_801C35D8(CloudCmd **arg0, T030Cloud *arg1, s32 arg2, s32 arg3)
{
    CloudCmd *dl;
    s32 i, offset;
    s32 visible;
    T030Cloud *cloud;
    s16 start;
    s32 end;
    dl = (*arg0)++;
    dl->w0 = 0x06000000; dl->w1 = (u32)D_80290F90;
    D_802D38E0 = D_800F4070;
    i = 0;
    if (arg2 > 0)
    {
        offset = 0; cloud = arg1; do
        {
            start = cloud->angle;
            end = cloud->width + start;
            if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1;
            else visible = 0;
            if (visible || cloud->alpha > 0)
            {
                if (visible)
                {
                    cloud->alpha += 1;
                    if (cloud->alpha >= 17) cloud->alpha = 16;
                }
                else
                {
                    cloud->alpha -= 2;
                    if (cloud->alpha <= 0) cloud->alpha = 0;
                }
                func_801C3758(arg0, (T030Cloud *)((u32)offset + (u8 *)arg1), cloud->alpha);
            }
            else cloud->alpha = 0;
            i++;
            offset += 12;
            if (D_80290D88 >= 60) D_80290D88 = 0;
            cloud++;
        }
        while (i != arg2);
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_13FF0/func_801C3758.s")
