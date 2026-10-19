/* DRAFT. Remaining diff: 37 positional words; 148/112 bytes. Decoder input state is carried in t4-t8/fp; explicit C arguments differ. */
/* The original entry consumes decoder state in t4-t8/fp. This C interface
 * exposes that state explicitly; it cannot reproduce the private register ABI. */
void func_80032600(u8 *bits, u8 *tree, s32 base, s32 mask, s32 bitIndex, s32 value) {
    s32 offset = 0;
    while (tree[base + offset] != 0) {
        s32 choice = value & 0x80;
        if (mask == 0) choice = bits[bitIndex] & 0x80;
        offset += 3 * tree[base + offset + (choice ? 2 : 1)];
    }
}
