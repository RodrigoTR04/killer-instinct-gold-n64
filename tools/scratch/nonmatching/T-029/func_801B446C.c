/* DRAFT (T-062). 31 differing words (was 34), 292 bytes. Both byte tables are unsigned. Remaining: flag-base retention and instruction scheduling. */
extern u8 D_802C8CE0;
extern u8 D_802C8D06;
extern u8 D_802C8CEA[];
extern s32 D_802C8C18[];
extern u8 D_80127CE8[][11];
extern u8 D_80127CFE[];
extern u8 D_802C8CF0[][11];
extern u8 D_802C8D0F;
extern u8 D_802C8D0C;
extern s32 D_802C8CDC, D_802C8CD4;
void func_801B446C(u8 arg0) {
    s32 bit;
    s32 flags;
    s32 choice;
    u8 *cursor;
    u8 pos;
    u8 *flagsp = &D_802C8CE0;

    flags = *flagsp;
    bit = 1 << arg0;
    if (!(flags & bit)) {
        if (D_802C8D06 & 8) {
            cursor = &D_802C8CEA[arg0];
            pos = *cursor;
            choice = D_802C8C18[arg0];
            D_80127CE8[arg0][pos & 15] = choice;
            *cursor = pos + 1;
            pos = *cursor;
            if (pos >= D_80127CFE[arg0]) {
                *flagsp = flags | bit;
                if (D_8004A407 != 0) D_802C8D0F = 1;
            }
            D_802C8CF0[arg0][choice] = pos;
        } else {
            *flagsp = flags | bit;
            D_802C8CDC = D_802C8CD4 + 1;
        }
        if (D_802C8D0C == 2) D_802C8D0C = arg0;
    }
}
