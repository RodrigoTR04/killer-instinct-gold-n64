/* T-045 DRAFT: 2 linked words remain; 188-byte body (196 with TU padding). Only end-pointer setup and delta-pointer move are swapped. Was 49 positional words. */
void func_8003037C(s16 *input, s16 *deltas, s32 count) {
    s16 *vertices;
    s16 *delta;
    s16 *end;
    if (count > 0) {
        vertices = input;
        delta = deltas;
        end = deltas + count;
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
