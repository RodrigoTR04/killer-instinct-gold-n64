#include "common.h"

f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
    return ((arg1 - arg0) * ((f32) arg2 / (f32) arg3)) + arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801AFAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801AFFAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B01EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0520.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0668.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0A40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B0CDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B1210.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B132C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/ovl_7DF8/ovl_7DF8_3F60/func_801B17BC.s")

typedef struct { u8 pad[0x10]; s32 state; } T025State;
extern void func_801C0610(s32);
extern void func_801C49A8(s32, s32, s32, s32, s32, s32, s32);
extern u8 D_8029571A;
extern u8 D_802C8724;
s32 func_801B18BC(s32 arg0, T025State *arg1, s32 arg2, u32 arg3) {
    s32 i, n;
    if (arg3 >= 0xF1U) {
        D_8029571A++;
        arg1->state = -1;
    }
    func_801C0610(arg0);
    for (i = 0; i != 3; i++) {
        if (D_802C8724 & (1 << i)) n = 12;
        else n = 15;
        func_801C49A8(arg0, i, 0x82000 + i * 0xC8000, 0x172000, (n << 12) / 10, 0, 0);
    }
    return 0;
}
