/* T-094 DRAFT: 5 relocation-masked differing words; 184/184 bytes. Use the input/output parameters directly and a single unsigned packing accumulator. */
extern s32 func_801BF914(s32);
u8 *func_801BF988(u8 *arg0, u8 *arg1, s32 count) {
    u16 score;
    u32 packed;
    s32 i;
    i = 0;
    if (count > 0) {
        do {
            packed = func_801BF914((*(s32 *)arg1 >> 24) & 255) << 10;
            packed |= (func_801BF914((*(s32 *)arg1 >> 16) & 255) << 5);
            packed |= func_801BF914((*(s32 *)arg1 >> 8) & 255);
            arg0[0] = packed >> 8;
            arg0[1] = packed;
            score = *(u16 *)(arg1 + 4);
            i++;
            arg1 += 8;
            arg0 += 3;
            arg0[-1] = score;
        } while (i != count);
    }
    return arg0;
}
