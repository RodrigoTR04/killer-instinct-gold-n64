/* DRAFT. Remaining diff: 6 differing words / 124 bytes: pointer increment and load/add scheduling; same registers and arithmetic. */
s32 func_8003B3E0(u8 *data, s32 length) {
    s32 sum = 0;
    u8 *p = data;
    s32 i;
    for (i = 0; i < length; i++, p++) {
        sum += *p;
        sum &= 0xFFFF;
    }
    return sum & 0xFFFF;
}
