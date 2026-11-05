/* T-172 w1: 4-wide pointer walk over D_801D3430. */
#include "common.h"

extern u8 D_8004AA28;
extern f32 D_8004A920[];

extern T05518664Obj D_801D3430[40];

void func_800191F0(void) {
    T05518664Obj *obj;
    f32 unit = 256.0f;
    s32 i;
    if (D_8004AA28 == 0) {
        for (i = 0; i < 40; i += 4) {
            obj = &D_801D3430[i];
            if (obj[0].type == 0x3C) {
                D_8004A920[0] -= (f32)obj[0].vx / unit;
                obj[0].vx = (s16)((f32)obj[0].vx + D_8004A920[0] * unit / 200.0f);
            }
            if (obj[1].type == 0x3C) {
                D_8004A920[0] -= (f32)obj[1].vx / unit;
                obj[1].vx = (s16)((f32)obj[1].vx + D_8004A920[0] * unit / 200.0f);
            }
            if (obj[2].type == 0x3C) {
                D_8004A920[0] -= (f32)obj[2].vx / unit;
                obj[2].vx = (s16)((f32)obj[2].vx + D_8004A920[0] * unit / 200.0f);
            }
            if (obj[3].type == 0x3C) {
                D_8004A920[0] -= (f32)obj[3].vx / unit;
                obj[3].vx = (s16)((f32)obj[3].vx + D_8004A920[0] * unit / 200.0f);
            }
        }
    }
}
