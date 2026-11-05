f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);

f32 func_801B1A7C(T169Vertex *arg0, T169Vertex *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32)((f64)amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32)(ratio * distance);
        }
        arg0++;
        arg1++;
    }
    return (f32)((f64)amount * 1.5);
}
