/* DRAFT (T-047). See T-047/REPORT.md for comparison counts and remaining differences. */
void func_801BF678(s8 *out, s32 value) {
    s32 i;
    s8 *p;

    i = 5;
    p = out + 5;
    do {
        if (value || i == 5) {
            *p = value % 10 + 48;
        } else {
            *p = 32;
        }
        value /= 10;
        i--;
        p--;
    } while (i >= 0);
}
