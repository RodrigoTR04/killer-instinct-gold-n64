/* T-045 DRAFT: 49 standalone relocation-masked positional words; 284 compiled bytes. Was 53 words/284 bytes. Changed disjoint packed-color fields expressed with arithmetic/bitwise operations. Not linked/runtime validated. */
typedef struct { u32 w0, w1; } T032Gfx24028;
extern u8 D_80045CD8[][9];
void func_80024028(T032Gfx24028 **dl, s32 kind, s32 fade) {
    T032Gfx24028 *p;
    u8 *color;
    s32 alpha;
    p = (*dl)++; p->w0 = 0xFA000100;
    if (fade == 64) alpha = 0; else alpha = 255 - fade * 4;
    color = D_80045CD8[kind];
    p->w1 = (alpha & 255) + (color[0] << 24) | (color[1] << 16) + (color[2] << 8);
    p = (*dl)++; p->w0 = 0xFB000000;
    p->w1 = (color[5] << 8) | (color[3] << 24) | (color[4] << 16);
    p = (*dl)++; p->w1 = 0xA00; p->w0 = 0xBA000903;
    p = (*dl)++; p->w0 = ((color[8] >> 5) & 15) | 0xEC000000 | (color[6] << 13) | (color[7] * 16);
    p->w1 = color[8] << 27;
}
