/* T-173 draft: 18 positional words, 328/328 bytes in the full TU. */
extern s32 guRandom(void);
extern u8 D_802C8CC8[];
void func_801B465C(s32 arg0, s32 arg1) {
    u8 index;
    u8 current;
    u8 next;
    s32 limit;
    limit = func_801B4324((u8)arg0) + 7;
    index = D_802C8CC8[arg0];
    current = index;
    if (index >= limit) {
        index = 0;
        current = index;
        D_802C8CC8[arg0] = 0;
    }
    if (index == D_802C8CC8[1-arg0] && D_802C8CB8[0] == D_802C8CB8[1]) {
        if (D_8004A407 & (2 - arg0)) {
            if (current == D_802C8CC8[1-arg0]) {
                do {
                    D_802C8CC8[1-arg0] = guRandom() % 6;
                } while (D_802C8CC8[arg0] == D_802C8CC8[1-arg0]);
            }
        } else {
            next = index + 1;
            if (arg1 >= 0) {
                D_802C8CC8[arg0] = next;
                if (next >= 7) D_802C8CC8[arg0] = 0;
            } else {
                if (index == 0) {
                    D_802C8CC8[arg0] = 6;
                    return;
                }
                D_802C8CC8[arg0] = index - 1;
            }
        }
    }
}
