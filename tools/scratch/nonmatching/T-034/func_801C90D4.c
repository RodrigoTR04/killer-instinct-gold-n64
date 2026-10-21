/* T-122 nonmatching: 217 differing words; 1192 compiled bytes. See T-122/REPORT.md. */
#include "frontend.h"
/* DRAFT. Same instruction count (300); remaining diff is scheduling/register allocation around the first call's stack args and the fade-loop setup. D_80292698 is a u8 ***[] table (string = *tbl[mode][i]). Doubles D_802954D0/D8 and float D_802954C8 are rodata, referenced as externs. */



extern u8 ***D_80292698[];
extern FrontendGfxWords D_80292748[];
extern u8 D_80295314[];
extern u8 D_80295318[];
extern f32 D_802954C8;
extern f64 D_802954D0;
extern f64 D_802954D8;
extern s32 D_802956F4;

extern u8 D_802D3A00;
extern u8 D_802D3A08;
extern f32 D_802D3A10[2];

void func_801C90D4(FrontendGfxWords **gfxp, FrontendRenderContext *arg1)
    {
    s32 i;
    FrontendGfxWords *g;
    f32 a;
    f32 target;
    u8 c;
    g = (*gfxp)++; g->w0 = 0x06000000; g->w1 = (u32)D_80292748;
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), *D_80292698[D_802D3A00][D_802D39FC], 0.0f, 80.0f, D_802954C8, 0xC0, 0xC0, 0xC0, 0xFF, 1.0f);
    for (i = 0;
    i < 2;
    i++) { target = (i == D_802D3A08) * 0.5 + 0.5;
    if (D_802D3A10[i] < target - D_802954D8) {
            D_802D3A10[i] += D_802954D0;
    } else if (D_802D3A10[i] > target + D_802954D8) {
            D_802D3A10[i] -= D_802954D0;
    }
    }
    a = D_802D3A10[1] * 255.0f;
    c = 255.0f - a;
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), D_80295314, -60.0f, -30.0f, -600.0f, (u32)a, c, c, 0xFF, D_802D3A10[1]);
    a = D_802D3A10[0] * 255.0f;
    c = 255.0f - a;
    D_802956F4 += func_801BE540(gfxp, arg1->matrices + (D_802956F4 << 6), D_80295318, 60.0f, -25.0f, -600.0f, (u32)a, c, c, 0xFF, D_802D3A10[0]);
    }
