#include "common.h"
extern u8 D_801D87AD, D_801D87AC;
void func_801AF2E8(void) {
s32 value = D_801D87AD;
if (value != 0) *(u16 *)&D_801D87AC = value << 8;
value = D_801D87AC;
if (value != 0) D_801D87AC = value - 1;
}
