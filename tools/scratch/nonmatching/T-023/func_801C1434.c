/* DRAFT. Remaining diff: 64-bit score loads/call ABI, branches and saved-register allocation differ. */
extern void func_801C0610(s32);
extern void func_801C08F8(s32, s32, u8, s32, u64, s32);
extern void func_801C11F0(s32, s32, s32, u8);
extern void func_801C1C34(s32, s32, s32, s32);
extern u8 D_8004A404, D_8004A407, D_8004EA9B[], D_8004EA9C, D_8004EA9D[];
extern u8 D_802D37FC, D_802D37FD, D_802D3810;
extern u64 D_802D3800[];
void func_801C1434(s32 list, s32 matrix, s32 state) {
    u8 flags;
    func_801C0610(list);
    if (D_8004A407) {
        if (D_802D37FD) { func_801C1C34(list, matrix, state, 0); return; }
        if (!(D_802D3810 & D_802D37FC) && D_802D37FC > 0) {
            func_801C08F8(list, matrix, D_8004EA9B[D_802D37FC], 0, D_802D3800[D_802D37FC - 1], D_802D37FC - 1); return;
        }
        if (D_802D37FC == 0) { func_801C11F0(list, matrix, 0, D_802D37FC); return; }
        func_801C11F0(list, matrix, 0, D_802D37FC - 1); return;
    }
    if (D_802D37FD == D_802D37FC && D_802D37FD == 0) {
        flags = D_802D3810;
        if (!(flags & 1)) {
            if (D_802D3800[0]) func_801C08F8(list, matrix, D_8004EA9C, -1, D_802D3800[0], 0);
        } else if (D_8004A404 != 2) func_801C11F0(list, matrix, -1, 0);
        if (!(flags & 2)) {
            if (D_802D3800[1]) func_801C08F8(list, matrix, D_8004EA9D[0], 1, D_802D3800[1], 1);
        } else if (D_8004A404 != 2) func_801C11F0(list, matrix, 1, 1);
    } else {
        if (!(D_802D3810 & D_802D37FC)) func_801C08F8(list, matrix, D_8004EA9B[D_802D37FC], D_802D37FC * 2 - 3, D_802D3800[D_802D37FC - 1], D_802D37FC - 1);
        else func_801C11F0(list, matrix, D_802D37FC * 2 - 3, D_802D37FC - 1);
        func_801C1C34(list, matrix, state, 3 - D_802D37FC * 2);
    }
}
