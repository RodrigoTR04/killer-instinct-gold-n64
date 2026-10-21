/* T-121 DRAFT: 0 relocation-masked words; 668/668 bytes. Linked rodata unresolved. */
f32 func_801AFA80(f32 arg0, f32 arg1, s32 arg2, s32 arg3);
/* Exact text candidate; external constant ownership prevents promotion. See T-121/REPORT.md. */
typedef struct { u32 w0, w1; } T025Gfx0A40;
extern f32 cosf(f32), sinf(f32);
extern void guLookAtReflect(void *, void *, f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void guTranslate(void *, f32, f32, f32);
extern void guScale(void *, f32, f32, f32);
extern void guRotate(void *, f32, f32, f32, f32);
extern s32 func_8002F6F4();
extern s8 D_801CD454;
extern u8 D_801D2DF8[];
extern f64 D_802928E8;
extern f64 D_802928F0;
extern f64 D_802928F8;
extern f32 D_80292900;
extern u8 D_802C8780[];
extern u8 D_802C8790[];
extern s32 D_802CA064;

s32 func_801B0A40(T025Gfx0A40 **arg0, s32 arg1, u8 *arg2, u32 arg3)
    { u8 sp70[0x40];
    T025Gfx0A40 *temp_v1;
    T025Gfx0A40 *temp_v1_2;
    T025Gfx0A40 *temp_v1_3;
    struct { f32 x, y, z; } eye;
    f32 temp_f12;
    f32 temp_f0;

    temp_f0 = func_801AFA80(300.0f, 0.0f, arg3, 40);
    if (temp_f0 > 0.0f) {
        if (temp_f0 <= 60.0f) {
            temp_f0 = 120.0 - cosf(temp_f0 * D_802928E8 * 0.75) * 60.0f / D_802928F0;
        } else {
            D_801CD454 = 0;
            D_802CA064 = 0x280;
        }
        temp_f0 -= 35.0f;
    } else {
        temp_f0 = 0.0f;
    }
    temp_f12 = (f32) (((f64)arg3 * D_802928F8) / 2);
    eye.x = sinf(temp_f12);
    eye.y = cosf(temp_f12); eye.z = 220.0f;
    guLookAtReflect(&sp70, &D_802C8780, eye.x * 60.0f, eye.y * 60.0f, eye.z, 6.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    guScale(arg2, D_80292900, D_80292900, 1.0f); guTranslate(arg2 + 0x40, (f32) ((f64) (temp_f0 + 75.0f) - 8.0), 28.0f, 170.0f); temp_v1 = (*arg0)++;
    temp_v1->w0 = 0x03840010; temp_v1->w1 = (u32)&D_802C8780;
    temp_v1_2 = (*arg0)++;
    temp_v1_2->w0 = 0x03820010; temp_v1_2->w1 = (u32)&D_802C8790; temp_v1_3 = (*arg0)++; temp_v1_3->w0 = 0x06000000; temp_v1_3->w1 = (u32)&D_801D2DF8; return 2;
}
