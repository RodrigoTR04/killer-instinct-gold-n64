#include "common.h"

extern s32 D_801D9F48;

void func_801B6858(void) {
    s32 value = D_801D9F48;
    if (value > 0x20000) value = 0x20000;
    if (value < -0x20000) value = -0x20000;
    D_801D9F48 = value;
}
