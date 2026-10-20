#include "common.h"

extern s32 D_80065C60, D_80065C68, D_80065C6C;
extern void func_8002A194(s32);
void func_8002A150(s32 a, s32 b) {
    s32 z = 0; D_80065C60 = z; func_8002A194(z);
    D_80065C68 = a;
    D_80065C6C = b;
}


extern s32 D_80065C7C;
void func_8002A194(s32 value) {
    D_80065C7C = value;
}

extern u8 D_80063C60[][0x800], D_80064C60[][0x800];
extern void *D_80065C64, *D_80065C70;
void func_8002A1A0(u8 index) {
    D_80065C64 = D_80063C60[index];
    D_80065C70 = D_80064C60[index];
}

