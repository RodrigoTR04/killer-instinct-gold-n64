/* DRAFT. Remaining diff: Instruction sequence matches apart from frame 0x88 versus 0x80 and perspective-normalization slot sp+0x86 versus sp+0x7E. */
extern void func_801AF5B8();
typedef struct { s32 w0; void *w1; } T025GfxF424;
extern void guPerspective(void *, u16 *, f32, f32, f32, f32, f32);
extern void guLookAtHilite(void *, void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32);
extern s32 guRandom(void);
extern f32 D_802927E0;
extern u8 D_802A8B80[], D_802A8B90[];
void func_801AF424(T025GfxF424 **arg0, void *arg1) {
    u16 perspNorm;
    void *view;
    void *projection;
    func_801AF5B8(arg1);
    projection = (u8 *)arg1 + 8;
    guPerspective(projection, &perspNorm, 33.0f, 1.333333373f, 2.0f, D_802927E0, 1.0f);
    view = (u8 *)arg1 + 0x48;
    guLookAtHilite(view, D_802A8B90, D_802A8B80, *(f32 *)((u8 *)arg1 + 0xC8), *(f32 *)((u8 *)arg1 + 0xCC), -*(f32 *)((u8 *)arg1 + 0xD0), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, (f32)(guRandom() % 64), *(f32 *)((u8 *)arg1 + 0xE0), -1.0f, -60.0f, 0.0f, -10.0f, 32, 32);
    {
    T025GfxF424 *g = (*arg0)++;
    g->w0 = 0x01030040;
    g->w1 = projection;
    }
    {
    T025GfxF424 *g = (*arg0)++;
    g->w0 = 0x01010040;
    g->w1 = view;
    }
    {
    T025GfxF424 *g = (*arg0)++;
    g->w0 = 0xB4000000;
    g->w1 = (void *)(u32)perspNorm;
    }
}
