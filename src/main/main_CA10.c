#include "common.h"

extern u32 func_800326F0();
extern u8 D_8004A730[8];
extern u8 D_8004A738[8];
extern s8 D_8004A5E0[][7], D_8004A688[][7];
extern f32 D_8004AC84;
extern u8 D_8004AA28, D_8004AC88;
extern void (*D_8004AA30)(void);
extern u8 *D_8004ACD8;
extern void func_80019880(void);
extern f32 sinf(f32), cosf(f32);
extern s32 guMtxIdentF(f32 *);

void func_8001C370(u8 **arg0, s32 arg1, s32 arg2, u8 *arg3) {
    s32 i, j;
    s32 value;
    for (i = 0; i < arg1; i++) {
        for (j = 0; j < 3; j++) {
            value = arg3[i * 16 + j + 12] - (func_800326F0() & arg2);
            if (value < 0) arg0[i][j + 12] = 0;
            else arg0[i][j + 12] = value;
        }
    }
}



void func_8001C43C(s32 count, u8 *n, u8 *data, u8 *m, u8 *other) {
    s32 i, j, second = 0, first = 0;

    for (i = 0; i < count; i++) {
        D_8004A730[i] = n[i];
        for (j = 0; j < n[i];) {
            j++;
            D_8004A5E0[j - 1][i] = data[first++];
        }
        D_8004A738[i] = m[i];
        for (j = 0; j < m[i];) {
            j++;
            D_8004A688[j - 1][i] = other[second++];
        }
    }
}


extern u8 D_80044ECC[];
extern void func_8001BB10(void), func_8001C05C(u8 *);
void func_8001C534(void) {
    D_8004AC84 = 75.0f;
    D_8004AA28 = 1;
    func_8001BB10();
    D_8004AA30 = func_80019880;
    D_8004AC88 = 0;
    D_8004ACD8 = (u8 *)0x801AAB20;
    func_8001C05C(D_80044ECC);
}

extern s32 D_8004AEB0;

void func_8001C5A0(void) {
    D_8004AEB0 = 0;
}

typedef struct { u32 w0,w1; } T069Gfx;
extern u8 D_80044A24, D_8004A984;
extern f32 D_8004A980;
typedef union { s64 align; s32 words[16]; } T069Matrix;
typedef struct { T069Matrix matrices[3][20]; } T069Frame;
extern T069Frame D_8004AEB8[];
extern T069Gfx *D_8004A998[][4];
extern void func_8001BB64(T069Gfx **);
extern void guTranslate(void *,f32,f32,f32),guRotateRPY(void *,f32,f32,f32),guScale(void *,f32,f32,f32);
extern void func_8001CD0C(void *,f32,f32,f32);
#define MATRIX(n) (&D_8004AEB8[D_80044A24].matrices[n][D_8004AEB0])
#define EMIT(a,b) { T069Gfx *g=(*arg0)++; g->w0=(a); g->w1=(u32)(b); }
#define MATRIX_CMD(n,op) { T069Gfx *g=(*arg0)++; g->w0=(op); g->w1=(u32)MATRIX(n); }
void func_8001C5AC(T069Gfx **arg0,s32 mode,T069Gfx *display,s32 group,s32 count,f32 x,f32 y,f32 z,f32 rx,f32 ry,f32 rz,s32 scale) {
 s32 i;
 f32 factor;
 if ((display || D_8004A998[group][3-count]) && D_8004AEB0 != 20) {
  if (mode == 0) { EMIT(0xB7000000,0x2000); EMIT(0xB6000000,0x1000); }
  else { EMIT(0xB6000000,0x2000); EMIT(0xB7000000,0x1000); }
  EMIT(0xE7000000,0);
  func_8001BB64(arg0);
  guTranslate(MATRIX(0),x,y,z);
  if (mode == 1) func_8001CD0C(MATRIX(1),rx,ry,rz);
  else guRotateRPY(MATRIX(1),rx,ry,rz);
  if (D_8004A984) guRotateRPY(MATRIX(1),rx,ry,rz);
  MATRIX_CMD(0,0x01040040);
  MATRIX_CMD(1,0x01000040);
  if (D_8004A984) {
   guRotateRPY(MATRIX(2),0.0f,D_8004A980,0.0f);
   MATRIX_CMD(2,0x01000040);
  } else if (scale != 0 && scale != 4096) {
   factor=(f32)scale / 4096;
   guScale(MATRIX(2),factor,factor,factor);
   MATRIX_CMD(2,0x01000040);
  }
  if (display) { EMIT(0x06000000,display); }
  else for (i=3;i>=3-count;i--) {
   if (D_8004A998[group][i]) {
    T069Gfx *g=(*arg0)++; g->w0=0x06000000; g->w1=(u32)D_8004A998[group][i];
   }
  }
  EMIT(0xBD000000,0);
  if (mode) { EMIT(0xB7000000,0x2000); EMIT(0xB6000000,0x1000); }
  EMIT(0xE7000000,0); EMIT(0xB9000002,0);
  D_8004AEB0++;
 }
}
#undef MATRIX
#undef EMIT
#undef MATRIX_CMD


void func_8001CBCC(f32 *m, f32 x, f32 y, f32 z) {
    f32 pad0, siny, sinz, pad, cosy, cosz;
    f32 sinx, cosx;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sinx = sinf(x);
    cosx = cosf(x);
    siny = sinf(y);
    cosy = cosf(y);
    sinz = sinf(z);
    cosz = cosf(z);
    guMtxIdentF(m);
    m[0] = -cosy * cosz;
    m[1] = -cosy * sinz;
    m[2] = siny;
    m[4] = sinx * siny * cosz - cosx * sinz;
    m[5] = sinx * siny * sinz + cosx * cosz;
    m[6] = sinx * cosy;
    m[8] = cosx * siny * cosz + sinx * sinz;
    m[9] = cosx * siny * sinz - sinx * cosz;
    m[10] = cosx * cosy;
}


extern void guMtxF2L(void *, void *);
void func_8001CD0C(void *arg0, f32 arg1, f32 arg2, f32 arg3) {
    f32 matrix[4][4];
    func_8001CBCC(&matrix[0][0], arg1, arg2, arg3);
    guMtxF2L(matrix, arg0);
}
