/* T-112 DRAFT: 74 relocation-masked positional words, 316/316 bytes.
 * Full owning-TU measurement; not linked/runtime validated. */
void func_800300DC(void *src, void *outputAddress, s32 length) {
    u16 *output = (u16 *)outputAddress;
    u8 *input; s32 i = 0;
    if (length > 0) { input=src;
        do {
            s32 first = *input;
            if (!(first & 1)) {
                u8 second = input[1];
                input++;
                output[i] = ((second & 0xC0) * 2) + (first << 8) + (second & 0x3F);
            } else {
                u8 n = (first & 0x80) ? 2 : 1;
                s32 distance = (first >> 1) & 0x3F;
                s32 j;
                for (j = 0; j < n; j++) output[i+j] = output[i+j-distance-1];
                i = i + j - 1;
            }
            i++;
            input++;
        } while (i < length);
    }
}
