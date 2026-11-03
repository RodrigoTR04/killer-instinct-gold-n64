/* Diagnostic only: 23/49 words, 196/196 B. The base is computed by subtracting from a scalar extern; use an array-backed view before promotion. */
/* T-105: nonmatching draft; see T-105/REPORT.md for measurement and remaining differences. */
extern void memcpy(void *, void *, s32);
extern u32 guRandom(void);
extern u8 D_80128340;
extern u8 D_80128349;
extern u8 D_801F3530;
void func_801B43A8(void) {
    s32 i;
    u32 random;
    u8 *other;
    u8 *group;
    u8 *entry;
    u8 value;
    memcpy(&D_80128340, &D_801F3530, 11);
    group = &D_80128349 - 9;
    do {
        random = guRandom();
        i = 0;
        entry = group;
        do {
            other = group + (u8)(random % 3U);
            value = *entry;
            i++;
            *entry = *other;
            entry++;
            random >>= 4;
            *other = value;
        } while (i != 3);
        group = entry;
    } while (group != &D_80128349);
}
