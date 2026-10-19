/* DRAFT. Remaining diff: 147 positional words differ; 328/620 bytes */
typedef struct { u16 *pixels; u8 *alpha; s16 halfW,halfH,w,h,w2,h2; u8 pad[4]; s16 flags; u8 tail[2]; } T032Sprite25D;
extern T032Sprite25D D_8004CED0[];
extern s32 D_8004EA78;
typedef struct { u8 value[13]; } T032Height13;
typedef struct { u8 value[14]; } T032Height14;
extern T032Height13 D_80047DAC;
extern T032Height14 D_80047DBC;
void func_80025D58(s32 x, s16 color, s8 alpha, s32 kind) {
    T032Height13 heights = D_80047DAC;
    T032Height14 otherHeights = D_80047DBC;
    s32 y, end, pixelXor, alphaXor;
    end = (kind == 0 ? heights.value[x-6] : otherHeights.value[x-111]) + 10;
    for (y=10;y<end;y++) {
        if ((y & 1) == 1) { pixelXor=2; alphaXor=4; }
        else { pixelXor=0; alphaXor=0; }
        D_8004CED0[D_8004EA78].pixels[(y * D_8004CED0[D_8004EA78].w2 + x) ^ pixelXor]=color;
        D_8004CED0[D_8004EA78].alpha[(y * ((D_8004CED0[D_8004EA78].w2+7)&0xFFF8) + x) ^ alphaXor]=alpha;
    }
}
