/* DRAFT. Remaining diff: First global load uses a reused base rather than a separate lui; four bytes shorter. */
extern s32 D_802D36D0, D_802D3748[];
s32 func_801BF0E8(s32 *arg0, s32 count, s32 used) {
    s32 i, j, value;
    s32 *score;
    i = 0;
    if (count > 0) {
        do {
            value = *arg0;
            j = 0;
            if (used > 0 && value != D_802D36D0) {
                do {
                    j++;
                    if (j >= used) break;
                } while (value != (&D_802D36D0)[j]);
            }
            if (j == used) {
                (&D_802D36D0)[j] = value;
                D_802D3748[j] = 10 - i;
                used++;
            } else {
                score = &D_802D3748[j];
                *score = (*score - i) + 10;
            }
            i++;
            arg0 += 2;
        } while (i != count);
    }
    return used;
}
