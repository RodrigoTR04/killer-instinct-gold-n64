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

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx2EF4;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30C0;
extern s16 D_802C87D0;

s32 func_801B2EF4(T025Gfx2EF4 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30C0;
    T025Gfx2EF4 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 2)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 2) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, -125.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx310C;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30C4;
extern s16 D_802C87D0;

s32 func_801B310C(T025Gfx310C **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30C4;
    T025Gfx310C *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 3)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 3) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, -75.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx3324;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30C8;
extern s16 D_802C87D0;

s32 func_801B3324(T025Gfx3324 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30C8;
    T025Gfx3324 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 4)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 4) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, -30.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx353C;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30CC;
extern s16 D_802C87D0;

s32 func_801B353C(T025Gfx353C **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30CC;
    T025Gfx353C *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 5)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 5) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, 14.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx3754;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30D0;
extern s16 D_802C87D0;

s32 func_801B3754(T025Gfx3754 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30D0;
    T025Gfx3754 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 6)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 6) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, 70.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

/* Original completed-animation path reads alpha before assigning it. */
extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx396C;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30D4;
extern s16 D_802C87D0;

s32 func_801B396C(T025Gfx396C **arg0, s32 arg1, void *arg2, s32 arg3)
{
    u8 alpha;
    s32 *counter = &D_801D30D4;
    T025Gfx396C *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 7)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        /* Pack before allocating the command; keep alpha assignment separate. */
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores joined for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        *counter = arg1;
        /* Exit the completed-animation block before advancing a finished stage. */
        do {
            p1 = (*arg0)++;
            p1->w0 = primitive;
            color2 = D_802C87D0 & 0xFF;
            p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));
            alpha = 0xFF;
            if ((s32) D_801D308C >= 7) {
                break;
            }
            D_801D308C += 1;
        } while (0);
    }
    guTranslate(arg2, 128.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

extern f32 func_801B19F0(f32, f32, s32, s32);

typedef struct {
    u32 w0, w1;
} T025Gfx3B84;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3030[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s16 D_801D3094;
extern s32 D_801D30D8;
extern s16 D_802C87D0;
extern u8 D_8029571A;

s32 func_801B3B84(T025Gfx3B84 **arg0, s32 arg1, void *arg2, s32 arg3)
{
    /* Original completed-animation path reads alpha before assigning it. */
    u8 alpha;
    s32 *counter = &D_801D30D8;
    T025Gfx3B84 *p0, *p1, *p2, *p3;
    u8 color;
    s32 color2;
    s32 packed;
    u32 value;
    u32 primitive;
    if ((s32) D_801D3088 < 8)
    {
        return 0;
    }
    primitive = 0xFA000000;
    arg1 = *counter;
    if (arg1++ < 10)
    {
        value = (u32) func_801B19F0(0.0f, 255.0f, *counter = arg1, 10);
        color = (u16)value;
        packed = ((color & 0xFF) << 0x18) | ((color & 0xFF) << 0x10) | ((color & 0xFF) << 8) | (color & 0xFF);
        alpha = value;
        p0 = (*arg0)++;
        /* Keep both stores on one line for IDO delay-slot scheduling. */
        p0->w0 = primitive; p0->w1 = (s32) packed;
    }
    else
    {
        p1 = (*arg0)++;
        p1->w0 = primitive;
        color2 = D_802C87D0 & 0xFF;
        p1->w1 = (s32) ((color2 << 0x18) | (color2 << 0x10) | (color2 << 8) | (alpha & 0xFF));

        alpha = 0xFF;
        if ((s32) D_801D308C < 8)
        {
            D_801D308C += 1;
        }
        *counter = arg1;
        if (arg1 < 0x32) { D_8029571A = 1; }
    }
    guTranslate(arg2, 178.0f, 0.0f, (f32) D_801D3094);
    p2 = (*arg0)++;
    p2->w0 = 0xFB000000;
    p2->w1 = (s32) ((alpha + D_801D3094) & 0xFF);
    p3 = (*arg0)++;
    p3->w0 = 0x06000000; p3->w1 = (s32) &D_801D3030;
    return 1;
}

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

extern void *memcpy(void *, const void *, u32);
extern s32 guRandom(void);
extern u8 D_80128340[];
extern u8 D_80128349;
extern u8 D_801F3530;

void func_801B43A8(void) {
    s32 i;
    u32 random;
    u8 *other;
    u8 *group;
    u8 *entry;
    u8 value;
    u8 *end;
    u8 *end2;

    end2 = &D_80128349;
    memcpy(D_80128340, &D_801F3530, 11);
    for (group = (u8 *)((long)(u32)end2 - 9), end = end2; group != end; group += 3) {
        random = guRandom();
        i = 0;
        entry = group;
        do {
            other = (u8 *)((u32)group + (u8)(random % 3U));
            value = *entry;
            i++;
            *entry = *other;
            entry++;
            *other = value;
            random >>= 4;
        } while (i != 3);
    }
}

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

typedef struct T029Gfx801B6528 { u32 w0, w1; } T029Gfx801B6528;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_802C8CE0, D_802C8D06, D_802C8CE8;
extern s16 D_802C8CE2;
extern s32 D_802C8CDC, D_802C8CD4;
extern u8 D_80128340[];
extern u8 D_801F2E80[];
extern u8 D_801F2EB4[];
extern u8 D_80290BE0[];
typedef struct T029Card { u8 pad[12]; s32 index; } T029Card;
s32 func_801B6528(T029Gfx801B6528 **arg0, void *arg1, void *arg2, s32 arg3) {

    f32 y;
    s32 index;
    if (D_8004A407 == 0 || D_802C8CE0 == 0 || D_802C8D06 == 6) {
        return 0;
    }
    if (D_802C8CE0 != 3) {
        index = ((T029Card *)arg1)->index;
        y = (index - (u8)D_8012834B) * 70 - D_802C8CE2;
        if (D_802C8CE2 > 0 && index == 0) {
            D_802C8CE2 = D_802C8CE2 - D_802C8CE8 * 9 - 8;
        }
        D_802C8CDC = D_802C8CD4 + 1;
    } else {
        D_802C8CE2 += 3;
        index = ((T029Card *)arg1)->index;
        if ((u8)D_8012834B >= index) {
            y = (index - (u8)D_8012834B) * 70 - D_802C8CE2;
        } else {
            y = (index - (u8)D_8012834B) * 70 + D_802C8CE2;
        }
    }
    guTranslate(arg2, 0.0f, y, 0.0f);
    { T029Gfx801B6528 *q = (*arg0)++; q->w0 = 0x06000000; q->w1 = (u32)D_801F2E80; }
    if (((T029Card *)arg1)->index < (u8)D_8012834B) {
        T029Gfx801B6528 *q = (*arg0)++;
        q->w0 = 0xFA000000; q->w1 = 0x373737FF;
    }
    {
        T029Gfx801B6528 *q = (*arg0)++;
        q->w0 = 0xFD100000;
        q->w1 = *(u32 *)(D_801F2EB4 + D_80128340[((T029Card *)arg1)->index] * 140);
    }
    { T029Gfx801B6528 *q = (*arg0)++; q->w0 = 0x03800010; q->w1 = (u32)D_80290BE0; }
    return 1;
}

void func_801B677C(u8 arg0, f32 *arg1, f32 *arg2, f32 *arg3, u16 arg4)
{
  s32 remainder;
  s32 row;
  remainder = ((s32) arg4) % 3;
  arg0--;
  if (remainder >= (arg4 - arg0))
  {
    *arg1 = (f32) ((220 / (remainder + 1)) * (arg4 - arg0));
  }
  else
  {
    *arg1 = (f32) ((((-((arg0 % 3) * 2)) * 9) * 4) + 180);
  }
  row = arg0 / 3;
  *arg2 = (f32) (100 - ((220 / ((arg4 + 2) / 3)) * row));
  *arg3 = -100.0f;
  if (arg4 >= 10)
  {
    *arg2 = (f32) (100 - (row * 73));
  }
}

extern u8 D_802C8CC8[];
extern u8 D_802C8D08[];
extern u8 D_802C8808[][512];
typedef struct T029Asset { u8 pad[8]; u8 *frames; } T029Asset;

void func_801B695C(T029Asset *arg0, s32 arg1) {
    u8 *frame;

    if (arg0 != 0 && arg0->frames != 0) {
        frame = (D_802C8CC8[arg1] * 3 << 5) + arg0->frames;
        D_802C8D08[arg1] ^= 0x40;
        if (D_802C8CC8[arg1] < 8) {
            memcpy(D_802C8808[arg1] + D_802C8D08[arg1] * 2, arg0->frames, 0x60);
        } else {
            memcpy(D_802C8808[arg1] + D_802C8D08[arg1] * 2, frame, 0x60);
        }
        memcpy(D_802C8808[arg1] + D_802C8D08[arg1] * 2 + 0x100, frame, 0x60);
    }
}

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

#include "frontend.h"
extern u8 D_802C8D0A[];
extern u8 D_802C8D0B;
extern s16 D_801F35AC;
extern u8 D_80292A44[], D_80292A4C[];
extern void *D_801F3570[], *D_801F3540[];
s32 func_801B6BD8(FrontendGfxWords **arg0, u8 *arg1) {
    s32 offset, count;
    count = 0;
    offset = 0;
    if (D_802C8D0A[0] == 3 && D_802C8D0A[1] == 3) offset = 9;
    if (D_802C8D0A[0] != 0) {
        count += func_801BE540(arg0, arg1, D_80292A44, 0.0f, 170.0f, -1600.0f, 0, (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), 255, 1.0f);
        count += func_801BE540(arg0, arg1 + (count << 6), D_801F3570[D_802C8D0A[0] + offset], 0.0f, 130.0f, -1600.0f, (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), 255, 1.0f);
    }
    if (D_802C8D0A[1] != 0) {
        count += func_801BE540(arg0, arg1 + (count << 6), D_80292A4C, 0.0f, 80.0f, -1600.0f, 0, (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), 255, 1.0f);
        count += func_801BE540(arg0, arg1 + (count << 6), D_801F3540[D_802C8D0B + offset], 0.0f, 40.0f, -1600.0f, (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), (u8)(255 - D_801F35AC), 255, 1.0f);
    }
    return count;
}

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

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA088;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3678;
extern u8 D_801F367C[];
extern u8 D_801F3680[];

void func_801BA088(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA088 *arg4, s32 arg5) {
    s32 *counter;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F3678;
    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0x13C) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0x8A) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0xE0) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x128) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F367C + (*counter * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3680 + (*counter * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0x35) {
        *counter = 2;
    }
}

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA280;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern u8 D_801F3824[];
extern u8 D_801F388C[];

