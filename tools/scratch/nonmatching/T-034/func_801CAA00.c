/* DRAFT. Compiles (980 vs 998 instructions); large diff (~1000 lines): control-flow layout, prev-pad pointer (sp28) handling and the unrolled queue-reset loop differ. Logic reconstructed from m2c/asm: menu input handler (port, unused, hi, buttons) with per-port previous-button state D_802D3678. Needs T021Six and T034_D_80127D30 macro. */
typedef struct {
    s32 hi;
    s32 buttons;
} T034PadPrev;

extern s32 osSendMesg(void *, s32, s32);
extern void func_8002AA98(s32, s32);
extern s32 func_8002F6DC(s32);
extern void func_8002F6F4(s32, s32, s32 *);
extern void func_801ADC64(s32);
extern void func_801ADDD8(s32, u8 *);
extern void func_801AF5D4(s32);
extern void func_801AF5EC(s32);
extern s32 func_801AF67C(s32);
extern void func_801B3DB0(u8, s32);
extern s32 func_801C7998(s32, s32);
extern void func_801C7A98(void);
extern void func_801C7CD0(s32, s32, s32);
extern void func_801C7E98(s32, s32);
extern void func_801C7F90(void);
extern void func_801CA784(s32, s32);
extern void func_801CA7E4(s32);
extern s32 D_8004A25C;
extern s32 D_8004A260;
extern s32 D_80066C40;
extern u8 D_80127D00[8][4];
extern u8 D_80127D20[8];
extern u8 D_80127D28[8];
extern u8 D_802923A0;
extern s8 D_802923A4;
extern s8 D_802923A8;
extern u8 D_802923F0[];
extern u8 ***D_802926AC;
extern u8 *D_802926F8[];
extern u8 *D_80292710[];
extern u8 D_80295428[];
extern T034PadPrev D_802D3678[];
extern f32 D_802D39F8;
extern u8 D_802D39FC;
extern u8 D_802D39FE[2];
extern u8 D_802D3A00;
extern u8 D_802D3A01;
extern u8 D_802D3A02;
extern s8 D_802D3A04[];
extern u8 D_802D3A06;
extern u8 D_802D3A07;
extern u8 D_802D3A08;
extern f32 D_802D3A10[2];
extern u8 D_802D3A18[3];
extern u8 D_802D3E14;
extern u8 D_802D3E15;
extern u8 D_802D3FC8[];

