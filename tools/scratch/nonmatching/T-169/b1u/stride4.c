typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    s32 n;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i + 3 <= count; i += 4) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32) ((f64) amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1[i + 1].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i + 1].y = (arg1[i + 1].y * scale) >> 8;
            arg0[i + 1].z = (s32) ((f64) amount * 0.5);
            arg0[i + 1].x = ((arg1[i + 1].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1[i + 2].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i + 2].y = (arg1[i + 2].y * scale) >> 8;
            arg0[i + 2].z = (s32) ((f64) amount * 0.5);
            arg0[i + 2].x = ((arg1[i + 2].x * scale) >> 8) + (s32) (ratio * distance);
        }
        if (arg1[i + 3].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i + 3].y = (arg1[i + 3].y * scale) >> 8;
            arg0[i + 3].z = (s32) ((f64) amount * 0.5);
            arg0[i + 3].x = ((arg1[i + 3].x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    for (; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s32) ((f64) amount * 0.5);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}
