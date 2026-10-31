/* T-143 DRAFT: 70 differing words; 800/800 bytes in full TU. */
extern void *D_8004A4C0[];
extern f32 D_8004A740[], D_8004A800[], D_8004A860[], D_8004A8C0[], D_8004A920[], D_8004A7A0;
extern f32 D_8004A980, D_8004ACE0, D_8004ACE4, D_800488B0, D_800488B4, D_800488B8;
extern s32 D_8004ACF8;
extern void func_8001B50C(s32);
extern void func_8001BA94(f32);

extern f32 D_8004A740[];
extern f32 D_8004A800[];
extern f32 D_8004A860[];
extern f32 D_8004A8C0[];
extern f32 D_8004A920[];
void func_80017D6C(void) {
    s32 index, other; s32 offset;
    f32 *pitch, *x, *yaw;
    index = (s32)D_8004A4C0[2];
    other = (s32)D_8004A4C0[71];
    offset = index * 4;
    D_8004ACF8++;
    if ((*(f32 *)((u8 *)D_8004A800 + offset)) > 2000.0f || D_8004ACF8 < 2) {
        D_8004ACF8 = 1;
        (&D_8004A7A0)[index] = 0.0f;
        D_8004A740[index] = 4000.0f;
        (*(f32 *)((u8 *)D_8004A800 + offset)) = D_800488B0;
        D_8004A860[index] = 10.0f;
        D_8004A920[index] = -20.0f;
        D_8004A8C0[index] = -90.0f;
        D_8004ACE0 = 0.0f;
            func_8001BA94(0.0f);
    }
    D_8004A980 += 20.0f;
    pitch = &D_8004A860[index];
    x = &D_8004A740[index];
    yaw = &D_8004A8C0[index];
    if (D_800488B4 < D_8004A980) D_8004A980 -= 360.0f;
    if ((&D_8004A7A0)[index] < 2000.0f) (&D_8004A7A0)[index] += 50.0f;
    else {
        if (*yaw < 0.0f) func_8001BA94(D_800488B8);
        else func_8001BA94(0.0f);
        if (D_8004ACE0 < 110.0f) D_8004ACE0 += 1.0f;
        *yaw += D_8004ACE4;
    }
    func_8001B50C(index);
    (&D_8004A7A0)[other] = (&D_8004A7A0)[index];
    D_8004A740[other] = *x;
    D_8004A800[other] = (*(f32 *)((u8 *)D_8004A800 + offset));
    if (D_8004A920[index] < -30.0f) D_8004A920[index] = -30.0f;
    D_8004A860[other] = *pitch;
    D_8004A920[other] = D_8004A920[index];
    D_8004A8C0[other] = *yaw;
}
