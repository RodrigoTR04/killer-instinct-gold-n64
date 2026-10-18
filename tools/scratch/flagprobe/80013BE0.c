typedef int s32; typedef short s16; typedef unsigned char u8; typedef float f32; typedef double f64;
int func_80028600(int, f32, f32, int);                    /* extern */
extern s16 D_8004A530;
extern s32 D_8004ACF0;
extern f32 D_FLT_8004A9FC;
extern f32 D_FLT_8004AC84;
extern struct {float unk0, unk4, unk8;} D_FLT_80061CC8;

void func_80013BE0(void) {
    f32 temp_f0;

    if ((D_FLT_8004A9FC == 0.0f) && (D_8004ACF0 == 0)) {
        temp_f0 = D_FLT_8004AC84 / 2.0f;
        func_80028600(1, temp_f0, temp_f0, 0xF0);
        D_FLT_80061CC8.unk0 = 3.0f;
        D_FLT_80061CC8.unk8 = 3.0f;
        D_FLT_80061CC8.unk4 = 0.0f;
        D_8004A530 = 3;
        D_8004ACF0 = 1;
    }
}
