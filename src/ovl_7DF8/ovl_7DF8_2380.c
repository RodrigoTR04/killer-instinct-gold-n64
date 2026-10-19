#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801ADEA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AF424.s")

typedef struct { u8 pad[0xC8]; f32 x, y, z; } T025Position;

void func_801AF5B8(T025Position *arg0) {
    arg0->x = 0.0f;
    arg0->y = 0.0f;
    arg0->z = -600.0f;
}

extern s32 D_802A2178;

void func_801AF5D4(s32 arg0) {
    D_802A2178 |= arg0;
}

typedef struct { s32 pad0[2]; s32 flags; s32 padC; s32 state; u8 pad14[0x54]; } T025Effect;

extern T025Effect D_801D18B8[];
extern T025Effect D_801D2DD8[];
extern s32 D_802A2178;

void func_801AF5EC(s32 arg0) {
    s32 i;
    D_802A2178 &= -1 ^ arg0;
    for (i = 0; i < 52; i++) {
        if (D_801D18B8[i].flags & arg0) D_801D18B8[i].state = -1;
    }
}

extern s32 D_802A2178;

s32 func_801AF67C(s32 arg0) {
    return D_802A2178 & arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_2380/func_801AF68C.s")

extern s32 D_802A1A60[];
extern s32 D_802A1A80;
void func_801AFA48(s32 arg0) {
    if (D_802A1A80 < 7) {
        D_802A1A60[D_802A1A80] = arg0;
        D_802A1A80++;
    }
}
