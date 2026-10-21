#include "common.h"

typedef struct {
    s16 x, y, z;
    u16 flag;
    s16 s, t;
    u8 r, g, b, a;
} T030Vertex;

extern f32 D_802D38F0, D_802D38F4;
extern s32 D_802D38F8, D_802D38FC;
extern s32 D_802D3900[16];
extern void guTranslate(void *, f32, f32, f32);
extern T030Vertex *D_802D3940;

void func_801C3990(T030Vertex *arg0) {
    s32 i, j;
    D_802D38F0 = 0.1f;
    D_802D38F4 = 0.1f;
    D_802D38FC = 0;
    D_802D38F8 = 0;
    D_802D3940 = arg0;
    guTranslate(&D_802D3900, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 0x300; ) {
        D_802D3940[i].s = 0;
        D_802D3940[i].t = 0;
        D_802D3940[i + 1].s = 0x400;
        D_802D3940[i + 1].t = 0;
        D_802D3940[i + 2].s = 0x200;
        D_802D3940[i + 2].t = 0x400;
        for (j = 0; j != 3; j++, i++) {
            D_802D3940[i].r = 255;
            D_802D3940[i].g = 255;
            D_802D3940[i].b = 255;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_17E70/func_801C3AA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_17E70/func_801C3E40.s")