void func_801BA280(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA280 *arg4, s32 arg5) {
    s32 y0;
    s32 x0;
    s32 x1;
    s32 y1;

    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0x120) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0xF9) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0xB5) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x11C) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3824 + (((s32) (arg3 >> 3) % 25) * 4)), 2, 0x28, 0x1E, 0x28, 0x1E, 0, 0, 0x27, 0x1D, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F388C + (((s32) (arg3 >> 2) % 13) * 4)), 2, 0x1C, 0x26, 0x1C, 0x26, 0, 0, 0x1B, 0x25, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
}

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA470;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F38C4;
extern u8 D_801F38C8[];
extern u8 D_801F38CC[];

void func_801BA470(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA470 *arg4, s32 arg5) {
    s32 *counter;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F38C4;
    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0x1A0) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0xED) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0x10A) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0xE5) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F38C8 + (*counter * 8)), 2, 0x2C, 0x2A, 0x2C, 0x2A, 0, 0, 0x2B, 0x29, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F38CC + (*counter * 8)), 2, 0x24, 0x33, 0x24, 0x33, 0, 0, 0x23, 0x32, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0x20) {
        *counter = 0;
    }
}

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA674;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F39C8;
extern u8 D_801F39CC[];
extern u8 D_801F39D0[];

void func_801BA674(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA674 *arg4, s32 arg5) {
    s32 *counter;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F39C8;
    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0x184) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0x8C) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0xE4) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x83) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F39CC + ((*counter / 3) * 8)), 2, 0x18, 0x54, 0x18, 0x54, 0, 0, 0x17, 0x53, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F39D0 + ((*counter / 3) * 8)), 2, 0x2C, 0x2C, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0xC) {
        *counter = 0;
    }
}

typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BA884;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F39EC;
extern u8 D_801F39F0[];
extern u8 D_801F39F4[];

void func_801BA884(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BA884 *arg4, s32 arg5)
{
    s32 firstY;
    s32 *counter;
    s32 x1;
    s32 secondY;
    s32 frame;
    s32 x0;
    counter = &D_801F39EC;
    x0 = (arg1 * 4) + (((s32) (((arg5 * 0x15) + 0x1CC) * arg4->scale)) >> 0xA);
    firstY = ((arg2 * 4) + (((s32) (arg4->scale * 0x70)) >> 0xA)) + (arg4->yOffset * 4);
    secondY = ((arg2 * 4) + (((s32) (arg4->scale * 0x70)) >> 0xA)) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + (((s32) (arg4->scale * 0x12C)) >> 0xA);
    if (arg5 != 0)
    {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *((s32 *) (D_801F39F0 + (*counter * 8))), 2, 0x20, 0x40, 0x20, 0x40, 0, 0, 0x1F, 0x3F, (f32) x0, (f32) firstY, ((s32) (arg4->scale * 4)) / 3, arg5);
    func_801BC1B0(arg0, *((s32 *) (D_801F39F4 + (*counter * 8))), 2, 0x34, 0x1C, 0x34, 0x1C, 0, 0, 0x33, 0x1B, (f32) x1, (f32) secondY, (s32) arg4->scale, arg5);
    frame = *counter + 1;
    *counter = frame;
    if (frame >= 0xC) *counter = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BAA78.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BADEC.s")

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB024;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3ACC;
extern u8 D_801F3AD0[];
extern u8 D_801F3AD4[];

void func_801BB024(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB024 *arg4, s32 arg5) {
    s32 *counter;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F3ACC;
    x0 = (arg1 * 4) + ((s32) (((arg5 * 0x16) + 0x124) * arg4->scale) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0xCB) >> 0xA) + (arg4->yOffset * 4);
    x1 = (arg1 * 4) + ((s32) (((arg5 * 0x16) + 0x72) * arg4->scale) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0xD6) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3AD0 + (*counter * 8)), 2, 0x34, 0x25, 0x34, 0x25, 0, 0, 0x33, 0x24, (f32) x0, (f32) y0, (s32) (arg4->scale * 4) / 3, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3AD4 + (*counter * 8)), 2, 0x20, 0x40, 0x20, 0x40, 0, 0, 0x1F, 0x3F, (f32) x1, (f32) y1, (s32) (arg4->scale * 4) / 3, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0x28) {
        *counter = 0;
    }
}

typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB258;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3C10;
extern u8 D_801F3C14[];
extern u8 D_801F3C18[];

void func_801BB258(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB258 *arg4, s32 arg5) {
    s32 x1;
    s32 y1;
    s32 *counter;
    s32 y0;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F3C10;
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0xC4) >> 0xA);
    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0xC4) >> 0xA);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x153) >> 0xA) + (arg4->yOffset * 4);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0xD7) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x1 = 0x9B0 - x1;
        x0 = 0x9B0 - x0;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3C14 + ((*counter / 3) * 8)), 2, 0x2C, 0x20, 0x2C, 0x20, 0, 0, 0x2B, 0x1F, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3C18 + ((*counter / 3) * 8)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0xC) {
        *counter = 0;
    }
}

typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB464;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3C34;
extern u8 D_801F3C38[];

void func_801BB464(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB464 *arg4, s32 arg5) {
    s32 var_v0;
    s32 *counter;
    s32 temp_v0;
    s32 y;

    counter = &D_801F3C34;
    var_v0 = (arg1 * 4) + ((s32) (arg4->scale * 0x214) >> 0xA);
    y = (arg2 * 4) + ((s32) (arg4->scale * 0x226) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        var_v0 = 0x9B0 - var_v0;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3C38 + (((s32) D_801F3C34 / 3) * 4)), 2, 0x2C, 0x2B, 0x2C, 0x2B, 0, 0, 0x2B, 0x2A, (f32) var_v0, (f32)y, (s32) arg4->scale, arg5);
    temp_v0 = *counter + 1;
    *counter = temp_v0;
    if (temp_v0 >= 0x78) {
        *counter = 0;
    }
}

