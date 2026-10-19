/* DRAFT. Remaining diff: Division scheduling, normalized argument lifetimes and integer temporary registers differ. */
void func_801B677C(u8 arg0, f32 *arg1, f32 *arg2, f32 *arg3, u16 arg4) {
    s32 remainder;
    s32 row;
    s32 remaining;
    remainder = (s32)arg4 % 3;
    arg0--;
    remaining = arg4 - arg0;
    if (remainder >= remaining) {
        *arg1 = (f32)((220 / (remainder + 1)) * remaining);
    } else {
        *arg1 = (f32)((((arg0 % 3) * -18) << 2) + 180);
    }
    row = arg0 / 3;
    *arg2 = (f32)(100 - (220 / ((arg4 + 2) / 3)) * row);
    *arg3 = -100.0f;
    if (arg4 >= 10) *arg2 = (f32)(100 - row * 73);
}
