#include "common.h"

extern u8 *D_8000BF80, *D_8000BF84;
extern s32 D_8000BF88, D_8000BF8C;
extern u32 D_8000BF94, D_8000BF98, D_8000BF9C;
s32 func_80001410(void), func_80001564(void), func_800016CC(void);
s32 func_80001BF0(s32 *);

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_1560/func_80000960.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_1560/func_80000FA0.s")

s32 func_80001410(void) {
    u32 length;
    u32 bits = D_8000BF94;
    u32 count = D_8000BF98;
    s32 out = D_8000BF8C;
    length = count & 7;
    bits >>= length;
    count -= length;
    while (count < 16) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    length = bits & 0xFFFF;
    bits >>= 16;
    count -= 16;
    while (count < 16) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    bits >>= 16;
    count -= 16;
    while (length--) {
        while (count < 8) {
            bits |= D_8000BF80[D_8000BF88++] << count;
            count += 8;
        }
        D_8000BF84[out++] = bits;
        bits >>= 8;
        count -= 8;
    }
    D_8000BF8C = out;
    D_8000BF94 = bits;
    D_8000BF98 = count;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_1560/func_80001564.s")

#pragma GLOBAL_ASM("asm/nonmatchings/boot/boot_1560/func_800016CC.s")

s32 func_80001BF0(s32 *last) {
    u32 type;
    u32 bits = D_8000BF94;
    u32 count = D_8000BF98;
    while (count < 1) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    *last = bits & 1;
    bits >>= 1;
    count--;
    while (count < 2) {
        bits |= D_8000BF80[D_8000BF88++] << count;
        count += 8;
    }
    type = bits & 3;
    bits >>= 2;
    count -= 2;
    D_8000BF94 = bits;
    D_8000BF98 = count;
    if (type == 2) return func_800016CC();
    if (type == 0) return func_80001410();
    if (type == 1) return func_80001564();
    return 2;
}

s32 func_80001D10(void) {
    s32 last;
    s32 status;
    u32 maximum;
    D_8000BF8C = 0;
    D_8000BF98 = 0;
    D_8000BF94 = 0;
    maximum = 0;
    do {
        D_8000BF9C = 0;
        status = func_80001BF0(&last);
        if (status != 0) return status;
        if (maximum < D_8000BF9C) maximum = D_8000BF9C;
    } while (!last);
    while (D_8000BF98 >= 8) {
        D_8000BF98 -= 8;
        D_8000BF88--;
    }
    return 0;
}
