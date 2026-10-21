/* T-113 DRAFT: 0 differing instruction words, 256/256 B in the full TU.
 * Integration needs rodata ownership: current YAML leaves the original
 * jump table in asm-owned data, duplicating a compiler-generated table.
 * The packed-input caller passes one u64 in a0/a1. */
#include "common.h"

/* Return the menu-key ordinal for a single button in the packed input. */
u8 func_801C7998(u64 buttons)
{
    u8 index = 0;

    switch (buttons & 0xFFFF) {
    case 0: break;
    case 0x8000: index++; /* fall through */
    case 0x4000: index++; /* fall through */
    case 0x20: index++; /* fall through */
    case 0x10: index++; /* fall through */
    case 8: index++; /* fall through */
    case 4: index++; /* fall through */
    case 2: index++; /* fall through */
    case 1: index++;
    }
    return index;
}
