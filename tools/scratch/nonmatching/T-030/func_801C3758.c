/* T-105: nonmatching draft; see T-105/REPORT.md for measurement and remaining differences. */
#include "common.h"

typedef struct { s16 x,y,z; u16 flag; s16 s,t; u8 rgba[4]; } T030Vertex3758;
extern s32 D_80290D88;
extern s16 D_80290D8C[][6];
#define T105Vertices ((T030Vertex3758 *)D_802D38E0)

void func_801C3758(arg0,arg1,arg2)
CloudCmd **arg0; T030Cloud *arg1; s8 arg2;
{
    s32 frame, next;
    s16 *uv;
    CloudCmd *dl;
    frame = (arg1->padA + 12) & 255;
    next = frame;
    if (frame >= 64) { frame = 0; next = 0; }
    arg1->padA = frame;
    T105Vertices[D_80290D88].x = arg1->x - arg2;
    T105Vertices[D_80290D88+1].x = arg1->x + arg2;
    T105Vertices[D_80290D88+2].x = arg1->x;
    T105Vertices[D_80290D88].y = arg1->y - arg2;
    T105Vertices[D_80290D88+1].y = arg1->y - arg2;
    T105Vertices[D_80290D88+2].y = arg1->y + arg2;
    T105Vertices[D_80290D88].z = arg1->z;
    T105Vertices[D_80290D88+1].z = arg1->z;
    T105Vertices[D_80290D88+2].z = arg1->z;
    uv = D_80290D8C[next >> 3];
    T105Vertices[D_80290D88].s = uv[0];
    T105Vertices[D_80290D88].t = uv[1];
    T105Vertices[D_80290D88+1].s = uv[2];
    T105Vertices[D_80290D88+1].t = uv[3];
    T105Vertices[D_80290D88+2].s = uv[4];
    T105Vertices[D_80290D88+2].t = uv[5];
    dl = *arg0; *arg0 = dl+1;
    dl->w0 = 0x04200030;
    dl->w1 = (u32)&T105Vertices[D_80290D88];
    dl = *arg0; *arg0 = dl+1;
    dl->w1 = 0xA14;
    dl->w0 = 0xBF000000;
    D_80290D88 += 3;
}
