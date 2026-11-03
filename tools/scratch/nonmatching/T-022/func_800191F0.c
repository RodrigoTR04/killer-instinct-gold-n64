/* Stage particle rotation and velocity update. */
extern u8 D_8004AA28;
extern f32 D_8004A920[];

void func_800191F0(void) {
    T05518664Obj *obj;
    s32 i;
    f32 unit = 256.0f;
    if (D_8004AA28 == 0) {
        for (i = 0; i < 40; i++) {
            obj = &D_801D3430[i];
            if (obj->type == 0x3C) {
                D_8004A920[0] -= (f32)obj->vx / unit;
                obj->vx = (s16)(s32)((f32)obj->vx + D_8004A920[0] * unit / 200.0f);
            }
        }
    }
}