/* Read scale from the state so IDO preserves completed coordinates across draws. */
typedef struct { u8 pad[0x7E]; u16 scale; s16 yOffset; } T023State801BB594;
extern void func_801BC1B0(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, s32, s32);
extern s32 D_801F3CD8;
extern u8 D_801F3CDC[];
extern u8 D_801F3D2C[];

void func_801BB594(s32 arg0, s32 arg1, s32 arg2, s32 arg3, T023State801BB594 *arg4, s32 arg5) {
    s32 *counter;
    s32 x1;
    s32 y0;
    s32 y1;
    s32 nextFrame;
    s32 x0;

    counter = &D_801F3CD8;
    x0 = (arg1 * 4) + ((s32) (arg4->scale * 0x150) >> 0xA);
    x1 = (arg1 * 4) + ((s32) (arg4->scale * 0x1A3) >> 0xA);
    y0 = (arg2 * 4) + ((s32) (arg4->scale * 0x160) >> 0xA) + (arg4->yOffset * 4);
    y1 = (arg2 * 4) + ((s32) (arg4->scale * 0x108) >> 0xA) + (arg4->yOffset * 4);
    if (arg5 != 0) {
        x0 = 0x9B0 - x0;
        x1 = 0x9B0 - x1;
    }
    func_801BC1B0(arg0, *(s32 *)(D_801F3CDC + (((s32) *counter / 2) * 4)), 2, 0x2C, 0x16, 0x2C, 0x16, 0, 0, 0x2B, 0x15, (f32) x0, (f32) y0, (s32) arg4->scale, arg5);
    func_801BC1B0(arg0, *(s32 *)(D_801F3D2C + (((s32) *counter / 4) * 4)), 2, 0x18, 0x16, 0x18, 0x16, 0, 0, 0x17, 0x15, (f32) x1, (f32) y1, (s32) arg4->scale, arg5);
    nextFrame = *counter + 1;
    *counter = nextFrame;
    if (nextFrame >= 0x28) {
        *counter = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BB7B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BBB60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BBC84.s")

extern s32 D_801F3D6C, D_801F3D70;
extern u8 D_802C9020[];
extern s16 D_802C9D20[];
extern s32 D_802C9F64;
typedef struct { u8 pad[0xE8]; s32 x, y; } T138View;
void func_801BBE88(FrontendGfxWords **arg0, T138View *arg1) {
    s32 temp_a2;
    FrontendGfxWords *g, *p0;
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    g = (*arg0)++; g->w0 = 0xFD100000; g->w1 = (u32)&D_802C9D20;
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE8000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5000100; q->w1 = (u32)0x07000000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE6000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF0000000; q->w1 = (u32)0x073FC000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xBA000E02; q->w1 = (u32)0x8000; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xFD500000; q->w1 = (u32)&D_802C9020; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5500000; q->w1 = (u32)0x07018060; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE6000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF3000000; q->w1 = (u32)0x075FF100; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xE7000000; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF5481000; q->w1 = (u32)0x18060; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xF2000000; q->w1 = (u32)0xFC0BC; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0x2F00BCC0; q->w1 = 0; }
    { FrontendGfxWords *q = (*arg0)++; q->w0 = 0xFCFFFFFF; q->w1 = (u32)0xFFFCF279; } if (D_802C9F64 != 0) {
        p0 = (*arg0)++;
        p0->w0 = (s32) ((((D_801F3D70 * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((arg1->y * 4) & 0xFFF));
        p0->w1 = (u32) ((((D_801F3D6C * 4) & 0xFFF) << 0xC) | ((D_802C9F64 * 4) & 0xFFF));
        p0 = (*arg0)++;
        p0->w0 = 0;
        temp_a2 = arg1->y;
        p0->w1 = (u32) ((((s32) (temp_a2 * 0x41) / (s32) (temp_a2 - D_802C9F64)) & 0xFFFF) | 0xC80000);
        return;
    }
    p0 = (*arg0)++;
    p0->w0 = (s32) ((((arg1->x * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((arg1->y * 4) & 0xFFF));
    p0->w1 = 0;
    p0 = (*arg0)++;
    p0->w0 = 0; p0->w1 = (u32)0xC80041;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BC1B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_5ED0/func_801BCB70.s")
