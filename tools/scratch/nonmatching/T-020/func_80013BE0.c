/* DRAFT T-020: Two instruction words differ: IDO folds division by 2.0f to multiplication by 0.5f. */
extern f32 D_8004A9FC, D_8004AC84;
extern s32 D_8004ACF0;
extern f32 D_80061CC8[];
extern s16 D_8004A530;
extern void func_80028600(s32, f32, f32, s32);

void func_80013BE0(void) {
    f32 half;
    if (D_8004A9FC == 0.0f && D_8004ACF0 == 0) {
        half = D_8004AC84 / 2.0f;
        func_80028600(1, half, half, 240);
        D_80061CC8[0] = 3.0f;
        D_80061CC8[2] = 3.0f;
        D_80061CC8[1] = 0.0f;
        D_8004A530 = 3;
        D_8004ACF0 = 1;
    }
}
