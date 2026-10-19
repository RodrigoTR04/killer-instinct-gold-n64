/* DRAFT. Remaining diff: 60 differing instruction words; emitted 228 / original 252 bytes (positional comparison). */
s32 func_8003B45C(u16 *data, u16 *sum, u16 *inverse) {
    s32 i;
    *inverse = 0;
    *sum = 0;
    for (i = 0; i < 14; i++) {
        u16 value = data[i];
        *sum += value;
        *inverse += ~value;
    }
    return 0;
}
