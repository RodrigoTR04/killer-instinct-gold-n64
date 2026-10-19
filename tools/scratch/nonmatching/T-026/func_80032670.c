/* DRAFT. Remaining diff: 45 positional words; 180/128 bytes including padding. Private decoder register ABI differs. */
/* Private decoder register state is represented as explicit arguments. */
u8 func_80032670(u8 *bits, u8 *tree, s32 mask, s32 bitIndex, s32 value) {
    s32 offset = 0;
    while (tree[offset] != 0) {
        s32 flags = tree[offset];
        s32 choice = mask ? value : bits[bitIndex];
        s32 step;
        if (choice & 0x80) step = tree[offset + 2] + ((flags & 0x1C) << 6);
        else step = tree[offset + 1] + ((flags >> 5) << 8);
        offset += step * 3;
    }
    return tree[offset + 1];
}
