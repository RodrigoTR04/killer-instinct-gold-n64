#include "common.h"

/* Ordered title/menu strings; explicit non-migration hints keep them C-owned. */
const u8 D_802927F0[] = "# 1994, 1995, 1996 NINTENDO / RARE";
const u8 D_80292814[] = "ARCADE";
const u8 D_8029281C[] = "TEAM";
const u8 D_80292824[] = "TEAM ELIMINATION";
const u8 D_80292838[] = "TOURNAMENT";
const u8 D_80292844[] = "PRACTICE";
const u8 D_80292850[] = "TRAINING";
const u8 D_8029285C[] = "FOCUSED TRAINING";
const u8 D_80292870[] = "OPTIONS";


f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    return ((arg1 - arg0) * ((f32) arg2 / (f32) arg3)) + arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801AFAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801AFFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B01EC.s")

typedef struct { u32 w0, w1; } T025Gfx0520;
typedef struct { s32 pad; void *list; } T025ListState;
extern void guTranslate(void *, f32, f32, f32);
extern void func_801C3AA0(f32, f32, f32, f32, f32);
extern u8 D_801D2F40[];
extern s32 D_801D2EBC;
extern s32 D_802956F8, D_802956FC, D_80295700;

s32 func_801B0520(T025Gfx0520 **arg0, T025ListState *arg1, void *arg2, s32 arg3) {
    s32 *frame = &D_801D2EBC;
    T025Gfx0520 *g;

    do { *frame = arg3 * 2; } while (0);
    if (*frame < 230) {
        guTranslate(arg2, 0.0f, (f32) *frame, 0.0f);
        arg1->list = D_801D2F40;
        if (D_802956F8 >= 16) {
            g = (*arg0)++;
            g->w0 = 0xFB000000;
            g->w1 = ((D_802956F8 & 255) << 24) | ((D_802956FC & 255) << 16) | ((D_80295700 & 255) << 8) | 255;
        } else {
            g = (*arg0)++;
            g->w0 = 0xFB000000; g->w1 = 255;
        }
        if (*frame < 220) {
            func_801C3AA0(0.0f, (f32) (*frame - 105), 0.0f, 80.0f, -90.0f);
        }
        return 1;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0668.s")

/* Constants remain in the neighboring assembly-owned pool. */
typedef struct { u32 w0, w1; } T025Gfx0A40;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern s8 D_801CD454;
extern u8 D_801D2DF8[];
extern f64 D_802928E8;
extern f64 D_802928F0;
extern f64 D_802928F8;
extern f32 D_80292900;
extern u8 D_802C8780[];
extern u8 D_802C8790[];
extern s32 D_802CA064;

s32 func_801B0A40(T025Gfx0A40 **arg0, s32 arg1, u8 *arg2, u32 arg3)
    { u8 sp70[0x40];
    T025Gfx0A40 *temp_v1;
    T025Gfx0A40 *temp_v1_2;
    T025Gfx0A40 *temp_v1_3;
    struct { f32 x, y, z; } eye;
    f32 temp_f12;
    f32 temp_f0;

    temp_f0 = func_801AFA80(300.0f, 0.0f, arg3, 40);
    if (temp_f0 > 0.0f) {
        if (temp_f0 <= 60.0f) {
            temp_f0 = 120.0 - cosf(temp_f0 * D_802928E8 * 0.75) * 60.0f / D_802928F0;
        } else {
            D_801CD454 = 0;
            D_802CA064 = 0x280;
        }
        temp_f0 -= 35.0f;
    } else {
        temp_f0 = 0.0f;
    }
    temp_f12 = (f32) (((f64)arg3 * D_802928F8) / 2);
    eye.x = sinf(temp_f12);
    eye.y = cosf(temp_f12); eye.z = 220.0f;
    guLookAtReflect(&sp70, &D_802C8780, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guScale(arg2, D_80292900, D_80292900, 1.0f); guTranslate(arg2 + 0x40, (f32) ((f64) (temp_f0 + 75.0f) - 8.0), 28.0f, 170.0f); temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x03840010; temp_v1->w1 = (u32)&D_802C8780;
    temp_v1_2 = (*arg0)++;
    temp_v1_2->w0 = 0x03820010; temp_v1_2->w1 = (u32)&D_802C8790; temp_v1_3 = (*arg0)++; temp_v1_3->w0 = 0x06000000; temp_v1_3->w1 = (u32)&D_801D2DF8; return 2;
}


#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0CDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B1210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B132C.s")

extern void func_801C47E0(s32, s32, void *, u8);
extern void func_801C48E4(s32, u8, s32);
extern u8 D_800F4070;
extern s8 D_801CD454;
extern s32 D_802956F8, D_802956FC, D_80295700;
extern u8 D_802C8724;
s32 func_801B17BC(u8 arg0, u8 arg1, u8 arg2)
{
    u8 colors[3];
    s32 i;
    u8 *p;
    u8 color;
    void *image = &D_800F4070;
    colors[0] = arg0;
    colors[1] = arg1;
    colors[2] = arg2;
    D_802C8724 = 0;
    /* These setup statements share a line for IDO scheduling. */
    p = colors; i = 0; do {
        color = *p;
        if (color == 8) {
            D_802C8724 |= 1 << i;
        }
        func_801C47E0((color + 0x80) & 0xFF, 0, image, color);
        func_801C48E4(i, *p, 1);
        i++;
        p++;
    } while (i != 3);
    D_801CD454 = 0;
    D_802956F8 = D_802956FC = D_80295700 = 0;
    return 0;
}


typedef struct { u8 pad[0x10]; s32 state; } T025State;
extern void func_801C0610(s32);
extern void func_801C49A8(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_8029571A;
extern u8 D_802C8724;
s32 func_801B18BC(s32 arg0, T025State *arg1, s32 arg2, u32 arg3) {
    s32 i, n;
    if (arg3 >= 0xF1U) {
        D_8029571A++;
        arg1->state = -1;
    }
    func_801C0610(arg0);
    for (i = 0; i != 3; i++) {
        if (D_802C8724 & (1 << i)) n = 12;
        else n = 15;
        func_801C49A8(arg0, i, 0x82000 + i * 0xC8000, 0x172000, (n << 12) / 10, 0, 0);
    }
    return 0;
}
