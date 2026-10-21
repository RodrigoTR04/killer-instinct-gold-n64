#include "frontend.h"
/* DRAFT. Remaining diff: only temp-register numbering (target uses t7/t6/t8/t9 in the loop, two registers later than here; tail uses t0..t5). Instruction sequence identical. Needs the D_80127D30 macro (see func_801CA7E4). */



extern s32 func_801BF914(s32);
extern u32 D_80127D00[8];
extern u8 D_80127D20[8];
extern u8 D_80127D28[8];

void func_801C8AE0(u8 *arg0) {
    s32 i;
    u16 c;

    for (i = 0; i < 8; i++) {
        c = func_801BF914((D_80127D00[i] >> 24) & 0xFF) << 10;
        c |= func_801BF914((D_80127D00[i] >> 16) & 0xFF) << 5;
        c |= func_801BF914((D_80127D00[i] >> 8) & 0xFF);
        *arg0++ = c >> 8;
        *arg0++ = c;
        *arg0++ = D_80127D20[i];
        *arg0++ = D_80127D28[i];
    }
    *arg0++ = (D_80127D30[1] << 4) | D_80127D30[0];
    *arg0++ = (D_80127D30[3] << 4) | D_80127D30[2];
    *arg0++ = (D_80127D30[5] << 4) | D_80127D30[4];
    *arg0++ = (D_80127D30[7] << 4) | D_80127D30[6];
}
