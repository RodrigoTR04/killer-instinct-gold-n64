/* DRAFT. Remaining diff: 79 differing instruction words; emitted 360 / original 356 bytes (positional comparison). */
extern s32 func_8003B45C(u16 *, u16 *, u16 *);
extern s32 func_8003BFC0(u8 *);
extern s32 func_8003C030(s32, s32, s32, void *);
extern s32 func_8003C3C0(s32, s32, s32, void *, s32);
s32 func_8003B8A4(u8 *pak, u16 *id) {
    u16 locations[4];
    u16 sum, inverse;
    s32 result;
    s32 i = 1;
    if (pak[0x65] != 0) {
        pak[0x65] = 0;
        result = func_8003BFC0(pak);
        if (result != 0) return result;
    }
    locations[0] = 1; locations[1] = 3; locations[2] = 4; locations[3] = 6;
    do {
        result = func_8003C030(*(s32 *)(pak + 4), *(s32 *)(pak + 8), locations[i], id);
        if (result != 0) return result;
        func_8003B45C(id, &sum, &inverse);
        if (sum == id[14] && inverse == id[15]) break;
        i++;
    } while (i != 4);
    if (i == 4) return 10;
    {
        s32 j;
        for (j = 0; j != 4; j++) {
            if (j != i) {
                result = func_8003C3C0(*(s32 *)(pak + 4), *(s32 *)(pak + 8), locations[j], id, 1);
                if (result != 0) return result;
            }
        }
    }
    return 0;
}
