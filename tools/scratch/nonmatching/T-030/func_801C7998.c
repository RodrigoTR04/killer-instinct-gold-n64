/* DRAFT. Remaining diff: C emits a jump table; 64-bit switch high-word setup, narrow increments and registers differ. */
#include "common.h"

u8 func_801C7998(u8 arg0, u16 buttons) {
    u8 index = 0;
    switch ((u64)buttons) {
    case 0x8000: index++;
    case 0x4000: index++;
    case 0x20: index++;
    case 0x10: index++;
    case 8: index++;
    case 4: index++;
    case 2: index++;
    case 1: index++;
    }
    return index;
}
