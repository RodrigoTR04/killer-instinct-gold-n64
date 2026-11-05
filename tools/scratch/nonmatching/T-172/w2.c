/* T-172 w2: 4-wide pointer walk with end pointer. */
#include "common.h"

extern u8 D_8004AA28;
extern f32 D_8004A920[];

extern T05518664Obj D_801D3430[40];

void func_800191F0(void) {
    T05518664Obj *obj, *end;
    f32 unit = 256.0f;
    if (D_8004AA28 == 0) {
        end = &D_801D3430[40];
        for (obj = D_801D3430; obj != end; obj += 4) {
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
