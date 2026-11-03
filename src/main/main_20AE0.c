#include "render.h"


void func_80030440(u8 *image, s32 index) {
    s32 stride, source, y, x;
    D_80069E48[index].width = image[0];
    D_80069E48[index].height = image[1];
    D_80069E48[index].spacing = image[2];
    D_80069E48[index].baseline = image[3];
    stride = (D_80069E48[index].width + 7) & 0xFFF8;
    source = 8;
    for (y = 0;
    y < D_80069E48[index].height;
    y++) {
        s32 swap;
        if ((y & 1) == 0) swap = 0; else swap = 4;
        for (x = 0; x < D_80069E48[index].width; x++) {
            s32 run;
            s32 n;
            s32 j;
            run = image[source] & 0xF0;
            n = (image[source++] & 15) + 1;
            for (j = 0;
            j < n;
            j++) D_80069F70[index * 0x120 + ((x+j)^swap) + y*stride] = run;
            x += n - 1;
        }
        for (; x < stride; x++) {
            D_80069F70[index * 0x120 + (x^swap) + y*stride] = 0;
        }
    }
    for (x = 0;
    x < stride;
    x++) D_80069F70[index * 0x120 + x + y*stride] = 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/main/main_20AE0/func_800306B8.s")

s32 func_80030EF0(u8 code) {
    s32 character;

    character = code & 0xFF;
    if (character == 0x20) {
        return 0xFF;
    }
    if ((character >= 0x41) && (character < 0x5B)) {
        return character - 0x41;
    }
    if ((character >= 0x61) && (character < 0x7B)) {
        return character - 0x47;
    }
    if (character == 0x2E) {
        return 0x34;
    }
    if ((character >= 0x30) && (character < 0x3A)) {
        return character + 5;
    }
    if (character == 0x2D) {
        return 0x3F;
    }
    if (((character & 1) == 1) && (character >= 0x81) && (character < 0x88)) {
        return 0x40;
    }
    if ((character == 0x82) || (character == 0x86)) {
        return 0x41;
    }
    if ((character == 0x84) || (character == 0x80)) {
        return 0x42;
    }
    if (character == 0x2B) {
        return 0x43;
    }
    if (character == 0x27) {
        return 0x44;
    }
    if (character == 0x2C) {
        return 0x45;
    }
    if (character == 0x2F) {
        return 0x46;
    }
    if (character == 0x89) {
        return 0x47;
    }
    return 0x34;
}
