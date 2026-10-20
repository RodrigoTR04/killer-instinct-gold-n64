/* T-045 DRAFT: 76 standalone relocation-masked positional words; 312 compiled bytes. Was 77 words/308 bytes. Changed input cursor initialized inside the nonempty-input branch. Not linked/runtime validated. */
void func_800300DC(u8 *src, s32 outputAddress, s32 length) {
    u16 *output = (u16 *)outputAddress;
    u8 *input; s32 i = 0;
    if (length > 0) { input=src;
        do {
            u8 first = *input;
            if (!(first & 1)) {
                u8 second = input[1];
                input++;
                output[i] = ((second & 0xC0) * 2) + (first << 8) + (second & 0x3F);
            } else {
                s32 n = (first & 0x80) ? 2 : 1;
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
