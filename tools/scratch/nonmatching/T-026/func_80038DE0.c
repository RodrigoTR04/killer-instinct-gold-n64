/* DRAFT. Remaining diff: 49 differing instruction words; emitted 200 / original 196 bytes (positional comparison). */
u8 func_80038DE0(s32 arg0, s32 arg1) {
    u8 *sequence = (u8 *)arg0;
    u8 **cursor = (u8 **)(sequence + arg1 * 4 + 0x18);
    u8 **repeat = (u8 **)(sequence + arg1 * 4 + 0x58);
    u8 *remaining = sequence + arg1 + 0x98;
    u8 *read;
    u8 byte;
    if (*remaining != 0) {
        read = *repeat;
        *repeat = read + 1;
        (*remaining)--;
        return *read;
    }
    read = *cursor;
    byte = *read;
    *cursor = read + 1;
    if (byte == 0xFE) {
        u8 high = read[1];
        *cursor = read + 2;
        if (high != 0xFE) {
            *cursor = read + 3;
            *cursor = read + 4;
            *repeat = read - ((high << 8) + read[2]);
            *remaining = read[3];
            read = *repeat;
            byte = *read;
            *repeat = read + 1;
            (*remaining)--;
        }
    }
    return byte;
}
