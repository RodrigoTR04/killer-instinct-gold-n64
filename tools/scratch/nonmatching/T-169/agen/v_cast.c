f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;

f32 func_801B1A7C(void *arg0, void *arg1, f32 distance, s32 count) {
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++) {
        if (((T169Vertex *)arg1)[i].z >= 6) {
            ratio = amount / radius;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            ((T169Vertex *)arg0)[i].y = (((T169Vertex *)arg1)[i].y * scale) >> 8;
            ((T169Vertex *)arg0)[i].z = (s32)((f64)amount * 0.5);
            ((T169Vertex *)arg0)[i].x = ((((T169Vertex *)arg1)[i].x * scale) >> 8) + (s32)(ratio * distance);
        }
    }
    return (f32)((f64)amount * 1.5);
}
