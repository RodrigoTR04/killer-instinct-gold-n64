#include "render.h"

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_8002FB80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20220/func_8002FDA0.s")

void func_8002FFDC(u8 *a, s32 b, u8 *c, s32 d, u32 *e, RenderVertex *f, u8 *g) {
    func_8002FB80(a, b, (u32)f, e, g);
    func_8002FDA0(c, d, f);
}


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

void func_8003037C(s16 *input, s16 *deltas, s32 count) {
    s16 *vertices;
    s16 *delta;
    s16 *end;
    if (count > 0) {
        vertices = input;
        delta = deltas; end = deltas + count;
        do {
            vertices[0] += delta[0];
            vertices[8] += delta[0];
            vertices[16] += delta[0];
            vertices[1] +=
            delta[1];
            vertices[9] += delta[1];
            vertices[17] += delta[1];
            vertices[2] += delta[2];
            vertices[10] += delta[2];
            vertices[18] += delta[2];
            delta += 3;
            vertices += 24;
        }
        while ((u32)delta < (u32)end);
    }
}
