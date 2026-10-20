#include "common.h"

extern u8 D_801D9FC8, D_801D9FC4, D_801DA001;
extern s8 D_801D87E6;
extern u8 D_801D87E4, D_801D9F37, D_801D9F33;
extern u8 D_801C3FC0[][16], D_801D3430[], D_801D3530[];
extern u8 *D_801D919C;

void func_801ADD20(void) {
    s32 result = 50;
    s32 index, row, adjust;
    u8 *table;
    if (D_801D9FC8 == 0) {
        index = D_801D9FC4;
        if (index >= 15) index = 15;
        row = D_801DA001;
        if (row >= 6) row = 5;
        table = D_801C3FC0[row];
        adjust = D_801D87E6;
        if (adjust < (s8)table[14]) adjust = (s8)table[14];
        if ((s8)table[15] < adjust) adjust = (s8)table[15];
        D_801D87E6 = adjust;
        result = table[index];
        if (index == 0) D_801D87E6 = 0;
        result += D_801D87E6;
        if (result <= 0) result = 1;
        if (result >= 51) {
            if (result >= 60) {
                if (D_801D9F37 != 0) D_801D919C = D_801D3430;
                else if (D_801D9F33 != 0) D_801D919C = D_801D3530;
            }
            result = 50;
        }
    }
    D_801D87E4 = result;
}
