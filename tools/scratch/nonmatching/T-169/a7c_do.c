f32 func_801B1A14(f32 arg0, f32 arg1, f32 arg2);
typedef struct { s16 x, y, z; u8 rest[10]; } T169Vertex;

f32 func_801B1A7C(void *arg0v, void *arg1v, f32 distance, s32 count) {
    T169Vertex *arg0 = arg0v;
    T169Vertex *arg1 = arg1v;
    T169Vertex *s;
    T169Vertex *d;
    f32 amount;
    f32 ratio;
    s16 scale;
    s32 i;

    amount = func_801B1A14(distance, 50.0f, 200.0f);
    s = arg1;
    d = arg0;
    i = 0;
    do {
        if (s->z >= 6) {
            ratio = amount / 50.0f;
            scale = (s32)((ratio * 256.0f) + 256.0f);
            d->y = (s16)((s->y * scale) >> 8);
            d->z = (s32)((f64)amount * 0.5);
            d->x = (s16)(((s->x * scale) >> 8) + (s32)(ratio * distance));
        }
        s++;
        d++;
        i++;
    } while (i <= count);
    return (f32)((f64)amount * 1.5);
}
