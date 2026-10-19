/* DRAFT. Remaining diff: Selection-byte temporaries, saved registers and branch scheduling differ. */
extern s32 guRandom(void);
extern u8 D_802C8CC8[];
extern u8 D_802C8CC9[];
void func_801B465C(s32 arg0, s32 arg1) {
    u8 *self;
    u8 *other;
    u8 index;
    u8 current;
    u8 next;
    s32 random;
    s32 limit;
    limit = func_801B4324((u8)arg0) + 7;
    self = &D_802C8CC8[arg0];
    index = *self;
    current = index;
    if (index >= limit) {
        index = 0;
        current = index;
        *self = 0;
    }
    other = &D_802C8CC9[-arg0];
    if (current == *other && D_802C8CB8[0] == D_802C8CB8[1]) {
        if (D_8004A407 & (2 - arg0)) {
            if (current == *other) {
                do {
                    random = guRandom() % 6;
                    *other = random;
                } while (*self == (u8)random);
            }
        } else {
            next = index + 1;
            if (arg1 >= 0) {
                *self = next;
                if (next >= 7) *self = 0;
            } else {
                if (current == 0) {
                    *self = 6;
                    return;
                }
                *self = index - 1;
            }
        }
    }
}
