typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;
f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
extern f32 D_802937C0;
f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    f32 amount;
    f32 radius = 50.0f;
    f32 ratio;
    s16 scale;
    s32 i;
    amount = func_801B1A14(distance, radius, 200.0f);
    for (i = 0; i <= count; i++, arg0++, arg1++) {
        if (arg1->z >= 6) {
            ratio = amount / radius;
            scale = (s32) ((ratio * 256.0f) + 256.0f);
            arg0->y = (arg1->y * scale) >> 8;
            arg0->z = (s32) ((f64) amount * 0.5);
            arg0->x = ((arg1->x * scale) >> 8) + (s32) (ratio * distance);
        }
    }
    return (f32) ((f64) amount * 1.5);
}