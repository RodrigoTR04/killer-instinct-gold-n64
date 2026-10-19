/* DRAFT. Remaining diff: Extra argument spill, frame-wrap assignments, vertex/display-list registers and scheduling differ. */
#include "common.h"

typedef struct { s16 x,y,z,angle,width; u8 frame; s8 alpha; } T030Cloud3758;
typedef struct { s16 x,y,z; u16 flag; s16 s,t; u8 rgba[4]; } T030Vertex3758;
extern s32 D_80290D88;
extern s16 D_80290D8C[][6];
extern T030Vertex3758 *D_802D38E0;

void func_801C3758(u32 **arg0, T030Cloud3758 *arg1, s8 arg2) {
    s32 frame, next;
    s16 *uv;
    u32 *dl;
    frame = (arg1->frame + 12) & 255;
    next = frame;
    if (frame >= 64) { next = 0; frame = 0; }
    arg1->frame = next;
    D_802D38E0[D_80290D88].x = arg1->x - arg2;
    D_802D38E0[D_80290D88+1].x = arg1->x + arg2;
    D_802D38E0[D_80290D88+2].x = arg1->x;
    D_802D38E0[D_80290D88].y = arg1->y - arg2;
    D_802D38E0[D_80290D88+1].y = arg1->y - arg2;
    D_802D38E0[D_80290D88+2].y = arg1->y + arg2;
    D_802D38E0[D_80290D88].z = arg1->z;
    D_802D38E0[D_80290D88+1].z = arg1->z;
    D_802D38E0[D_80290D88+2].z = arg1->z;
    uv = D_80290D8C[frame >> 3];
    D_802D38E0[D_80290D88].s = uv[0];
    D_802D38E0[D_80290D88].t = uv[1];
    D_802D38E0[D_80290D88+1].s = uv[2];
    D_802D38E0[D_80290D88+1].t = uv[3];
    D_802D38E0[D_80290D88+2].s = uv[4];
    D_802D38E0[D_80290D88+2].t = uv[5];
    dl = *arg0; *arg0 = dl+2;
    dl[0] = 0x04200030;
    dl[1] = (u32)&D_802D38E0[D_80290D88];
    dl = *arg0; *arg0 = dl+2;
    dl[1] = 0xA14;
    dl[0] = 0xBF000000;
    D_80290D88 += 3;
}
