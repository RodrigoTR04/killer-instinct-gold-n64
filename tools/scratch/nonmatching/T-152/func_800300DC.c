void func_800300DC(void *src, void *outputAddress, s32 length) {
    u16 *output = outputAddress;
    u8 *input = src;
    s32 i = 0;
    while (i < length) {
        u8 first = *input;
        if (!(first & 1)) {
            u8 second = input[1];
            input++;
            output[i] = ((second & 0xC0) * 2) + (first << 8) + (second & 0x3F);
        } else {
            u8 count = (first & 0x80) ? 2 : 1;
            u8 delta = (first >> 1) & 0x3F;
            s32 j;
            for (j = 0; j < count; j++) output[i + j] = output[i + j - delta - 1];
            i = i + j - 1;
        }
        i++;
        input++;
    }
}
