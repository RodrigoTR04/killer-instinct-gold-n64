/* DRAFT. Remaining diff: 4 linked instruction words; compiled 204 bytes, original 204 bytes. */

extern s32 func_800326F0(void);
void func_8001C370(u8 **arg0, s32 arg1, s32 arg2, u8 *arg3) {
    u8 **out;
    s32 j, i;
    s32 value;
    s32 bound;
    u8 *source, *base;
    base = arg3;
    if (arg1 > 0) {
        i = 0;
        out = arg0;
        bound = 3;
        do {
            j = 0;
            source = base;
            do {
                value = source[12] - (func_800326F0() & arg2);
                if (value < 0) (*out)[j+12] = 0;
                else (*out)[j+12] = value;
                j++;
                source++;
            } while (j != bound);
            i++;
            base += 16;
            out++;
        } while (i != arg1);
    }
}
