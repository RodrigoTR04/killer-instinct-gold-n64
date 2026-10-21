#include "frontend.h"
/* T-105: nonmatching draft; see T-105/REPORT.md for measurement and remaining differences. */

extern u8 D_8004A407;
extern s8 D_80292CC4;
extern f32 D_80292CF0;
extern s32 D_802956F4, D_802CA068, D_802D3818[];
void func_801C11F0(s32 list, s32 unused, s32 side, s32 player) {
    s8 digit[2];
    s32 phase, shade;
    f32 x;
    if (D_8004A407) player = 0;
    phase = D_802D3818[player];
    shade = (phase % 100) * 255 / 100;
    if (shade >= 65 && shade < 192) shade = 63;
    if (shade >= 193) shade = 255 - shade;
    shade *= 4;
    x = side * 218;
    digit[0] = phase / 100 + '0'; digit[1] = 0;
    D_802956F4 += func_801BE540((FrontendGfxWords **)list, (void *)((D_802956F4 << 6) + D_802CA068), (u8 *)&D_80292CC4, x, 75.0f, -500.0f, 255, 255, 255, 255, 0.75f);
    shade &= 255;
    D_802956F4 += func_801BE540((FrontendGfxWords **)list, (void *)((D_802956F4 << 6) + D_802CA068), (u8 *)digit, x, 0.0f, -500.0f, (u8)shade, (u8)shade, (u8)shade, 255, D_80292CF0);
}
