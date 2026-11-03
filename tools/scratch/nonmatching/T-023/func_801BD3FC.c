/* T-130: emit the incoming u64 >> 32 and >> 16 helpers; 145→134 words, 440→484 B. */
extern void func_801ADC64(s32);
extern void func_801ADCFC(s32);
extern void func_801AF5EC(s32);
extern u8 D_80127D50;
extern u8 D_8029571A;
extern u8 D_80295723;
extern u64 D_802D3678[];
extern s32 D_802D36A0;

void func_801BD3FC(s32 player, u64 input, s32 *state) {
    u32 high;
    u32 shifted;
    u32 buttons;
    u32 old;
    u8 selection;

    high = input >> 32;
    shifted = input >> 16;
    buttons = (u32)input;
    old = (u32)D_802D3678[player];
    if (buttons & 0xFFFF) {
        D_802D36A0 = state[1];
    }
    if ((D_8029571A == 1) || (D_8029571A == 5)) {
        D_80295723 = 0;
        if ((buttons & 0x2000) && !(old & 0x2000)) {
            func_801AF5EC(0xFFFF);
            func_801ADC64(3);
        }
        if ((buttons & 0x400) && !(old & 0x400)) {
            selection = D_80127D50 + 1;
            D_80127D50 = selection;
            if ((selection & 0xFF) >= 8) {
                D_80127D50 = 7;
            }
        } else if ((buttons & 0x800) && !(old & 0x800)) {
            D_80127D50 -= 1;
            if ((s32)D_80127D50 <= 0) {
                D_80127D50 = 0;
            }
        }
        if ((buttons & 0x1000) && !(old & 0x1000)) {
            if (D_80127D50 == 7) {
                func_801AF5EC(0xFFFF);
                func_801ADC64(2);
            } else {
                func_801AF5EC(0xFFFF);
                func_801ADCFC(player);
            }
        }
    } else if ((buttons & 0x1000) && !(old & 0x1000) && (D_80295723 == 0)) {
        func_801AF5EC(0xFFFF);
        D_8029571A = 1;
    }
    D_802D3678[player] = input;
}
