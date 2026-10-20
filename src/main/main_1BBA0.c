#include "common.h"

typedef struct { u16 button; s8 stick_x, stick_y; u8 errno; u8 pad; } T040ContPad;
extern u8 D_800684E0[], D_800684F8[];
extern T040ContPad D_800684B8[4];
extern void *D_800684D0[];
extern s32 D_8004A284;
extern void osSetEventMesg(s32, void *, s32);
void func_8002B500(void) {
    osCreateMesgQueue(D_800684E0, D_800684F8, 8);
    osSetEventMesg(5, D_800684E0, D_8004A284);
    D_800684D0[0] = &D_800684B8[0];
    D_800684D0[1] = &D_800684B8[1];
    D_800684D0[2] = &D_800684B8[2];
    D_800684D0[3] = &D_800684B8[3];
}


typedef struct { u16 type;
 u8 status,error;
 } T052ContStatus;

extern T052ContStatus D_800684A8[4];
 extern u8 D_80068518,D_80068520,D_800684E0[];
 extern s32 D_800684A0;

extern s32 osContInit(void *,u8 *,void *);

void func_8002B57C(void) { s32 i;
 while(osContInit(D_800684E0,&D_80068518,D_800684A8)) {} D_800684A0=0;
 for(i=0;
i<4;
i++) if((D_80068518&(1<<i)) && !(D_800684A8[i].error&8)) { D_80068520|=1<<i;
 D_800684A0++;
 } }

extern u8 D_800684E0[];
extern s32 osContStartReadData(void *);
void func_8002B6EC(void) {
    osContStartReadData(D_800684E0);
}

extern u8 D_800684E0[], D_8006851C[];
extern u8 D_80068520;
extern void *D_800684D0[];
extern void osContGetReadData(void *);
extern s32 osRecvMesg(void *, void *, s32);
void *func_8002B710(void) {
    s32 i;

    osRecvMesg(D_800684E0, D_8006851C, 1);
    osContGetReadData(D_800684B8);
    D_80068520 = 0;
    for (i = 0; i < 4; i++) {
        if (D_800684B8[i].errno == 0) {
            D_80068520 |= 1 << i;
        }
    }
    return D_800684D0;
}

