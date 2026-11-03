/* T-138 DRAFT: 15 differing words, 192/196 B. Nonmatching. */
extern void memcpy(void *, void *, s32);
extern u32 guRandom(void);
extern u8 D_80128340[];
extern u8 D_80128349;
extern u8 D_801F3530;
void func_801B43A8(void) {
    s32 i;
    u32 random;
    u8 *other;
    u8 *group;
    u8 *entry;
    u8 value;
    memcpy(D_80128340, &D_801F3530, 11);
    for (group = (u8 *)((u32)&D_80128349 - 9); group != &D_80128349; group = entry) {
        random = guRandom();
        i = 0;
        entry = group;
        do {
            other = group + (u8)(random % 3U);
            value = *entry;
            i++;
            *entry = *other;
            entry++;
            *other = value;
            random >>= 4;
        } while (i != 3);
    }
}
