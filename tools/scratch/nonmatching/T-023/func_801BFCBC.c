/* DRAFT. Remaining diff: 64-bit input ABI, state-machine branches, stack and global scheduling differ. */
extern s32 func_8002F6F4(), osSendMesg();
extern void func_8002FA5C();
extern void func_801ADC64(s32), func_801AF5D4(s32), func_801AF5EC(s32), func_801BFC08(s32), func_801BFC8C(void);
extern void func_801BED0C(u32, u64);
extern u8  D_8004A407, D_802D3FC8;
extern u8 D_8004A258;
extern s32 D_8004A25C, D_8004A278, D_80066C40, D_802D37D0, D_802D37D8[], D_802D37E0[], D_802D37F0[], D_802D3818[], D_802D3820, D_802D3824;
extern u32 D_80128300[];
extern u8 D_802D37E8[], D_802D37EA[], D_802D3810, D_802D3828;
extern u16 D_802D382C;
extern u64 D_802D3678[], D_802D3800[];
u8 func_801BFCBC(s32 player, u64 input, u8 flags) {
    s32 bit, mode, x, y, cell, shift, editPlayer, value;
    u32 buttons, previous, other;
    u8 result, cursor;
    s32 *timer;
    u8 *lastSecond;
    buttons = input; previous = D_802D3678[player]; other = D_802D3678[player ^ 1];
    if (D_802D382C < 0x7FFF) {
        D_802D382C += 350;
        if (D_8004A278) func_8002FA5C(D_8004A278, 8, 0x7FFF - D_802D382C);
    }
    bit = 1 << player; result = flags;
    if (flags & bit) {
        y = D_802D37E0[player]; x = D_802D37D8[player]; cursor = D_802D37EA[player];
        cell = (y / 8) * 6 + x / 8; shift = (3 - cursor) * 8;
        if (buttons & 0x800) {
            D_802D37E0[player] = y - 1;
            if (y - 1 < 0) D_802D37E0[player] = 0;
            D_802D37E8[player] &= 14;
        }
        if (buttons & 0x400) {
            value = D_802D37E0[player] + 1; D_802D37E0[player] = value;
            if (value >= 33) D_802D37E0[player] = 32;
            D_802D37E8[player] |= 1;
        } else if (!(buttons & 0x800) && (D_802D37E0[player] & 7)) {
            if (D_802D37E8[player] & 1) D_802D37E0[player]++;
            else D_802D37E0[player]--;
        }
        if (buttons & 0x200) {
            D_802D37D8[player] = x - 1;
            if (x - 1 < 0) D_802D37D8[player] = 0;
            D_802D37E8[player] &= 13;
        }
        if (buttons & 0x100) {
            value = D_802D37D8[player] + 1; D_802D37D8[player] = value;
            if (value >= 41) D_802D37D8[player] = 40;
            D_802D37E8[player] |= 2;
        } else if (!(buttons & 0x200) && (D_802D37D8[player] & 7)) {
            if (D_802D37E8[player] & 2) D_802D37D8[player]++;
            else D_802D37D8[player]--;
        }
        if (cell == 26) cell = -33;
        else if (cell == 28) cell = -19;
        if (cell != 29) {
            value = cell == 27 ? '.' : cell + 'A';
            D_802D37F0[player] = (D_802D37F0[player] & ~(255 << shift)) | (value << shift);
        }
        if ((buttons & 0xC00F) && !(previous & 0xC00F)) {
            if (cell == 27) { D_802D37EA[player] = cursor - 1; if (cursor <= 0) D_802D37EA[player] = 0; }
            else if (cell != 29) { D_802D37EA[player] = cursor + 1; if (D_802D37EA[player] >= 3) buttons |= 0x1000; }
            else buttons |= 0x1000;
        }
        if (((buttons & 0x1000) && !(previous & 0x1000)) || D_802D3824 < 2) {
            func_801BED0C(D_802D37F0[player], D_802D3800[player]);
            result = flags ^ bit; D_802D3810 |= bit;
            D_80128300[player] = D_802D37F0[player];
            if (result == 0) result = 4;
            if (!(result & 3)) osSendMesg(&D_802D3FC8, 9, 1);
        } else D_802D3824--;
    } else {
        mode = 8 << player;
        if (flags & mode) {
            editPlayer = player; if (D_8004A407) editPlayer = 0;
            timer = &D_802D3818[editPlayer]; value = *timer;
            D_802D3810 |= bit;
            if (value <= 0) {
                *timer = 1000;
                func_8002F6F4(D_80066C40, 376, &D_8004A25C, editPlayer);
                (&D_802D3828)[editPlayer + 2] = 9; value = *timer;
            }
            if (buttons & 0xC80F) { value -= 5; *timer = value; }
            if (player == editPlayer || D_8004A407) {
                *timer = --value; lastSecond = &(&D_802D3828)[editPlayer + 2];
                if (value / 100 != *lastSecond) {
                    func_8002F6F4(D_80066C40, 410, (u8 *)&D_8004A258 + editPlayer * 4 + 8, editPlayer);
                    value = *timer; *lastSecond = value / 100;
                }
            }
            if (value <= 0) {
                if (D_8004A407) { func_8002F6F4(D_80066C40, 375, &D_8004A25C); result = flags & 0xE7; }
                else result = flags & (mode ^ 255);
                if (!result) result = 4;
            }
            if ((buttons & 0x1000) && !(previous & 0x1000)) {
                result &= 0xE7; D_802D3828 = player + 1;
                if (!result) result = D_802D3828 + 4;
            }
        } else {
            mode = 32 << player;
            if (flags & mode) {
                if (mode == flags) D_802D3810 |= bit;
                if (((buttons & 0xD00F) && !(previous & 0xD00F)) || !D_8004A407 || D_802D3820 < 5) {
                    result = flags ^ mode;
                    if (!result) result = D_802D3828 + 4;
                } else D_802D3820 -= 5;
            } else if (flags == 0) {
                if ((buttons & 0x2800) && !(previous & 0x2800) && !(other & 0x2800)) func_801BFC08(0);
                if ((buttons & 0x400) && !(previous & 0x400) && !(other & 0x400)) func_801BFC8C();
                if ((buttons & 0x1000) && !(previous & 0x1000)) {
                    func_801ADC64(0); func_801AF5EC(0xFFFF); func_801AF5D4(16); D_802D37D0 = 0;
                }
            } else D_802D3810 |= bit;
        }
    }
    D_802D3678[player] = (input & 0xFFFFFFFF00000000ULL) | buttons;
    return result;
}
