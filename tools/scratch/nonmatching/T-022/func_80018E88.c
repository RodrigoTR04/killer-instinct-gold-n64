/* DRAFT. Remaining diff: 2 linked instruction words; compiled 152 bytes, original 152 bytes. */

extern const f32 D_800488E8;
extern f32 D_8004A8C0[], D_8004A8C8;
extern const f64 D_800488F0;
void func_80018E88(void) {
    s32 i;
    for (i = 0; i < 2; i++) {
        D_8004A8C0[i] = (f64)D_8004A8C0[i] + D_800488F0;
        if (D_800488E8 < D_8004A8C0[i]) D_8004A8C0[i] = 0.0f;
    }
    D_8004A8C0[2] = (f64)D_8004A8C0[2] - D_800488F0;
    if (D_8004A8C0[2] < 0.0f) D_8004A8C0[2] = D_800488E8;
}
