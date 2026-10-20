/* DRAFT. T-043 gives this TU rodata ownership. Two instruction words still differ: default-result register and return move; jump table bytes now match. */
s32 func_801BF914(u32 code) {
    s32 result;
    if (code >= 'A' && code <= 'Z') return code - 'A';
    switch (code) {
        case ' ': return 27;
        case '.': return 28;
        case '/': return 29;
        case ':': return 30;
        case ',': return 31;
    }
    result = 27;
    return result;
}
