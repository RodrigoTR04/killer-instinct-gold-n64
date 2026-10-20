/* DRAFT. Remaining diff: 2 linked instruction words; 320/320 bytes. BLOCKED BY RODATA (T-040): D_80045C00 is the literal 0.017453292f from this TU's .rodata (owned by the data asm); with the literal the lwc1/mtc1 order matches (as in func_8002A004). Frame and spill slots now match. */

s32 guMtxIdentF(f32 *);
extern f32 D_80045C00;

void func_8001CBCC(f32 *m, f32 x, f32 y, f32 z) {
    f32 pad0, siny, sinz, pad, cosy, cosz;
    f32 sinx, cosx;

    x *= D_80045C00;
    y *= D_80045C00;
    z *= D_80045C00;
    sinx = sinf(x);
    cosx = cosf(x);
    siny = sinf(y);
    cosy = cosf(y);
    sinz = sinf(z);
    cosz = cosf(z);
    guMtxIdentF(m);
    m[0] = -cosy * cosz;
    m[1] = -cosy * sinz;
    m[2] = siny;
    m[4] = sinx * siny * cosz - cosx * sinz;
    m[5] = sinx * siny * sinz + cosx * cosz;
    m[6] = sinx * cosy;
    m[8] = cosx * siny * cosz + sinx * sinz;
    m[9] = cosx * siny * sinz - sinx * cosz;
    m[10] = cosx * cosy;
}
