/* DRAFT. Remaining diff: Early-return branch shape differs (three fewer instructions). */
extern void func_801CBF8C();
extern s32 osContGetReadData();
extern s32 osContStartReadData();
extern s32 osRecvMesg();
extern u8 D_800684E0;
extern u8 D_802D3E0D;

s32 func_801CCDE8(void) {
    u16 sp18[12];

    if (D_802D3E0D == 0) {
        func_801CBF8C();
        if (D_802D3E0D == 0) {
            goto block_9;
        }
    }
    osContStartReadData(&D_800684E0);
    osRecvMesg(&D_800684E0, 0, 1);
    osContGetReadData(sp18);
    if ((sp18[0] & 0x1000) && (D_802D3E0D & 1)) {
        return 1;
    }
    if ((sp18[3] & 0x1000) && (D_802D3E0D & 2)) {
        return 2;
    }
block_9:
    return 0;
}
