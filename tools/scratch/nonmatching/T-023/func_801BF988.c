/* DRAFT. Remaining diff: Saved input/accumulator registers and final result temporaries differ. */
extern s32 func_801BF914(s32);
u8 *func_801BF988(u8 *arg0, u8 *arg1, s32 count) {
    s32 first, combined, i;
    u32 packed;
    u16 score;
    u8 *in;
    u8 *out;
    in = arg1;
    out = arg0;
    i = 0;
    if (count > 0) {
        do {
            first = func_801BF914((*(s32 *)in >> 24) & 255) << 10;
            first |= (func_801BF914((*(s32 *)in >> 16) & 255) << 5);
            packed = first | func_801BF914((*(s32 *)in >> 8) & 255);
            out[0] = packed >> 8;
            out[1] = packed;
            score = *(u16 *)(in + 4);
            i++;
            in += 8;
            out += 3;
            out[-1] = score;
        } while (i != count);
    }
    return out;
}
