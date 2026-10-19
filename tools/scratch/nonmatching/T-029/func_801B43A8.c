/* DRAFT. Remaining diff: Shuffle pointer lifetime, saved/temporary registers, and one extra instruction differ. */
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
    group = &D_80128340;
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
        group += 3;
    } while (group != &D_80128349);
}
