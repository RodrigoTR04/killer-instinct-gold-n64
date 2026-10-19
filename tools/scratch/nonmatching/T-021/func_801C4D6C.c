/* DRAFT. Remaining diff: Instruction/register/control-flow mismatch; see saved asm-differ output. */
extern s8 D_802D399F;
extern s32 *D_802D39A0;
extern s32 *D_802D39A4;
extern s32 *D_802D39A8;
extern s32 *D_802D39AC;
extern u8 D_802D39BA;

void func_801C4D6C(void) {
    s32 var_v1;
    s8 temp_t6;

    if (D_802D39BA & 1) {
        D_802D39AC = D_802D39A0;
    } else if (D_802D39BA & 2) {
        D_802D39AC = D_802D39A4;
    } else if (D_802D39BA & 4) {
        D_802D39AC = D_802D39A8;
    } else {
        D_802D39AC = D_802D39A0;
    }
    var_v1 = 0 & 0xFF;
    D_802D399F = 0;
    if (D_802D39AC[var_v1] != 0) {
        do {
            temp_t6 = var_v1 + 1;
            var_v1 = temp_t6 & 0xFF;
            D_802D399F = temp_t6;
        } while (D_802D39AC[var_v1] != 0);
    }
}
