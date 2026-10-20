#include "common.h"

f32 func_801B19F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    return ((arg1 - arg0) * ((f32) arg2 / (f32) arg3)) + arg0;
}

extern f32 sqrtf(f32);
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp_f0;

    temp_f0 = sqrtf((arg1 * arg1) + (arg0 * arg0));
    arg1 = ((arg2 - temp_f0) * arg1) / temp_f0;
    if (arg1 < 0.0f) {
        return 0.0f;
    }
    return arg1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B1A7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B1DE4.s")

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { s32 w0, w1; } T025Gfx2010;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D309C;
extern u8 D_802C03E0[];
extern u8 D_802C0BE0[];

s32 func_801B2010(T025Gfx2010 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D309C;
    T025Gfx2010 *env;
    if ((s32) D_801D308C >= 2)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(-6.0f, -150.0f, *counter = arg1, 1); } else { *counter = arg1; position = -150.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C03E0, &D_802C0BE0, position, 0x7F);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 2))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx21B4;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30A0;
extern u8 D_802C13E0[];
extern u8 D_802C2020[];

s32 func_801B21B4(T025Gfx21B4 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30A0;
    T025Gfx21B4 *env;
    if ((s32) D_801D308C >= 3)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(44.0f, -100.0f, *counter = arg1, 1); } else { *counter = arg1; position = -100.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C13E0, &D_802C2020, position, 0xC3);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 3))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx2358;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30A4;
extern u8 D_802C2C60[];
extern u8 D_802C3530[];

s32 func_801B2358(T025Gfx2358 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30A4;
    T025Gfx2358 *env;
    if ((s32) D_801D308C >= 4)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(89.0f, -55.0f, *counter = arg1, 1); } else { *counter = arg1; position = -55.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C2C60, &D_802C3530, position, 0x8C);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 4))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx24FC;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30A8;
extern u8 D_802C3E00[];
extern u8 D_802C4A40[];

s32 func_801B24FC(T025Gfx24FC **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30A8;
    T025Gfx24FC *env;
    if ((s32) D_801D308C >= 5)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(133.0f, -11.0f, *counter = arg1, 1); } else { *counter = arg1; position = -11.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C3E00, &D_802C4A40, position, 0xC3);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 5))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx26A0;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30AC;
extern u8 D_802C5680[];
extern u8 D_802C5D50[];

s32 func_801B26A0(T025Gfx26A0 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30AC;
    T025Gfx26A0 *env;
    if ((s32) D_801D308C >= 6)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(189.0f, 45.0f, *counter = arg1, 1); } else { *counter = arg1; position = 45.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C5680, &D_802C5D50, position, 0x6C);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 6))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx2844;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30B0;
extern u8 D_802C6420[];
extern u8 D_802C6AE0[];

s32 func_801B2844(T025Gfx2844 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30B0;
    T025Gfx2844 *env;
    if ((s32) D_801D308C >= 7)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(247.0f, 103.0f, *counter = arg1, 1); } else { *counter = arg1; position = 103.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C6420, &D_802C6AE0, position, 0x6B);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 7))
    {
        D_801D3088 += 1;
    }
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);
typedef struct { u32 w0, w1; } T025Gfx29E8;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D30B4;
extern f32 D_80292960;
extern u8 D_802C71A0[];
extern u8 D_802C7A70[];

