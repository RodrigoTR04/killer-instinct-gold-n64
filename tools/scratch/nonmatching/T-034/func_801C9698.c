#include "frontend.h"
/* T-050: retained improvement; 135 differing words including size penalty, 1148 compiled bytes. Full function remains nonmatching. */
/* DRAFT. Remaining diff (~65 lines, same instruction count): frame is 0xC8 here vs 0xB0; float constant hoisting differs (target keeps -400.0f in f28, 0.0f in f30 and the D_802954E0 x in f26, re-materialises 70.0f), and s1..s5 colour/name/index registers are rotated. D_802954E0/E4 are rodata floats referenced as externs to avoid emitting new rodata. */



extern u8 D_80127D00[][4];
extern u8 D_8029532C[];
extern u8 D_80295340[];
extern u8 D_80295358[];
extern u8 D_80295370[];
extern u8 D_80295380[];
extern f32 D_802954E0;
extern f32 D_802954E4;
extern s32 D_802956F4;



void func_801C9698(s32 arg0, FrontendRenderContext *arg1) {
    f32 x;
    s32 alpha;
    s32 b;
    u8 *name;
    s32 g;
    u8 i;
    f32 y;
    u8 label[3];
    s32 r;
    f32 scale;

    y = 225.0f;
    x = D_802954E0;
    scale = D_802954E4;
    label[0] = '1';
    label[1] = ':';
    label[2] = 0;
    for (i = 0; i < 8; i++) {
        alpha = 1;
        if (i == D_802D39FC) {
            r = 0xFF;
            g = 0xE6;
            b = 0x82;
            name = D_80127D00[i];
            alpha = -1 - D_802D3A01;
        } else {
            name = D_80127D00[i];
            r = g = b = 0x87;
            if (*(s32 *)name == 0) {
                r = g = b = 0x3C;
            }
        }
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), label, x, y, -1200.0f, r, g, b, 0xFF, scale);
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), name, -400.0f, y, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, alpha);
        D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), func_801C9584(i, 2), 0.0f, y, -1200.0f, r, g, b, 0xFF, scale);
        label[0]++;
        y -= 70.0f;
    }
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_8029532C, -450.0f, -320.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295340, -450.0f, -380.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295358, -450.0f, -440.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295370, 150.0f, -360.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
    D_802956F4 += func_801BDA6C((FrontendGfxWords **)arg0, arg1->matrices + (D_802956F4 << 6), D_80295380, 150.0f, -420.0f, -1200.0f, 0xFF, 0xFF, 0xFF, 0xFF, 0.5f);
}
