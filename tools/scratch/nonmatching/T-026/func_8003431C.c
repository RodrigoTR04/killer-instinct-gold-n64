/* DRAFT. Remaining diff: 54 differing instruction words; emitted 200 / original 216 bytes (positional comparison). */
typedef struct { u8 a,b,c,d,e,f,g,h; } T026StatusCommand;
extern u8 D_8006F080[], D_8006F0C0[], D_8006F111;
void func_8003431C(s32 command) {
    T026StatusCommand request;
    u8 *p = D_8006F080;
    s32 i;
    do { *(s32 *)p = 0; p += 4; } while ((u32)p < (u32)D_8006F0C0);
    D_8006F080[0x3C] = 1;
    request.a = 0xFF;
    request.b = 1;
    request.c = 3;
    request.d = command;
    request.e = 0xFF;
    request.f = 0xFF;
    request.g = 0xFF;
    request.h = 0xFF;
    p = D_8006F080;
    for (i = 0; i < D_8006F111; i++) {
        *(T026StatusCommand *)p = request;
        p += 8;
    }
    *p = 0xFE;
}
