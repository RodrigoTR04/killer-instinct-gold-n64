/* DRAFT. Remaining diff: Global bases a1/a2 and corresponding comparison/load registers are exchanged. */
extern s32 D_802D3E04;
extern s32 D_802D3E08;
extern u8 D_802D3E0C;

s32 func_801CCD74(s32 *arg0) {
    s32 var_v1;

    if (D_802D3E08 != (var_v1 = D_802D3E04)) {
        D_802D3E08 = var_v1;
        D_802D3E0C = 0xFF;
    }
    if (((s32) D_802D3E0C >= 4) && (var_v1 != 0)) {
        D_802D3E0C -= 4;
    } else {
        D_802D3E04 = 0;
        var_v1 = 0;
        D_802D3E08 = 0;
        D_802D3E0C = 0;
    }
    *arg0 = var_v1;
    return D_802D3E0C;
}
