#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_80024CE0.s")

extern void func_8001D768(s32, s32 *);
extern s32 D_800470C0[], D_80046EF0[], D_8011E670[], D_8011E990[];
extern s16 D_80061490[2];
extern u8 D_80061494[2], D_8004D26C;
void func_80025354(void) {
    func_8001D768(6, D_800470C0);
    func_8001D768(7, D_80046EF0);
    func_8001D768(8, D_8011E670);
    func_8001D768(9, D_8011E990);
    D_80061490[0] = 0; D_80061490[1] = 0;
    D_80061494[0] = 0; D_80061494[1] = 0;
    D_8004D26C = 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_800253D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_800257FC.s")

typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite25D;
extern T032Sprite25D D_8004CED0[];
extern s32 D_8004EA78;
typedef struct { u8 value[13]; } T032Height13;
typedef struct { u8 value[14]; } T032Height14;
extern T032Height13 D_80047DAC;
extern T032Height14 D_80047DBC;
void func_80025D58(s32 x, s32 color, s32 alpha, s32 kind) {
    s32 y;
    s32 pixelXor;
    s32 alphaXor;
    s32 height;
    T032Height13 heights;
    T032Height14 otherHeights;
    heights = D_80047DAC;
    otherHeights = D_80047DBC;
    height = (kind == 0 ? heights.value[x-6] : otherHeights.value[x-111]);
    for (y=10; y < height + 10; y++) {
        if ((y & 1) == 1) { alphaXor=4; pixelXor=2; }
        else { alphaXor=0; pixelXor=0; }
        D_8004CED0[D_8004EA78].pixels[(y * D_8004CED0[D_8004EA78].w2 + x) ^ pixelXor]=color;
        D_8004CED0[D_8004EA78].alpha[(y * ((D_8004CED0[D_8004EA78].w2+7)&0xFFF8) + x) ^ alphaXor]=alpha;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_80025FC4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_80026738.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_15380/func_800268C0.s")

typedef struct { u32 w0, w1; } T032Gfx269AC;
extern void func_8001EC74(T032Gfx269AC **, s32, s32, s32, s32, s32, s32, s32);
extern s32 D_8004EA78, D_801D8760, D_801D8764, D_801D8768;
extern u8 D_801D5D50[];
void func_800269AC(T032Gfx269AC **dl)
{
    T032Gfx269AC *environment;
    T032Gfx269AC *p;
    T032Gfx269AC *primitive;
    if (D_801D8760)
    {
        if ((D_801D5D50[2] == 0) && (D_801D5D50[1] == 0))
        {
            D_8004EA78 = 30;
        }
        else
        {
            D_8004EA78 = 29;
        }
        p = (*dl)++; p->w1 = 0; p->w0 = 0xE7000000;
        primitive = (*dl)++; primitive->w0 = 0xFA000100; primitive->w1 = 255;
        environment = (*dl)++; p = environment; p->w0 = 0xFB000000; p->w1 = 0;
        func_8001EC74(dl, D_801D8760 * 16, D_801D8764 * 16, D_801D8768, D_801D8768, 8, 0, 0);
    }
}
