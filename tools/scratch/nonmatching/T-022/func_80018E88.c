/* DRAFT. Remaining diff: 2 linked words; 152/152 bytes. BLOCKED BY RODATA (T-040): the original uses float/double literals (359.0f, 0.2) from this TU's .rodata (now owned by the data asm). With literals the code matches standalone; with extern constants the two constant loads are scheduled in the opposite order. */

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
