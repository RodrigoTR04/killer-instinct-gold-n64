#include "render.h"






void func_8002B7E0(void) { u16 norm;
 func_8002B95C(&norm,33.0f,1.3333334f,2.0f,D_80048D70,1.0f);
 D_800695B8=D_800695BC=D_800695C0=D_800695C4=D_800695C8=0.0f;
 if(D_8004AC88==12) D_800698C4=120;
 else D_800698C4=80;
 D_800695E0=0.0f;
 func_8002B8B0(0);
 }

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

void func_8002B91C(float a, float b, float c, float d, float e) {
 D_800695B8=a; D_800695BC=b; D_800695C0=c; D_800695C4=d; D_800695C8=e; }

void func_8002B95C(u16 *norm,float fovy,float aspect,float near,float far,float scale) {
 guPerspectiveF(D_80069700,norm,fovy,aspect,near,far,scale); }

void func_8002B9B4(void)
{
    guRotateRPYF(D_80069740[D_80044A24], D_800695D8, 0.0f, 0.0f);
    guRotateRPYF(D_80069840[D_80044A24], 0.0f, D_800695DC, D_800695E0);
    guTranslateF(D_800697C0[D_80044A24], 0.0f - D_800695CC, 0.0f - D_800695D0, 0.0f - D_800695D4);
    guMtxCatF(D_800697C0[D_80044A24], D_80069840[D_80044A24], D_80069600[D_80044A24]);
    guMtxCatF(D_80069600[D_80044A24], D_80069740[D_80044A24], D_80069680[D_80044A24]);
}

void func_8002BAF0(RenderWorldPoint *p) {
    p->worldX=(float)p->x/D_8004AC84;
    p->worldZ=(float)p->z/D_8004AC84+D_8004AC80;
    p->worldY=(float)p->y/D_8004AC84;
    p->height=(float)p->top/D_8004AC84+D_8004AC80;
}

void func_8002BB74(s32 x,s32 y,s32 z,float *outX,float *outZ,float *outY) {
    *outX=(float)x/D_8004AC84;
    *outZ=(float)z/D_8004AC84+D_8004AC80;
    *outY=(float)y/D_8004AC84;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002BBD0.s")

void func_8002D9C4(RenderCameraPose *pose, s32 frame, s32 duration, s32 reverse) {
    float to[5], from[5];
    s32 i;
    if (reverse == 0) {
        for (i = 0; i < 5; i++) to[i] = ((float *)pose)[i];
        from[0] = D_800695CC;
        from[1] = D_800695D0;
        from[2] = D_800695D4;
        from[3] = D_800695D8;
        from[4] = D_800695DC;
    }
    else {
        for (i = 0; i < 5; i++) from[i] = ((float *)pose)[i];
        to[0] = D_800695CC;
        to[1] = D_800695D0;
        to[2] = D_800695D4;
        to[3] = D_800695D8;
        to[4] = D_800695DC;
    }
    D_800695CC = from[0]+(to[0]-from[0])*(float)frame/(float)duration;
    D_800695D0 = from[1]+(to[1]-from[1])*(float)frame/(float)duration;
    D_800695D4 = from[2]+(to[2]-from[2])*(float)frame/(float)duration;
    func_8002DBDC(to[3], &from[3]);
    D_800695D8 = from[3]+(to[3]-from[3])*(float)frame/(float)duration;
    func_8002DC48(&D_800695D8);
    func_8002DBDC(to[4], &from[4]);
    D_800695DC = from[4]+(to[4]-from[4])*(float)frame/(float)duration;
    func_8002DC48(&D_800695DC);
}


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

void func_8002DCC8(float x,float y,float z,u32 *distance) {
 float dx=D_800695CC-x,dy=D_800695D0-y,dz=D_800695D4-z; *distance=(u32)(D_80048EDC/(sqrtf(dx*dx+dy*dy+dz*dz)*D_8004AC84)); }

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_1BE80/func_8002DDD4.s")

void func_8002DF98(float m[4][4],float x,float y,float z,float w,float *a,float *b,float *c,float *d) {
 *a=(m[0][0]*x+m[1][0]*y+m[2][0]*z)+m[3][0]*w; *b=(m[0][1]*x+m[1][1]*y+m[2][1]*z)+m[3][1]*w; *c=(m[0][2]*x+m[1][2]*y+m[2][2]*z)+m[3][2]*w; *d=(m[0][3]*x+m[1][3]*y+m[2][3]*z)+m[3][3]*w; }

void func_8002E08C(RenderCameraInput *in, RenderCameraOutput *out) {
    out->x = in->x / D_8004AC84;
    out->z = in->z / D_8004AC84 + D_8004AC80;
    out->y = in->y / D_8004AC84;
    func_8002DCC8(out->x, out->z, out->y, &in->distance);
    func_8002DDD4(out->x, out->z, out->y, &in->a, &in->b);
}

