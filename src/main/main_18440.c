#include "common.h"

extern void guOrtho(void *, f32, f32, f32, f32, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern u8 D_80061D20[], D_80061CE0[];
void func_80027DA0(void) {
    guOrtho(D_80061D20, 0.0f, 320.0f, 240.0f, 0.0f, 1.0f, 10.0f, 1.0f);
    guRotate(D_80061CE0, 0, 0.0f, 0.0f, 1.0f);
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80027E1C.s")

extern u8 D_A69A20[], D_A69A40[], D_A69A70[];
extern s16 D_80061CD8, D_80061CDA;
extern void boot_dma(void *, void *, s32);

void func_800281C4(s32 index) {
    u8 *start, *end;

    if (index == 0) {
        start = D_A69A20;
        end = D_A69A40;
    } else {
        start = D_A69A40;
        end = D_A69A70;
    }
    boot_dma(start, (void *)0x803A5200, end - start);
    D_80061CD8 = ((s32 *)0x803A5200)[0];
    D_80061CDA = ((s32 *)0x803A5200)[1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80028230.s")

extern u8 D_800614D0, D_80061CD4, D_80061CD5;
extern s16 D_80061CD6;
extern float D_80061528, D_8006152C, D_80061530, D_80061CC8[3];
extern void func_8002970C(s32, s32);

s32 func_80028600(s32 count, float scaleX, float scaleY, s32 mode) {
    s32 i, j;

    D_800614D0 = count;
    D_80061528 = 205.0f / scaleX;
    D_80061530 = 205.0f / scaleY;
    D_8006152C = D_80061528 * 14.0f;
    D_80061CD4 = mode;
    D_80061CD5 = 1;
    D_80061CD6 = 1;
    for (i = 0; i < 3; i++) {
        D_80061CC8[i] = 0.0f;
    }
    for (i = 0; i < D_800614D0; i++) {
        for (j = 0; j < 20; j++) {
            func_8002970C(i, j);
        }
    }
}


extern u8 D_80061CD4,D_80061CD5;
extern s16 D_80061CD6;
extern u32 func_800326F0(void);
void func_80028708(void) {
    if (D_80061CD4!=255) {
        if (D_80061CD6>0) {
            D_80061CD6--;
            return;
        }
        D_80061CD5^=1;
        D_80061CD6=func_800326F0()&0x1FF;
        if (D_80061CD5==1) D_80061CD6=(D_80061CD6*255)/(256-D_80061CD4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_800287D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80028A00.s")

typedef struct { float x,y,z; s16 active,timer; } T024Particle;
extern T024Particle D_80061538[][20];
extern u32 func_800326F0(void);
void func_8002970C(s32 group, s32 index) {
    D_80061538[group][index].active = 1;
    D_80061538[group][index].x = 0.0f;
    D_80061538[group][index].y = 0.0f;
    D_80061538[group][index].z = 0.0f;
    D_80061538[group][index].timer = (func_800326F0() >> 28) + 100;
}


typedef struct { u8 pad[0x12C]; s16 timer; u8 tail[0x12]; } T024ResetEffect;
extern T024ResetEffect D_80061D60[];
void func_80029770(void) {
    s32 i;
    for (i=0;i<4;i++) D_80061D60[i].timer=-1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_800297A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80029AB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_18440/func_80029BE0.s")

extern float sinf(float), cosf(float);
extern void guMtxIdentF(void *);

void func_8002A004(float m[4][4], float x, float y, float z) {
    float sx, cx;
    float sz;
    float sy;
    float cy;
    float cz;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);
    guMtxIdentF(m);
    m[1][2] = sx;
    m[0][0] = cy * cz - sx * sy * sz;
    m[0][1] = cy * sz + sx * sy * cz;
    m[0][2] = -sy * cx;
    m[1][0] = -cx * sz;
    m[1][1] = cx * cz;
    m[2][0] = sy * cz + sx * cy * sz;
    m[2][1] = sy * sz - sx * cy * cz;
    m[2][2] = cx * cy;
}