void func_801CAA00(s32 port, s32 unused, s32 hi, s32 buttons) {
    T034PadPrev *prev;
    u8 kind;
    u8 sel;
    u8 *slot;
    u8 *ch;
    u8 player;
    s32 key;
    s32 i;
    u8 cur;
    u8 next;

    kind = D_802926F8[D_802D3A00][D_802D39FC];
    buttons &= 0xFFFF;
    hi = 0;
    sel = D_802D39FC;
    if (D_802D3A07) {
        if ((buttons & 0x100) && !(D_802D3678[port].buttons & 0x100)) {
            D_802D3A08 = 0;
        }
        prev = &D_802D3678[port];
        if ((buttons & 0x200) && !(prev->buttons & 0x200)) {
            D_802D3A08 = 1;
        }
        if ((buttons & 0xC00F) && !(prev->buttons & 0xC00F) && D_802D3A00 == 1) {
            if (D_802D3A08) {
                func_801ADDD8(1, &D_802D3A08);
                func_801C7A98();
                func_8002F6F4(D_80066C40, 8, &D_8004A25C);
                buttons |= 0x1000;
            }
            D_802D3A07 = 0;
        }
    } else if (D_802D3A00 != 3 && D_802D3A00 != 4) {
        if (D_802D3A00 == 5) {
            if (port + 1 == D_802D3E15) {
                if (hi != 0 || buttons != 0) {
                    if (hi == 0 && buttons == 0x4000 && D_802D3A18[0] == 1) {
                        *D_802926AC[sel] = D_80295428;
                        osSendMesg(D_802D3FC8, (sel << 16) + ((D_802D3E15 - 1) << 8) + 5, 1);
                        osSendMesg(D_802D3FC8, ((D_802D3E15 - 1) << 8) + 6, 1);
                    }
                    if (hi == 0 && buttons == 0x8000) {
                        D_802D3A18[0] = 1;
                    } else {
                        D_802D3A18[0] = 0;
                    }
                }
                goto nav;
            }
        } else {
            if ((buttons & 0xC30F) && !(D_802D3678[port].buttons & 0xC30F)) {
                if (D_802923A0 >= D_802923A4) {
                    if (kind != 0) {
                        func_8002F6F4(D_80066C40, 0x1B0, &D_8004A25C);
                        if (hi == 0 && buttons == 0x200) {
                            if ((s8)D_80292710[D_802D3A00][sel]-- <= 0) {
                                D_80292710[D_802D3A00][sel] = (kind & 0x1F) - 1;
                            }
                        } else {
                            D_80292710[D_802D3A00][sel]++;
                            if (D_80292710[D_802D3A00][sel] >= (kind & 0x1F)) {
                                D_80292710[D_802D3A00][sel] = 0;
                            }
                        }
                        func_8002AA98(0x7FFF, (s32)D_80292710);
                    } else if (buttons & 0xC00F) {
                        if (D_802D3A00 == 0) {
                            switch (D_802D39FC) {
                                case 4:
                                    D_802D3A00 = 3;
                                    D_802D39FC = 0;
                                    D_802D39F8 = 0.0f;
                                    break;
                                case 5:
                                    func_8002F6F4(D_80066C40, 0x109, &D_8004A25C);
                                    func_801C7F90();
                                    break;
                                case 7:
                                    D_802D3A00 = 1;
                                    D_802D39FC = 0;
                                    D_802D39F8 = 0.0f;
                                    break;
                            }
                        } else if (D_802D3A00 == 1) {
                            switch (D_802D39FC) {
                                case 0:
                                    if (D_802D3E14) {
                                        func_801C7CD0(5, 2, 3);
                                    } else {
                                        osSendMesg(D_802D3FC8, 2, 1);
                                    }
                                    break;
                                case 1:
                                    osSendMesg(D_802D3FC8, 3, 1);
                                    break;
                                case 2:
                                    D_802D3A10[1] = 0.5f;
                                    D_802D3A07 = 1;
                                    D_802D3A08 = 0;
                                    D_802D3A10[0] = D_802D3A10[1];
                                    break;
                                case 3:
                                    D_802D3A00 = 0;
                                    D_802D39FC = 0;
                                    D_802D39F8 = 0.0f;
                                    break;
                            }
                        }
                    }
                } else {
                    func_8002F6F4(D_80066C40, 0x1B2, &D_8004A260);
                    D_802D3A18[2] = 1;
                }
            }
        nav:
            prev = &D_802D3678[port];
            if ((buttons & 0x400) && !(prev->buttons & 0x400) && D_802923A0 >= D_802923A8 - 1) {
                D_802D39FC++;
                if (D_802D39FC >= D_802923F0[D_802D3A00]) {
                    D_802D39FC = D_802923F0[D_802D3A00] - 1;
                } else if (D_802926F8[D_802D3A00][D_802D39FC] == 0xFF) {
                    D_802D39FC++;
                }
            }
            if ((buttons & 0x800) && !(prev->buttons & 0x800)) {
                if (D_802D39FC > 0) {
                    D_802D39FC--;
                    if (D_802926F8[D_802D3A00][D_802D39FC] == 0xFF) {
                        D_802D39FC--;
                    }
                }
            }
        }
    } else if (D_802D3A00 == 3) {
        if ((buttons & 0x400) && !((prev = &D_802D3678[port])->buttons & 0x400)) {
            if (++D_802D39FE[port] >= 7) {
                D_802D39FE[port] = 0;
            }
        } else {
            prev = &D_802D3678[port];
            if ((buttons & 0x800) && !(prev->buttons & 0x800)) {
                if ((s8)D_802D39FE[port]-- <= 0) {
                    D_802D39FE[port] = 6;
                }
            } else {
                slot = &D_802D39FE[port];
                if (*slot != 6) {
                    if ((buttons & 0xFFFF) != (prev->buttons & 0xFFFF)) {
                        key = func_801C7998(hi, buttons);
                        player = port;
                        if (D_802D3A06) {
                            player = T034_D_80127D30[port] + 1;
                        }
                        if (key != 0) {
                            cur = *slot;
                            next = key - 1;
                            for (i = 0; i < 6; i = (u8)(i + 1)) {
                                if (next == D_80127C68[player].b[i] && i != cur) {
                                    D_80127C68[player].b[i] = D_80127C68[player].b[cur];
                                }
                            }
                            D_80127C68[player].b[cur] = next;
                            if (++*slot >= 6) {
                                *slot = 0;
                            }
                        }
                    }
                } else if ((buttons & 0xC00F) && !(prev->buttons & 0xC00F)) {
                    if (D_802D3A06) {
                        D_802D3A06 = 0;
                        func_801AF5EC(0xFFFF);
                        func_801B3DB0(port, 5);
                    } else {
                        D_802D3A00 = 0;
                    }
                }
            }
        }
    } else {
        ch = &D_80127D00[D_802D39FC][D_802D3A01];
        if ((buttons & 0x400) && !((prev = &D_802D3678[port])->buttons & 0x400)) {
            if (D_802D39FC < 7 && *(s32 *)D_80127D00[D_802D39FC] != 0) {
                D_802D39FC++;
            }
            D_802D3A01 = 0;
        } else {
            prev = &D_802D3678[port];
            if ((buttons & 0x800) && !(prev->buttons & 0x800)) {
                D_802D39FC--;
                if ((s8)D_802D39FC <= 0) {
                    D_802D39FC = 0;
                }
                D_802D3A01 = 0;
            } else if (hi == 0 && buttons == 0x100) {
                if (--D_802D3A04[port] <= 0) {
                    if (*ch <= 0x20) {
                        *ch = D_802D3A02;
                    } else if (++*ch >= 0x5B) {
                        *ch = 'A';
                    }
                    D_802D3A02 = *ch;
                    D_802D3A04[port] = 8;
                    func_801CA784(D_802D39FC + 1, (s32)&D_802D3A04[port]);
                }
            } else if (hi == 0 && buttons == 0x200) {
                if (--D_802D3A04[port] <= 0) {
                    if (*ch <= 0x20) {
                        *ch = D_802D3A02;
                    }
                    if (--*ch < 'A') {
                        *ch = 'Z';
                    }
                    D_802D3A02 = *ch;
                    D_802D3A04[port] = 8;
                    func_801CA784(D_802D39FC + 1, (s32)&D_802D3A04[port]);
                }
            } else if ((buttons & 0xC000) && !(prev->buttons & 0xC000)) {
                if (++D_802D3A01 >= 3) {
                    D_802D3A01 = 0;
                    if (D_802D39FC < 7 && *(s32 *)D_80127D00[D_802D39FC] != 0) {
                        D_802D39FC++;
                    }
                } else {
                    if (*ch <= 0x20) {
                        *ch = D_802D3A02;
                    }
                    if (D_80127D00[D_802D39FC][D_802D3A01] <= 0x20) {
                        D_80127D00[D_802D39FC][D_802D3A01] = D_802D3A02;
                    }
                    func_801CA784(D_802D39FC + 1, D_802D39FC);
                }
            } else if ((buttons & 2) && !(prev->buttons & 2)) {
                sel = D_802D39FC;
                if (D_802D39FC < 7 && *(s32 *)D_80127D00[D_802D39FC] != 0) {
                    for (i = D_802D39FC; i < 7; i = (u8)(i + 1)) {
                        *(s32 *)D_80127D00[i] = *(s32 *)D_80127D00[i + 1];
                        D_80127D20[i] = D_80127D20[i + 1];
                        D_80127D28[i] = D_80127D28[i + 1];
                        func_801C7E98(i, i + 1);
                    }
                    D_802D3A01 = 0;
                    func_801CA7E4(sel + 1);
                }
                *(s32 *)D_80127D00[7] = 0;
                D_80127D28[7] = 0;
                D_80127D20[7] = 0;
                func_801C7E98(0, 9);
            } else if ((buttons & 0x2000) && !(prev->buttons & 0x2000)) {
                if (func_801AF67C(0x60) == 0) {
                    func_801ADC64(0);
                } else {
                    osSendMesg(D_802D3FC8, 9, 1);
                }
            } else if ((buttons & 1) && !(prev->buttons & 1)) {
                for (i = 0; i < 8; i++) {
                    D_80127D20[i] = 0;
                    D_80127D28[i] = 0;
                    T034_D_80127D30[i] = (*(s32 *)D_80127D00[i] != 0) ? i + 1 : 0;
                }
            }
        }
    }
    if (D_802D3A18[2] && func_8002F6DC(D_8004A260) == 0) {
        func_8002F6F4(D_80066C40, 0x1B2, &D_8004A25C);
        D_802D3A18[2] = 0;
    }
    if (D_802D3A00 == 5 && D_802D3A18[1] < 60) {
        D_802D3A18[1]++;
    } else if ((buttons & 0x1000) && !(prev->buttons & 0x1000)) {
        if (D_802D3A06) {
            D_802D3A06 = 0;
            func_801AF5EC(0xFFFF);
            func_801B3DB0(port, 5);
        } else if (D_802D3A00 == 4) {
            for (i = 0; i < 8 && *(s32 *)D_80127D00[i] != 0; i = (u8)(i + 1)) {
            }
            if (i >= 2) {
                func_801AF5EC(0xFFFF);
                func_801B3DB0(port, 5);
            }
        } else {
            osSendMesg(D_802D3FC8, 9, 1);
            func_801ADC64(0);
            func_801AF5D4(0x10);
            D_802D3E15 = 0;
        }
        D_802D3A07 = 0;
    }
    prev->hi = hi;
    prev->buttons = buttons;
}
