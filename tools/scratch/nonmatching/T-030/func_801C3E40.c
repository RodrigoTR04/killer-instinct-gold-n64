/* DRAFT. Remaining diff: Display-list/count/index registers, vertex updates and instruction scheduling differ. */
#include "common.h"

typedef struct { u32 w0, w1; } T030Cmd3E40;
typedef struct { s16 x,y,z; u16 flag; s16 s,t; u8 r,g,b,a; } T030Vertex3E40;
typedef struct { T030Vertex3E40 v[3]; } T030Triangle3E40;
extern u8 D_80291808[];
extern f32 D_802937D0, D_802D38F0, D_802D38F4;
extern s32 D_802D38F8, D_802D38FC;
extern s32 D_802D3900[16];
extern T030Triangle3E40 *D_802D3940;

void func_801C3E40(T030Cmd3E40 **arg0) {
    T030Cmd3E40 *dl;
    s32 count, index, slot;
    s8 dx, dy;
    D_802D38F4 = D_802D38F0;
    D_802D38F0 = D_802937D0;
    if (D_802D38F8 != 0) {
        dl = (*arg0)++; dl->w0 = 0x01060040; dl->w1 = (u32)D_802D3900;
        dl = (*arg0)++; dl->w0 = 0x06000000; dl->w1 = (u32)D_80291808;
        count = D_802D38F8;
        index = D_802D38FC;
        if (count > 0) {
            do {
                slot = index & 255;
                dl = (*arg0)++; count--;
                dl->w0 = 0x04200030; dl->w1 = (u32)&D_802D3940[slot];
                dl = (*arg0)++; dl->w1 = 0xA14; dl->w0 = 0xBF000000;
                D_802D3940[slot].v[0].a -= 32;
                if (D_802D3940[slot].v[0].a < 32) {
                    D_802D3940[slot].v[0].a = 32;
                    D_802D38F8--;
                    D_802D38FC = (D_802D38FC+1)&255;
                } else {
                    dx = D_802D3940[slot].v[1].r;
                    D_802D3940[slot].v[0].x += dx;
                    D_802D3940[slot].v[1].x += dx;
                    D_802D3940[slot].v[2].x += dx;
                    dy = D_802D3940[slot].v[1].g;
                    D_802D3940[slot].v[0].y += dy;
                    D_802D3940[slot].v[1].y += dy;
                    D_802D3940[slot].v[2].y += dy;
                }
                index = slot+1;
            } while (count > 0);
        }
    }
}
