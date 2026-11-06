typedef struct { u32 w0, w1; } T025Gfx0520;
typedef struct { s32 pad; void *list; } T025ListState;
extern void guTranslate(void *, f32, f32, f32);
extern void func_801C3AA0(f32, f32, f32, f32, f32);
extern u8 D_801D2F40[];
extern s32 D_801D2EBC;
extern s32 D_802956F8, D_802956FC, D_80295700;

s32 func_801B0520(T025Gfx0520 **arg0, T025ListState *arg1, void *arg2, s32 arg3) {
    s32 *frame = &D_801D2EBC;
    T025Gfx0520 *g;

    do { *frame = arg3 * 2; } while (0);
    if (*frame < 230) {
        guTranslate(arg2, 0.0f, (f32) *frame, 0.0f);
        arg1->list = D_801D2F40;
        if (D_802956F8 >= 16) {
            g = (*arg0)++;
            g->w0 = 0xFB000000;
            g->w1 = ((D_802956F8 & 255) << 24) | ((D_802956FC & 255) << 16) | ((D_80295700 & 255) << 8) | 255;
        } else {
            g = (*arg0)++;
            g->w0 = 0xFB000000; g->w1 = 255;
        }
        if (*frame < 220) {
            func_801C3AA0(0.0f, (f32) (*frame - 105), 0.0f, 80.0f, -90.0f);
        }
        return 1;
    }
    return 0;
}
