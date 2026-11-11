#include "common.h"

extern u8 D_8004AA28;
extern f32 D_8004A920[];
extern T05518664Obj D_801D3430[40];

void func_800191F0(void) {
    T05518664Obj *p;
    s32 i;
    f32 unit = 256.0f;
    if (D_8004AA28 == 0) {
        for (i = 0; i < 40; i += 4) {
            p = &D_801D3430[i];
            if ((*p).type == 0x3C) {
                { s16 v = (*p).vx; (*p).vx = v; }
                D_8004A920[0] -= (f32)(*p).vx / unit;
                (*p).vx = (s16)((f32)(*p).vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p[1].type == 0x3C) {
                { s16 v = p[1].vx; p[1].vx = v; }
                D_8004A920[0] -= (f32)p[1].vx / unit;
                p[1].vx = (s16)((f32)p[1].vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p[2].type == 0x3C) {
                { s16 v = p[2].vx; p[2].vx = v; }
                D_8004A920[0] -= (f32)p[2].vx / unit;
                p[2].vx = (s16)((f32)p[2].vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p[3].type == 0x3C) {
                { s16 v = p[3].vx; p[3].vx = v; }
                D_8004A920[0] -= (f32)p[3].vx / unit;
                p[3].vx = (s16)((f32)p[3].vx + D_8004A920[0] * unit / 200.0f);
            }
        }
    }
}
