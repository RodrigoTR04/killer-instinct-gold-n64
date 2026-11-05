f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; count >= i; i++) {
        if (arg1[i].z > 5) {
            ratio = amount / radius;
            scale = (s16)((ratio * 256.0f) + 256.0f);
            arg0[i].x = ((arg1[i].x * scale) >> 8) + (s32)(ratio * distance);
            arg0[i].y = (arg1[i].y * scale) >> 8;
            arg0[i].z = (s16)((f64)amount * 0.5);
        }
    }
    return (f32)((f64)amount * 1.5);
}
