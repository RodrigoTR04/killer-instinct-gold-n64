/* DRAFT (T-060). 5 differing words (was 65); target size 384 bytes. Typed three-argument cloud call, command cursor, explicit visibility branches, direct alpha updates. Remaining: initial command and loop-initialization scheduling plus pointer-add operands. */
#include "common.h"

typedef struct { u32 w0,w1; } CloudCmd;

typedef struct {
    s16 x, y, z, angle, width;
    u8 padA;
    s8 alpha;
} T030Cloud;
extern void func_801C3758(CloudCmd **, T030Cloud *, s32);
extern u8 D_800F4070[];
extern s32 D_80290D88;
extern u32 D_80290F90[];
extern u8 *D_802D38E0;

void func_801C35D8(CloudCmd **arg0, T030Cloud *arg1, s32 arg2, s32 arg3) {
    CloudCmd *dl;
    s32 i, offset;
    s32 visible;
    T030Cloud *cloud;
    s16 start;
    s32 end;
    dl = (*arg0)++;
    dl->w0 = 0x06000000;
    dl->w1 = (u32)D_80290F90;
    D_802D38E0 = D_800F4070;
    i = 0;
    if (arg2 > 0) {
        cloud = arg1;
        offset = 0;
        do {
            start = cloud->angle;
            end = cloud->width + start;
            if ((arg3 >= start && arg3 < end) || arg3 + 360 < end) visible = 1; else visible = 0;
            if (visible || cloud->alpha > 0) {
                if (visible) {
                    cloud->alpha += 1;
                    if (cloud->alpha >= 17) cloud->alpha = 16;
                } else {
                    cloud->alpha -= 2;
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
