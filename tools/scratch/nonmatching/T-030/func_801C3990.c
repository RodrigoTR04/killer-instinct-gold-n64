/* DRAFT. Remaining diff: Loop matches; f0 and f2 are exchanged for zero and the external float before guTranslate. */
#include "common.h"

typedef struct {
    s16 x, y, z;
    u16 flag;
    s16 s, t;
    u8 r, g, b, a;
} T030Vertex;
extern const f32 D_802937C0;
extern f32 D_802D38F0, D_802D38F4;
extern s32 D_802D38F8, D_802D38FC;
extern s32 D_802D3900[16];
extern void guTranslate(void *, f32, f32, f32);
extern T030Vertex *D_802D3940;

void func_801C3990(T030Vertex *arg0) {
    s32 i, j;
    f32 zero = 0.0f;
    D_802D38F0 = D_802937C0;
    D_802D38F4 = D_802937C0;
    D_802D38FC = 0;
    D_802D38F8 = 0;
    D_802D3940 = arg0;
    guTranslate(&D_802D3900, zero, zero, zero);
    for (i = 0; i < 0x300; ) {
        D_802D3940[i].s = 0;
        D_802D3940[i].t = 0;
        D_802D3940[i+1].s = 0x400;
        D_802D3940[i+1].t = 0;
        D_802D3940[i+2].s = 0x200;
        D_802D3940[i+2].t = 0x400;
        for (j = 0; j != 3; j++, i++) {
            D_802D3940[i].r = 255;
            D_802D3940[i].g = 255;
            D_802D3940[i].b = 255;
        }
    }
}
