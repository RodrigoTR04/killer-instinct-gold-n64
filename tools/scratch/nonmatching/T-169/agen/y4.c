f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    f64 damt;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    damt = amount;
    for (i = 0; i <= count; i++) {
        if (arg1[i].z >= 6) {
            ratio = amount / radius;
            scale = (ratio * 256.0f) + 256.0f;
            arg0[i].y = (arg1[i].y * (s32)scale) >> 8;
            arg0[i].z = (s32)(damt * 0.5);
            arg0[i].x = ((arg1[i].x * (s32)scale) >> 8) + (s32)(ratio * distance);
        }
    }
    return (f32)((f64)amount * 1.5);
}
