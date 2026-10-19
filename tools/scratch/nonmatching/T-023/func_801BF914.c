/* DRAFT. Remaining diff: C switch emits a new jump table; default-result register also differs. */
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
