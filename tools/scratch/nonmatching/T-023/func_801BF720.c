/* DRAFT. Remaining diff: C switch emits a new jump table; assembly-owned rodata blocks retention. */
s32 func_801BF720(u32 code) {
    s32 result;
    if (code < 26) return code + 'A';
    result = ' ';
    switch (code) {
        case 27: return ' ';
        case 28: return '.';
        case 29: return '/';
        case 30: return ':';
        case 31: return ',';
    }
    return result;
}
