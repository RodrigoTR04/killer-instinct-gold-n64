/* DRAFT. Remaining diff: Counter/interpolation globals, pointer lifetime across the vertex helper, float temporaries and display-list scheduling differ. */
typedef struct { u32 w0, w1; } T025Gfx1DE4;
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

s32 func_801B1DE4(T025Gfx1DE4 **arg0, s32 arg1, void *arg2, s32 arg3) {
    f32 distance;
    f32 position;
    s32 frame;
    s32 frame_2;
    s32 alpha;
    T025Gfx1DE4 *temp_v1;
    T025Gfx1DE4 *temp_v1_2;
    T025Gfx1DE4 *temp_v1_3;

    frame = D_801D3098;
    D_801D3098 += 1;
    D_801D3090 = (s32) func_801B19F0(-200.0f, 400.0f, frame, 0x1E);
    frame_2 = D_801D3098;
    D_801D3094 = (s16) (s32) func_801B19F0(100.0f, -200.0f, D_801D3098, 0x46);
    if (frame_2 >= 0x1F) {
        func_801AF5EC(8);
        D_8029571A = 1;
    }
    if ((s32) D_801D308C > 0) {
        return 0;
    }
    if (frame_2 < 2) {
        position = func_801B19F0(-56.0f, -200.0f, frame_2, 1);
    } else {
        position = -200.0f;
    }
    guTranslate(arg2, position + 25.0f, 0.0f, (f32) D_801D3094);
    distance = position - (f32) D_801D3090;
    temp_v1 = *arg0;
    alpha = (s32) func_801B1A7C(&D_802BF8C0, &D_802BFE50, distance, 0x58);
    *arg0 = temp_v1 + 1;
    temp_v1->w0 = 0xFB000000;
    temp_v1->w1 = (s32) ((alpha & 0xFF) | 0xFFC80000);
    temp_v1_2 = *arg0;
    *arg0 = temp_v1_2 + 1;
    temp_v1_2->w1 = 0x64000000;
    temp_v1_2->w0 = 0xFA000000;
    if ((distance < 1.0f) && ((s32) D_801D3088 <= 0)) {
        D_801D3088 += 1;
    }
    temp_v1_3 = *arg0;
    *arg0 = temp_v1_3 + 1;
    temp_v1_3->w0 = 0x06000000;
    temp_v1_3->w1 = (s32) &D_801D3058;
    return 1;
}
