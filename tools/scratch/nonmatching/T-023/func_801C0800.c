/* DRAFT. Remaining diff: Display-list temporaries, packed-color arguments and scheduling differ. */
typedef struct { u32 w0, w1; } T023Gfx0800;
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_80282E88[];
extern s32 D_802956F4, D_802CA068;
void func_801C0800(T023Gfx0800 **list, f32 x, f32 y, f32 z, u8 r, u8 g, u8 b, u8 a) {
    T023Gfx0800 *p;
    guTranslate((void *)((D_802956F4 << 6) + D_802CA068), x, y, z);
    p = (*list)++;
    p->w0 = 0x01020040;
    p->w1 = (D_802956F4 << 6) + D_802CA068;
    p = (*list)++;
    p->w0 = 0xFA000000;
    p->w1 = (r << 24) | (g << 16) | (b << 8) | a;
    p = (*list)++;
    p->w0 = 0x06000000;
    p->w1 = (u32)D_80282E88;
    D_802956F4++;
}
