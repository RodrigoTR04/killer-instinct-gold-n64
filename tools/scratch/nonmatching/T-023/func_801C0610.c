/* DRAFT. Remaining diff: Display-list base registers, matrix address loads and scheduling differ. */
typedef struct { u32 w0, w1; } T023Gfx0610;
extern void guTranslate(void *, f32, f32, f32);
extern s32 D_802956F4, D_802CA068;
extern u8 D_8029C4B0[], D_8029C8B0[], D_802C9F70[];
void func_801C0610(T023Gfx0610 **list) {
    T023Gfx0610 *p;
    p = (*list)++; p->w0 = 0xFB000000; p->w1 = 0x0F000410;
    p = (*list)++; p->w1 = 0x3C010110;
    p->w0 = 0xFA000000;
    guTranslate((void *)((D_802956F4 << 6) + D_802CA068), 60.0f, 5.0f, 270.0f);
    p = (*list)++; p->w0 = 0x01020040;
    p->w1 = (D_802956F4 << 6) + *(s32 *)(D_802C9F70 + 0xF8);
    p = (*list)++; p->w1 = (u32)D_8029C4B0; p->w0 = 0x06000000;
    guTranslate((void *)(((D_802956F4 + 1) << 6) + *(s32 *)(D_802C9F70 + 0xF8)), -40.0f, -15.0f, 270.0f);
    p = (*list)++; p->w0 = 0x01020040;
    p->w1 = ((D_802956F4 + 1) << 6) + D_802CA068;
    p = (*list)++; p->w0 = 0x06000000; p->w1 = (u32)D_8029C8B0;
    D_802956F4 += 2;
}
