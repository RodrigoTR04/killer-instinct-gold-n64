#include "common.h"

extern void func_8002B95C(u16 *,float,float,float,float,float);

extern void func_8002B8B0(s32);

extern float D_80048D70,D_800695B8,D_800695BC,D_800695C0,D_800695C4,D_800695C8,D_800695E0;

extern s32 D_800698C4;

extern u8 D_8004AC88;

void func_8002B7E0(void) { u16 norm;
 func_8002B95C(&norm,33.0f,1.3333334f,2.0f,D_80048D70,1.0f);
 D_800695B8=D_800695BC=D_800695C0=D_800695C4=D_800695C8=0.0f;
 if(D_8004AC88==12) D_800698C4=120;
 else D_800698C4=80;
 D_800695E0=0.0f;
 func_8002B8B0(0);
 }

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

extern float D_800695B8, D_800695BC, D_800695C0, D_800695C4, D_800695C8;
void func_8002B91C(float a, float b, float c, float d, float e) {
 D_800695B8=a; D_800695BC=b; D_800695C0=c; D_800695C4=d; D_800695C8=e; }

extern float D_80069700[4][4];
extern void guPerspectiveF(float [4][4],u16 *,float,float,float,float,float);
void func_8002B95C(u16 *norm,float fovy,float aspect,float near,float far,float scale) {
 guPerspectiveF(D_80069700,norm,fovy,aspect,near,far,scale); }

extern u8 D_80044A24;
extern float D_800695CC,D_800695D0,D_800695D4,D_800695D8,D_800695DC,D_800695E0;
extern float D_80069740[][4][4],D_80069840[][4][4],D_800697C0[][4][4],D_80069600[][4][4],D_80069680[][4][4];
extern void guRotateRPYF(void *,float,float,float),guTranslateF(void *,float,float,float),guMtxCatF(void *,void *,void *);
void func_8002B9B4(void)
{
    guRotateRPYF(D_80069740[D_80044A24], D_800695D8, 0.0f, 0.0f);
    guRotateRPYF(D_80069840[D_80044A24], 0.0f, D_800695DC, D_800695E0);
    guTranslateF(D_800697C0[D_80044A24], 0.0f - D_800695CC, 0.0f - D_800695D0, 0.0f - D_800695D4);
    guMtxCatF(D_800697C0[D_80044A24], D_80069840[D_80044A24], D_80069600[D_80044A24]);
    guMtxCatF(D_80069600[D_80044A24], D_80069740[D_80044A24], D_80069680[D_80044A24]);
}

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

extern float D_800695CC,D_800695D0,D_800695D4,D_80048EDC,D_8004AC84;
extern float sqrtf(float);
void func_8002DCC8(float x,float y,float z,u32 *distance) {
 float dx=D_800695CC-x,dy=D_800695D0-y,dz=D_800695D4-z; *distance=(u32)(D_80048EDC/(sqrtf(dx*dx+dy*dy+dz*dz)*D_8004AC84)); }

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002DDD4.s")

void func_8002DF98(float m[4][4],float x,float y,float z,float w,float *a,float *b,float *c,float *d) {
 *a=(m[0][0]*x+m[1][0]*y+m[2][0]*z)+m[3][0]*w; *b=(m[0][1]*x+m[1][1]*y+m[2][1]*z)+m[3][1]*w; *c=(m[0][2]*x+m[1][2]*y+m[2][2]*z)+m[3][2]*w; *d=(m[0][3]*x+m[1][3]*y+m[2][3]*z)+m[3][3]*w; }

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

