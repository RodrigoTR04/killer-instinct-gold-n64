#include "common.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_8002FB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_8002FDA0.s")

extern void func_8002FB80(s32, s32, s32, s32, s32);
extern void func_8002FDA0(s32, s32, s32);
void func_8002FFDC(s32 a, s32 b, s32 c, s32 d, s32 e, s32 f, s32 g) {
    func_8002FB80(a, b, f, e, g);
    func_8002FDA0(c, d, f);
}


extern void func_800300DC(void *, void *, s32);
extern void func_8002A40C(void *, void *, s32);
void func_80030020(void **sources, void **targets, u16 *lengths, u16 count) {
    void **src;
    void **dst;
    u16 *len;
    s32 i;
    s32 kind, length;
    void *source, *target;

    i = 0;
    if (count > 0) {
        src = sources;
        dst = targets;
        len = lengths;
        do {
            length = *len;
            source = *src;
            target = *dst;
            kind = length >> 13;
            length &= 0x1FFF;
            switch (kind) {
                case 0: func_800300DC(source, target, length); break;
                case 1: func_8002A40C(source, target, length); break;
            }
            src++;
            dst++;
            len++;
            i++;
        } while (i != count);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_800300DC.s")

void func_80030218(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_80030220.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_8003037C.s")