s32 func_801B29E8(T025Gfx29E8 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    f32 position;
    s32 alpha;
    s32 *counter = &D_801D30B4;
    T025Gfx29E8 *env;
    if ((s32) D_801D308C >= 8)
    {
        return 0;
    }
    /* Keep the counter block joined for IDO instruction scheduling. */
    arg1 = *counter; if (arg1++ < 1) { position = func_801B19F0(D_80292960, 153.0f, *counter = arg1, 1); } else { *counter = arg1; position = 153.0f; }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802C71A0, &D_802C7A70, position, 0x8C);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFB000000; env->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0xFA000000; env->w1 = 0x64000000;
    env = *arg0;
    *arg0 = env + 1;
    env->w0 = 0x06000000; env->w1 = (s32) &D_801D3058;
    if ((position < 1.0f) && ((s32) D_801D3088 < 8))
    {
        D_801D3088 += 1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B2B8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B2EF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B310C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B3324.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B353C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B3754.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B396C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B3B84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B3DB0.s")

extern s8 D_8012834B;
extern void func_801B43A8(void);
void func_801B4300(void) {
    D_8012834B = 0;
    func_801B43A8();
}

extern u8 D_802C8CB8[];
extern u8 D_80127D58[];
extern u8 D_8004A407;
s32 func_801B4324(u8 arg0) {
    u8 value;
    value = D_80127D58[D_802C8CB8[arg0] + arg0 * 16];
    if (D_8004A407 & (arg0 + 1)) value = 0;
    if (value >= 120) return 3;
    if (value >= 55) return 2;
    if (value >= 5) return 1;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B43A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B446C.s")

extern void func_801AC95C(u8 *, s32);
extern u8 D_80127CE8[][11];
extern u8 D_80127CFE[];
extern u8 D_802C8D06;
extern u8 D_802C8CE0;
extern u8 D_802C8CEA[];
extern u8 D_802C8D0F;
void func_801B4590(u8 arg0) {
    u8 *entry;

    if (D_802C8D06 & 8) {
        entry = &D_80127CFE[arg0];
        func_801AC95C(D_80127CE8[arg0], *entry);
        D_802C8CE0 |= 1 << arg0;
        if (D_8004A407 & (1 << (1 - arg0))) D_802C8D0F = 1;
        D_802C8CEA[arg0] = *entry + 16;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B465C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B47A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B5534.s")

s32 func_801B55DC(u8 arg0) {
    s32 temp_t6;

    temp_t6 = arg0;
    if (temp_t6 < 0xA) {
        return (temp_t6 + 0x30) << 0x18;
    }
    return (((temp_t6 / 10) + 0x30) << 0x18) + (((temp_t6 % 10) + 0x30) << 0x10);
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B5650.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B5DCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B6528.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B677C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B695C.s")

typedef struct T029Gfx801B6A68 { u32 w0, w1; } T029Gfx801B6A68;
extern u8 D_802C8D08[];
extern u8 D_802C8808[][512];
extern u8 D_801F34B0[];
typedef struct T029Texture { u8 pad[8]; void *data; } T029Texture;
s32 func_801B6A68(T029Gfx801B6A68 **arg0, T029Texture *arg1, s32 arg2) {
    T029Gfx801B6A68 *command0;
    T029Gfx801B6A68 *command1;
    T029Gfx801B6A68 *command2;
    T029Gfx801B6A68 *command3;
    T029Gfx801B6A68 *command4;
    T029Gfx801B6A68 *command5;
    T029Gfx801B6A68 *command6;
    T029Gfx801B6A68 *command7;
    T029Gfx801B6A68 *command8;
    T029Gfx801B6A68 *command9;
    T029Gfx801B6A68 *command10;

    if (arg1->data != 0) {
        command0 = (*arg0)++;
        command0->w0 = 0xE7000000; command0->w1 = 0;
        command1 = (*arg0)++;
        command1->w0 = 0xFD100000;
        command1->w1 = (u32)(&D_802C8808[arg2][D_802C8D08[arg2] * 2]);
        command2 = (*arg0)++;
        command2->w0 = 0xE8000000; command2->w1 = 0;
        command3 = (*arg0)++;
        command3->w0 = 0xF5000100; command3->w1 = 0x07000000;
        command4 = (*arg0)++;
        command4->w0 = 0xE6000000; command4->w1 = 0;
        command5 = (*arg0)++;
        command5->w0 = 0xF0000000; command5->w1 = 0x073FC000;
        command6 = (*arg0)++;
        command6->w0 = 0xE7000000; command6->w1 = 0;
        command7 = (*arg0)++;
        command7->w0 = 0xBA000E02; command7->w1 = 0x8000;
        command8 = (*arg0)++;
        command8->w0 = 0x06000000; command8->w1 = (u32)D_801F34B0;
        return 2;
    }
    command9 = (*arg0)++;
    command9->w0 = 0xBA000E02; command9->w1 = 0;
    command10 = (*arg0)++;
    command10->w0 = 0x06000000; command10->w1 = (u32)D_801F34B0;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B6BD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B6E4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B849C.s")

typedef struct T039Gfx801B994C { u32 w0, w1; } T039Gfx801B994C;
extern void guTranslate(void *, f32, f32, f32);
extern void func_8002F6F4(s32, s32, void *);
extern s16 D_801F35AC;
extern u8 D_802C8800[];
extern s32 D_80066C40;
extern u8 D_8004A264[];
s32 func_801B994C(T039Gfx801B994C **arg0, s32 arg1, void *arg2, s32 arg3) {
    T039Gfx801B994C *command;
    guTranslate(arg2, 0.0f, 50.0f, 0.0f);
    command = (*arg0)++;
    command->w0 = 0xFA000000;
    command->w1 = (u32)(D_801F35AC & 0xFF) | ~0xFFU;
    if (D_802C8800[1] == 0 && D_801F35AC >= 51) {
        func_8002F6F4(D_80066C40, 70, D_8004A264);
        D_802C8800[1] = 1;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801B9A04.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BA088.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BA280.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BA470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BA674.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BA884.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BAA78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BADEC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB024.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB258.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB464.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB594.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB7B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BBB60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BBC84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BBE88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BC1B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BCB70.s")
