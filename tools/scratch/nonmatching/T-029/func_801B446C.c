/* DRAFT. Remaining diff: Flag/global address reuse, byte temporaries and store scheduling differ. */
extern u8 D_802C8CE0;
extern u8 D_802C8D06;
extern u8 D_802C8CEA[];
extern s32 D_802C8C18[];
extern s8 D_80127CE8[];
extern u8 D_80127CFE[];
extern s8 D_802C8CF0[];
extern s8 D_802C8D0F;
extern u8 D_802C8D0C;
extern s32 D_802C8CDC, D_802C8CD4;
void func_801B446C(u8 arg0) {
    s32 bit;
    s32 choice;
    u8 *cursor;
    u8 previous;
    u8 next;
    u8 signedNext;
    bit = 1 << arg0;
    if (!(D_802C8CE0 & bit)) {
        if (D_802C8D06 & 8) {
            cursor = &D_802C8CEA[arg0];
            previous = *cursor;
            choice = D_802C8C18[arg0];
            next = previous + 1;
            D_80127CE8[arg0 * 11 + (previous & 15)] = choice;
            *cursor = next;
            signedNext = next;
            if (signedNext >= D_80127CFE[arg0]) {
                D_802C8CE0 |= bit;
                if (D_8004A407 != 0) D_802C8D0F = 1;
            }
            D_802C8CF0[arg0 * 11 + choice] = signedNext;
        } else {
            D_802C8CE0 |= bit;
            D_802C8CDC = D_802C8CD4 + 1;
        }
        if (D_802C8D0C == 2) D_802C8D0C = arg0;
    }
}
