/* DRAFT. Remaining diff: 195 positional differing words; 824/800 bytes */
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
    s32 index, other;
    f32 *z, *pitch, *x, *y, *roll, *yaw;
    s32 offset;
    index = (s32)D_8004A4C0[2];
    other = (s32)D_8004A4C0[71];
    offset = index * 4;
    z = &D_8004A800[index];
    D_8004ACF8++;
    if (*z > 2000.0f || D_8004ACF8 < 2) {
        D_8004ACF8 = 1;
        (&D_8004A7A0)[index] = 0.0f;
        D_8004A740[index] = 4000.0f;
        *z = D_800488B0;
        D_8004A860[index] = 10.0f;
        D_8004A920[index] = -20.0f;
        D_8004A8C0[index] = -90.0f;
        D_8004ACE0 = 0.0f;
            func_8001BA94(0.0f);
    }
    D_8004A980 += 20.0f;
    pitch = &D_8004A860[index];
    x = &D_8004A740[index];
    y = &(&D_8004A7A0)[index];
    roll = &D_8004A920[index];
    yaw = &D_8004A8C0[index];
    if (D_800488B4 < D_8004A980) D_8004A980 -= 360.0f;
    if (*y < 2000.0f) *y += 50.0f;
    else {
        if (*yaw < 0.0f) func_8001BA94(D_800488B8);
        else func_8001BA94(0.0f);
        if (D_8004ACE0 < 110.0f) D_8004ACE0 += 1.0f;
        *yaw += D_8004ACE4;
    }
    func_8001B50C(index);
    (&D_8004A7A0)[other] = *y;
    D_8004A740[other] = *x;
    D_8004A800[other] = *z;
    if (*roll < -30.0f) *roll = -30.0f;
    D_8004A860[other] = *pitch;
    D_8004A920[other] = *roll;
    D_8004A8C0[other] = *yaw;
}
