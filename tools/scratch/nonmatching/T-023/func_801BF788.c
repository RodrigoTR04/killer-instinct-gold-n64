/* DRAFT. Remaining diff: Saved-register allocation, accumulator temporaries and scheduling differ. */
extern s32 func_801BF720(s32);
u8 *func_801BF788(u8 *arg0, u8 *arg1, s32 count) {
    s32 first, combined, packed, i;
    u8 score;
    u8 *in;
    u8 *out;
    in = arg0;
    out = arg1;
    i = 0;
    if (count > 0) {
        do {
            packed = (in[1] + (in[0] << 8)) & 0xFFFF;
            first = func_801BF720((packed >> 10) & 31) << 24;
            first |= (func_801BF720((packed >> 5) & 31) << 16);
            *(s32 *)out = first | (func_801BF720(packed & 31) << 8);
            score = in[2];
            i++;
            out += 8;
            in += 3;
            *(s16 *)(out - 4) = score;
        } while (i != count);
    }
    return in;
}
