typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
f32 func_801B1A7C(T169Vertex *arg0v, T169Vertex *arg1v, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    s32 n;
    amount = func_801B1A14(distance, radius, 200.0f);
    n = count + 1;
    for (i = 0; i < (n & 3); i++) {
        if (arg1v[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0v[i].y = (arg1v[i].y * scale) >> 8;
            arg0v[i].z = (s32) ((f64) amount * 0.5);
            arg0v[i].x = ((arg1v[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    for (; i != n; i += 4) {
        if (arg1v[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0v[i].y = (arg1v[i].y * scale) >> 8;
            arg0v[i].z = (s32) ((f64) amount * 0.5);
            arg0v[i].x = ((arg1v[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1v[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0v[i].y = (arg1v[i].y * scale) >> 8;
            arg0v[i].z = (s32) ((f64) amount * 0.5);
            arg0v[i].x = ((arg1v[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1v[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0v[i].y = (arg1v[i].y * scale) >> 8;
            arg0v[i].z = (s32) ((f64) amount * 0.5);
            arg0v[i].x = ((arg1v[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1v[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0v[i].y = (arg1v[i].y * scale) >> 8;
            arg0v[i].z = (s32) ((f64) amount * 0.5);
            arg0v[i].x = ((arg1v[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}
