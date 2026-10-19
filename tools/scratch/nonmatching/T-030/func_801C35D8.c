/* DRAFT. Remaining diff: Visibility-flag branch shape, saved-register assignment and display-list scheduling differ. */
#include "common.h"

typedef struct {
    s16 x, y, z, angle, width;
    u8 padA;
    s8 alpha;
} T030Cloud;
extern void func_801C3758();
extern u8 D_800F4070[];
extern s32 D_80290D88;
extern u32 D_80290F90[];
extern u8 *D_802D38E0;

void func_801C35D8(u32 **arg0, T030Cloud *arg1, s32 arg2, s32 arg3) {
    u32 *dl;
    s32 i, offset;
    s32 visible;
    T030Cloud *cloud;
    s16 start;
    s32 end;
    s8 alpha;
    dl = *arg0;
    *arg0 = dl + 2;
    dl[0] = 0x06000000;
    dl[1] = (u32)D_80290F90;
    D_802D38E0 = D_800F4070;
    i = 0;
    if (arg2 > 0) {
        offset = 0;
        cloud = arg1;
        do {
            start = cloud->angle;
            end = cloud->width + start;
            if (((arg3 >= start) && (arg3 < end)) || (visible = 0, arg3 + 360 < end)) visible = 1;
            if (visible || cloud->alpha > 0) {
                alpha = cloud->alpha;
                if (visible) {
                    cloud->alpha = alpha + 1;
                    if (cloud->alpha >= 17) cloud->alpha = 16;
                } else {
                    cloud->alpha = alpha - 2;
                    if (cloud->alpha <= 0) cloud->alpha = 0;
                }
                func_801C3758(arg0, (u8 *)arg1 + offset, cloud->alpha);
            } else cloud->alpha = 0;
            i++;
            offset += 12;
            if (D_80290D88 >= 60) D_80290D88 = 0;
            cloud++;
        } while (i != arg2);
    }
}
