/* T-145 DRAFT: 13 differing words; 556/556 bytes in the full TU. */
f32 func_801B19F0(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
void func_801AF5EC(s32 arg0);

typedef struct {
    u32 w0, w1;
} T025Gfx1DE4;
extern f32 func_801B1A7C(void *, void *, f32, s32);
extern void guTranslate(void *, f32, f32, f32);
extern u8 D_801D3058[];
extern u8 D_801D3088;
extern u8 D_801D308C;
extern s32 D_801D3090;
extern s16 D_801D3094;
extern s32 D_801D3098;
extern u8 D_8029571A;
extern u8 D_802BF8C0[];
extern u8 D_802BFE50[];

s32 func_801B1DE4(T025Gfx1DE4 **arg0, s32 arg1, void *arg2, s32 arg3) { f32 position; s32 frame; s32 alpha; T025Gfx1DE4 *temp_v1; frame = D_801D3098 + 1; D_801D3098 = frame;
    D_801D3090 = (s32) func_801B19F0(-200.0f, 400.0f, frame - 1, 0x1E);
    D_801D3094 = (s16) (s32) func_801B19F0(100.0f, -200.0f, D_801D3098, 0x46);
    arg3 = D_801D3098;
    if (arg3 >= 0x1F)
    {
        func_801AF5EC(8);
        D_8029571A = 1; arg3 = D_801D3098;
    }
    if ((s32) D_801D308C > 0)
    {
        return 0;
    }
    if (arg3 < 2)
    {
        position = func_801B19F0(-56.0f, -200.0f, arg3, 1);
    }
    else
    {
        position = -200.0f;
    }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    position = position - (f32) D_801D3090;
    alpha = (s32) func_801B1A7C(&D_802BF8C0, &D_802BFE50, position, 0x58);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFB000000;
    temp_v1->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFA000000; temp_v1->w1 = 0x64000000;
    if ((position < 1.0f) && ((s32) D_801D3088 <= 0))
    {
        D_801D3088 += 1;
    }
    temp_v1 = *arg0;
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0x06000000; temp_v1->w1 = (s32) &D_801D3058;
    return 1;
}
