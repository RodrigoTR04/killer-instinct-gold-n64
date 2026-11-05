/* T-160 draft: 57 positional words, 928 bytes; matches target trig registers. */
/* DRAFT. Remaining diff: Particle/random arithmetic, saved float/integer registers and vertex-store scheduling differ. */
#include "common.h"

extern f32 sinf(f32), cosf(f32);
extern s32 guRandom(void);
extern f64 D_802937C8;
extern f32 D_802D38F0, D_802D38F4;
extern s32 D_802D38F8, D_802D38FC;


void func_801C3AA0(f32 x, f32 y, f32 z, f32 width, f32 angle) {
    f32 radians, count, remaining, offset;
    f32 xPosition = x, yPosition = y;
    s32 index, i, random, absRandom, px, py, pz, intWidth;
    if (D_802D38F8 != 256) {
        radians = angle * D_802937C8;
        x = sinf(radians);

        y = cosf(radians);

        count = (256.0f-D_802D38F8)*(width/D_802D38F4);
        remaining = 256 - D_802D38F8;
        if (remaining < count) count = remaining;
        if ((f64)(count/width) > 0.5) count = (f64)width * 0.5;
        i = 0;
        index = D_802D38FC + D_802D38F8;
        if (count > 0.0f) {
            intWidth = width;
            pz = z;
            do {
                index &= 255;

                random = (f32)(guRandom() % (intWidth*2)) - width;
                absRandom = random;
                offset = random;
                px = xPosition-offset*x;
                py = offset*y+yPosition;
                D_802D3940[index * 3 + 0].x = px-30;
                D_802D3940[index * 3 + 0].y = py;
                D_802D3940[index * 3 + 0].z = pz;
                D_802D3940[index * 3 + 0].a = 255;
                if (random < 0) absRandom = -random;
                D_802D3940[index * 3 + 1].a = (absRandom*8)/intWidth;
                D_802D3940[index * 3 + 1].x = px+30;
                D_802D3940[index * 3 + 1].y = py;
                D_802D3940[index * 3 + 1].z = pz;
                D_802D3940[index * 3 + 2].x = px;
                D_802D3940[index * 3 + 2].y = py-30;
                D_802D3940[index * 3 + 2].z = pz;
                D_802D3940[index * 3 + 1].r = guRandom()%3;
                D_802D3940[index * 3 + 1].g = guRandom()%5-1;
                i++;
                index++;
            } while ((f32)i < count);
        }
        D_802D38F8 += i;
        D_802D38F0 += width;
    }
}
