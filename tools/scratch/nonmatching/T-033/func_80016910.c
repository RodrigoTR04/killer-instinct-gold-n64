/* DRAFT. Remaining diff: 83 positional differing words; 728/720 bytes */
extern f32 cosf(f32), sinf(f32);
extern void func_8002DBDC(f32, f32 *), func_8002DC48(f32 *);
extern u32 func_800326F0(void);
extern f64 D_80048838, D_80048840, D_80048848, D_80048850;
extern f32 D_80048858;
extern f32 D_8004A8C0[], D_8004A988, D_8004A98C, D_8004A990, D_8004A994, D_8004ACE0;
extern s16 D_8004A986;
extern f32 D_80061CC8[], D_80061CD0;
extern u8 D_801D3430;

extern f32 D_8004A8C0[];
void func_80016910(void) {
    f32 x;
    if (D_8004A986 > 0) D_8004A986--;
    else {
        D_8004A986 = func_800326F0() & 255;
        D_8004A98C = (f32)(func_800326F0() & 255);
        D_8004A994 = (f32)(func_800326F0() % 360U);
    }
    D_8004A988 += (D_8004A98C - D_8004A988) / 5.0f;
    func_8002DBDC(D_8004A994, &D_8004A990);
    D_8004A990 += (D_8004A994 - D_8004A990) / 10.0f;
    func_8002DC48(&D_8004A990);
    x = sinf((D_8004A990 * D_80048838) / D_80048840) * D_8004A988;
    D_80061CC8[1] = 0.0f;
    D_80061CC8[0] = x / 256.0f;
    D_80061CD0 = cosf((D_8004A990 * D_80048848) / D_80048850) * D_8004A988 / 256.0f;
    if ((&D_801D3430)[-0x7B] != 0) D_8004ACE0 = 4.0f;
    if ((&D_801D3430)[-0x7A] != 0) D_8004ACE0 = 0.0f;
    if (D_8004ACE0 > 4.0f) D_8004ACE0 = 4.0f;
    D_8004A8C0[1] += D_8004ACE0;
    D_8004A8C0[2] += D_8004ACE0;
    D_8004ACE0 -= D_8004ACE0 / 20.0f;
    while (D_80048858 < D_8004A8C0[0]) D_8004A8C0[0] -= 360.0f;
    while (D_80048858 < D_8004A8C0[1]) D_8004A8C0[1] -= 360.0f;
}
