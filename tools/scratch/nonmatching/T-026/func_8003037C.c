/* DRAFT. Remaining diff: 49 differing instruction words; emitted 180 / original 196 bytes (positional comparison). */
void func_8003037C(s16 *vertices, s16 *delta, s32 count) {
    s16 *end = delta + count;
    if (count > 0) {
        do {
            vertices[0] += delta[0];
            vertices[8] += delta[0];
            vertices[16] += delta[0];
            vertices[1] += delta[1];
            vertices[9] += delta[1];
            vertices[17] += delta[1];
            vertices[2] += delta[2];
            vertices[10] += delta[2];
            vertices[18] += delta[2];
            delta += 3;
            vertices += 24;
        } while ((u32)delta < (u32)end);
    }
}
