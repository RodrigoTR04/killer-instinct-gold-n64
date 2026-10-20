/* T-065 DRAFT: 6 differing words, 256 bytes. Byte result and explicit zero case recover the table range; high-word initialization remains. */
#include "common.h"

u8 func_801C7998(u8 arg0, u16 buttons) {
    u8 index = 0;
    switch ((u64)(buttons & 0xFFFF)) {
    case 0: break;
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
