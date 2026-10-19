/* DRAFT. Remaining diff: 26 positional words; 104/96 bytes. Private t1-t3 state survives calls in original. */
/* Private assembly ABI keeps the accumulated result in t1 across calls. */
extern u8 func_80038DE0(s32, s32);
s32 func_80038EA4(s32 sequence, s32 track) {
    s32 byte = func_80038DE0(sequence, track);
    s32 value = byte;
    while (byte & 0x80) {
        byte = func_80038DE0(sequence, track);
        value = (value << 7) + (byte & 0x7F);
    }
    return value;
}
