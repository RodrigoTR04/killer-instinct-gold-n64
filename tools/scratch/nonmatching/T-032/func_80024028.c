/* T-140 DRAFT: 45 differing words, 284/284 bytes in full context. */
typedef struct { u32 w0, w1; } T032Gfx24028;
extern u8 D_80045CD8[][9];
void func_80024028(T032Gfx24028 **dl, s32 kind, s32 fade) {
    T032Gfx24028 *p;
    u8 *color;
    s32 alpha;
    u8 red, green, blue;
    u32 packed;
    p = (*dl)++; p->w0 = 0xFA000100;
    if (fade == 64) alpha = 0; else alpha = 255 - fade * 4;
    color = D_80045CD8[kind];
    red = color[0];
    packed = (alpha & 255) | (red << 24);
    green = color[1];
    packed |= green << 16;
    blue = color[2];
    p->w1 = packed | (blue << 8);
    p = (*dl)++; p->w0 = 0xFB000000;
    p->w1 = (color[5] << 8) | (color[3] << 24) | (color[4] << 16);
    p = (*dl)++; p->w1 = 0xA00; p->w0 = 0xBA000903;
    p = (*dl)++; p->w0 = ((color[8] >> 5) & 15) | 0xEC000000 | (color[6] << 13) | (color[7] * 16);
    p->w1 = color[8] << 27;
}
