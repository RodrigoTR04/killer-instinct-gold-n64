/* T-172 w3: four pointer locals, end pointer D_801D5C30. */
#include "common.h"

extern u8 D_8004AA28;
extern f32 D_8004A920[];
extern T05518664Obj D_801D3430[40], D_801D5C30[1];

void func_800191F0(void) {
    T05518664Obj *p0, *p1, *p2, *p3;
    f32 unit = 256.0f;
    if (D_8004AA28 == 0) {
        for (p0 = D_801D3430; p0 != D_801D5C30; p0 += 4) {
            p1 = p0 + 1;
            p2 = p0 + 2;
            p3 = p0 + 3;
            if (p0->type == 0x3C) {
                D_8004A920[0] -= (f32)p0->vx / unit;
                p0->vx = (s16)((f32)p0->vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p1->type == 0x3C) {
                D_8004A920[0] -= (f32)p1->vx / unit;
                p1->vx = (s16)((f32)p1->vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p2->type == 0x3C) {
                D_8004A920[0] -= (f32)p2->vx / unit;
                p2->vx = (s16)((f32)p2->vx + D_8004A920[0] * unit / 200.0f);
            }
            if (p3->type == 0x3C) {
                D_8004A920[0] -= (f32)p3->vx / unit;
                p3->vx = (s16)((f32)p3->vx + D_8004A920[0] * unit / 200.0f);
            }
        }
    }
}
