/* DRAFT. Remaining diff: 64-bit input unpacking, button-history loads and branching differ. */
extern void func_801ADC64(s32), func_801ADCFC(s32), func_801AF5EC(s32);
extern u8 D_80127D50, D_8029571A, D_80295723;
extern u64 D_802D3678[];
extern s32 D_802D36A0;
void func_801BD3FC(s32 player, u64 input, s32 *state) {
    u32 buttons = input;
    u32 old = D_802D3678[player];
    u8 selection;
    if (buttons & 0xFFFF) D_802D36A0 = state[1];
    if (D_8029571A == 1 || D_8029571A == 5) {
        D_80295723 = 0;
        if ((buttons & 0x2000) && !(old & 0x2000)) {
            func_801AF5EC(0xFFFF); func_801ADC64(3);
        }
        if ((buttons & 0x400) && !(old & 0x400)) {
            selection = D_80127D50 + 1; D_80127D50 = selection;
            if ((selection & 255) >= 8) D_80127D50 = 7;
        } else if ((buttons & 0x800) && !(old & 0x800)) {
            D_80127D50--;
            if ((s32)D_80127D50 <= 0) D_80127D50 = 0;
        }
        if ((buttons & 0x1000) && !(old & 0x1000)) {
            if (D_80127D50 == 7) { func_801AF5EC(0xFFFF); func_801ADC64(2); }
            else { func_801AF5EC(0xFFFF); func_801ADCFC(player); }
        }
    } else if ((buttons & 0x1000) && !(old & 0x1000) && D_80295723 == 0) {
        func_801AF5EC(0xFFFF); D_8029571A = 1;
    }
    D_802D3678[player] = input;
}
