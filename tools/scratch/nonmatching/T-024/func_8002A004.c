/* DRAFT. Remaining diff: 2 words (T-040; was 20); 324/324 bytes. BLOCKED BY RODATA: D_80048138 is the literal 0.017453292f in this TU's .rodata (owned by the data asm); with the literal it matches standalone. Stack slot order needs the declaration order below. */
extern float D_80048138;
extern float sinf(float), cosf(float);
extern void guMtxIdentF(void *);

void func_8002A004(float m[4][4], float x, float y, float z) {
    float sx, cx;
    float sz;
    float sy;
    float cy;
    float cz;

    x *= D_80048138;
    y *= D_80048138;
    z *= D_80048138;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);
    guMtxIdentF(m);
    m[1][2] = sx;
    m[0][0] = cy * cz - sx * sy * sz;
    m[0][1] = cy * sz + sx * sy * cz;
    m[0][2] = -sy * cx;
    m[1][0] = -cx * sz;
    m[1][1] = cx * cz;
    m[2][0] = sy * cz + sx * cy * sz;
    m[2][1] = sy * sz - sx * cy * cz;
    m[2][2] = cx * cy;
}
