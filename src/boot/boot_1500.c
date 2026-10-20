#include "common.h"

extern s32 func_80001D10(void);
extern s32 D_8000BF80, D_8000BF84, D_8000BF88, D_8000BF8C, D_8000BF90;

s32 boot_inflate(s32 arg0, s32 arg1, s32 arg2) {
    D_8000BF80 = arg0;
    D_8000BF84 = arg1;
    D_8000BF90 = arg2;
    D_8000BF80 += 2;
    D_8000BF8C = 0;
    D_8000BF88 = 0;
    func_80001D10();
    return D_8000BF8C;
}
