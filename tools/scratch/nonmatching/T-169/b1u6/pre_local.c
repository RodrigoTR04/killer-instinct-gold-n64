typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *dst = arg0v;
    T169Vertex *src = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    s32 n;
    s32 rem;
    amount = func_801B1A14(distance, radius, 200.0f);
    n = count + 1;
    rem = n & 3;
    for (i = 0; i < rem; i++) {
        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
    }
    for (; i != n; i += 4) {
        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
        if (src->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            dst->y = (src->y * scale) >> 8;
            dst->z = (s32) ((f64) amount * 0.5);
            dst->x = ((src->x * scale) >> 8) + (s32) (ratio * distance);
        }
        src++; dst++;
    }
    return (f32) ((f64) amount * 1.5);
}
