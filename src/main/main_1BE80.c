#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002B7E0.s")

extern s32 D_800695B0;
extern s8 D_800695B4;
void func_8002B8B0(s32 mode) {
    switch (mode) {
        case 1:
            D_800695B0 = 0x2B750;
            break;
        case 2:
        case 3:
            D_800695B0 = 0x11170;
            break;
        case 0:
        default:
            D_800695B0 = 0x17ED0;
            break;
    }
    D_800695B4 = mode;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002B91C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002B95C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002B9B4.s")

typedef struct { s32 x,y,z; float worldX,worldZ,worldY,height; u8 pad[8]; s32 top; } T024WorldPoint;
extern float D_8004AC84,D_8004AC80;
void func_8002BAF0(T024WorldPoint *p) {
    p->worldX=(float)p->x/D_8004AC84;
    p->worldZ=(float)p->z/D_8004AC84+D_8004AC80;
    p->worldY=(float)p->y/D_8004AC84;
    p->height=(float)p->top/D_8004AC84+D_8004AC80;
}

extern float D_8004AC84, D_8004AC80;
void func_8002BB74(s32 x,s32 y,s32 z,float *outX,float *outZ,float *outY) {
    *outX=(float)x/D_8004AC84;
    *outZ=(float)z/D_8004AC84+D_8004AC80;
    *outY=(float)y/D_8004AC84;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002BBD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002D9C4.s")

void func_8002DBDC(float target,float *angle) {
    float current=*angle;
    float delta=target-current;
    if (delta > 180.0f) {
        *angle=current+360.0f;
        return;
    }
    if (delta < -180.0f) *angle=current-360.0f;
}

void func_8002DC48(float *angle) {
    while (*angle < 0.0f) *angle += 360.0f;
    while (*angle >= 360.0f) *angle -= 360.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002DCC8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002DDD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002DF98.s")

typedef struct { s32 pad, x, y, z; u8 pad10[0x58]; float a, b; u32 distance; } T024CameraInput;
typedef struct { u8 pad[0xC]; float x, z, y; } T024CameraOutput;
extern float D_8004AC84, D_8004AC80;
extern void func_8002DCC8(float, float, float, u32 *);
extern void func_8002DDD4(float, float, float, float *, float *);
void func_8002E08C(T024CameraInput *in, T024CameraOutput *out) {
    out->x = in->x / D_8004AC84;
    out->z = in->z / D_8004AC84 + D_8004AC80;
    out->y = in->y / D_8004AC84;
    func_8002DCC8(out->x, out->z, out->y, &in->distance);
    func_8002DDD4(out->x, out->z, out->y, &in->a, &in->b);
}

