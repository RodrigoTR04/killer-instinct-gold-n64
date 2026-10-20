/* DRAFT. Remaining diff: Stat comparison control flow, 64-bit result stores and saved registers differ. */
extern u64 func_801BEA74(u8, u8, u8, u8 *, u8 *, s32, s32);
extern void func_801C1704(u8);
extern u8 D_8004EA9C[], D_80128308[], D_8012830A[], D_80128310[], D_80128328[];
extern s32 D_80127C30[];
extern u8 D_80128300[];
extern u64 D_802D3800[];
s32 func_801C17D0(u32 *stats, u8 player) {    u8 character = D_8004EA9C[player];
    u8 *a, *b;
    u32 value;
    u64 *out;
    b = D_80128328 + player * 11 + character;
    a = D_80128310 + player * 11 + character;
    if (player == 0) {
        value = stats[3]; if (*b < value) *b = value;
        value = stats[1]; if (*a < value) *a = value;
    } else {
        value = stats[4]; if (*b < value) *b = value;
        value = stats[2]; if (*a < value) *a = value;
    }
    out = &D_802D3800[player];
    *out = func_801BEA74(D_8012830A[player], D_80128308[player], D_80127C30[player], D_80128310 + player * 11, D_80128328 + player * 11, ((s32 *)D_80128300)[player], character);
    func_801C1704(player);
    return *out != 0;
}
