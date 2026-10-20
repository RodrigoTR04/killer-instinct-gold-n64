/* DRAFT (T-046). UNCHANGED: 2 linked instruction words (+0x04/+0x08); 320/320 bytes. D_80045C00 is at image offset 0x362A0, outside main_2FF0's later 0x38E40-0x393B0 rodata pool. A 0.017453292f literal fixes scheduling standalone but emits a constant in the later pool, so its load address does not match. The T-043 ownership recipe alone does not solve this function; retain the extern load until the early constant's section/TU provenance is resolved. */

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
