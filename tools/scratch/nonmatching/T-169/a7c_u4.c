/* Explicit 4x vertex unroll: prologue handles (count+1) & 3, then groups of four. */
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;

#define T169_VERTEX(s, d) \
    if ((s)->z >= 6) { \
        ratio = amount / radius; \
        scale = (s32)((ratio * 256.0f) + 256.0f); \
        (d)->y = ((s)->y * scale) >> 8; \
        (d)->z = (s32)((f64)amount * 0.5); \
        (d)->x = (((s)->x * scale) >> 8) + (s32)(ratio * distance); \
    }

f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 n;
    s32 i;

    amount = func_801B1A14(distance, radius, 200.0f);
    if (count >= 0) {
        n = count + 1;
        for (i = 0; i != (n & 3); i++) {
            T169_VERTEX(arg1, arg0)
            arg1++;
            arg0++;
        }
        for (; i != n; i += 4) {
            T169_VERTEX(arg1, arg0)
            arg1++;
            arg0++;
            T169_VERTEX(arg1, arg0)
            arg1++;
            arg0++;
            T169_VERTEX(arg1, arg0)
            arg1++;
            arg0++;
            T169_VERTEX(arg1, arg0)
            arg1++;
            arg0++;
        }
    }
    return (f32)((f64)amount * 1.5);
}
