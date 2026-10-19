/* DRAFT. Compiles (896 vs 911 instructions, ~375 diff lines). Overlay entry/main loop: BSS clear, mode setup from D_80127D50/D_8004A407, then a state machine on D_80295708. Also blocked on rodata ownership: the attract-mode switch on D_8029571A needs jtbl_802927B0 (owned by the data file). Remaining diffs: the case 0/2/default sharing of the mode/fighter temporaries (sp56/sp57), the state-0 inner loop form, and register allocation. m2c needed labels added at the jump-table targets (see report). */
typedef struct {
    u8 unk0;
    u8 pad1[0x1B];
    u8 unk1C;
    u8 unk1D;
} T034GameArgs;

extern void bzero(void *, s32);
extern void boot_dma(void *, void *, s32);
extern void boot_inflate(void *, void *, void *);
extern s32 guRandom(void);
extern s32 osRecvMesg(void *, void *, s32);
extern s32 osSendMesg(void *, s32, s32);
extern void func_80012950(u8);
extern void func_8002F9FC();
extern void func_8002FA3C(void);
extern void func_801AC95C(u8 *, s32);
extern void func_801ACAD8(void);
extern void func_801ACE5C(void);
extern void func_801ACF50(void);
extern void func_801ACFC8(void);
extern void func_801AD030(void);
extern void func_801AD064(void);
extern void func_801AD098(void);
extern void func_801AD388(void);
extern void func_801AD794(s32 *, s32, s32, s32);
extern void func_801ADAD4(s32);
extern void func_801ADB20(void);
extern void func_801ADBB0(void);
extern void func_801ADC64(s32);
extern void func_801ADDD8();
extern void func_801ADE48(u8, u8, u8, u8);
extern void func_801ADEA0(void);
extern void func_801AF5D4(s32);
extern void func_801AF5EC(s32);
extern void func_801B17BC(u8, u8, u8);
extern void func_801B3DB0(u8, s32);
extern void func_801B4300(void);
extern void func_801BBB60(void);
extern s32 func_801BD200(s32);
extern void func_801BFB40(u8);
extern void func_801C1704(s32);
extern u8 func_801C1990(T034GameArgs *, u8);
extern void func_801C224C(u8, s32);
extern void func_801C3990(void *);
extern void func_801C4040(u8);
extern void func_801C407C(u8, u8);
extern void func_801C4E38(u8, u8);
extern void func_801C72B0(void);
extern void func_801C7CD0(s32);
extern void func_801C7F10(void);
extern void func_801C7F40(void);
extern void func_801CA91C(s32);
extern void func_801CB998(u8);
extern void func_801CBA2C(void);
extern void func_801CBED0(void);
extern void func_801CBF50(void);
extern s32 D_8000030C;
extern u8 D_80044A24;
extern u8 D_8004A298[];
extern s32 D_8004A2D8[];
extern s8 D_8004A401;
extern u8 D_8004A404;
extern u8 D_8004A407;
extern s32 D_8004A414;
extern void *D_8004A428[2];
extern s32 D_8004A4B0;
extern u8 D_8004AA28;
extern u8 D_8004AC88;
extern s8 D_8004AC8B;
extern u8 D_8004EA9B[];
extern u8 D_8004EA9D[];
extern u8 D_8007D900[];
extern u8 D_8007F900[];
extern u8 D_8008EA20[];
extern u8 D_800F4070[];
extern u8 D_80127C40;
extern u8 D_80127CC1;
extern u8 D_80127D39;
extern u8 D_80127D40[10];
extern u32 D_80127D4C;
extern u8 D_80127D50;
extern u8 *D_80127D80;
extern u8 D_80127E50[];
extern u8 D_8012834B;
extern u8 D_8012834C;
extern s16 *D_801CD458;
extern s32 D_80282A60;
extern u8 D_802956F0[];
extern s32 D_80295708;
extern s32 D_8029570C;
extern s32 D_80295710;
extern s32 D_80295714;
extern u8 D_80295719;
extern u8 D_8029571A;
extern s32 D_8029571C;
extern u8 D_80295720;
extern s8 D_80295721;
extern s8 D_80295723;
extern s32 D_802C9F70;
extern s32 D_802C9F74;
extern s32 D_802D36A0;
extern u8 D_802D3E15;
extern u8 D_802D3FC8[];
extern u8 D_802D3FF0[];
extern u8 D_802D4000[];
extern u8 D_8036A000[];
extern u8 D_A73980[];
extern u8 D_A77960[];

void func_801ABB20(T034GameArgs *arg0) {
    s32 size;
    u8 fighter;
    u8 mode;
    s32 state;
    s32 r;

    size = D_802D3FF0 - D_802956F0;
    if (size > 0) {
        bzero(D_802956F0, size);
    }
    D_8004AA28 = 1;
    func_801ACAD8();
    func_801AD794(&D_802C9F70, 320 << D_8004AA28, 240 << D_8004AA28, 8);
    D_802C9F70 = D_80044A24 ^ 1;
    func_801ADEA0();
    func_801BBB60();
    D_8004AC8B = 0;
    D_8004A428[0] = D_802D4000;
    D_8004A428[1] = D_8036A000;
    func_80012950(D_8004AA28);
    D_80295708 = 0;
    D_8029571A = 0;
    D_80295721 = 3;
    D_80295720 = arg0->unk0;
    D_80282A60 = func_801BD200(2);
    func_801CBED0();
    D_80295723 = 0;
    if (D_80127D80 == 0) {
        if (D_8000030C == 0) {
            D_80295723 = 1;
            func_801ADDD8();
        }
        D_80127D80 = D_80127E50;
        osSendMesg(D_802D3FC8, 7, 1);
        if (D_8000030C == 0) {
            osSendMesg(D_802D3FC8, 2, 1);
        } else {
            osSendMesg(D_802D3FC8, 0, 1);
        }
        osSendMesg(D_802D3FC8, 0, 1);
        osSendMesg(D_802D3FC8, 0, 1);
        if (D_802D3E15) {
            D_80295708 = 2;
        }
        D_8004A407 = 3;
        func_801B4300();
        func_801AC95C(D_80127D40, 10);
    } else if (D_80127D50 == 4 || D_80127D50 == 5 || D_80127D50 == 6 ||
               ((D_80127D50 == 1 || D_80127D50 == 2 || D_80127D50 == 3) && D_8004A404 != 0)) {
        if (D_80127D50 == 5 || D_80127D50 == 5) {
            osSendMesg(D_802D3FC8, 9, 1);
        }
        D_80295708 = 0;
    } else if ((D_80127D50 == 1 || D_80127D50 == 2) && D_8004A407 != 3 && D_80295720 != 0) {
        D_8004A407 |= 4;
        D_80295719 = 0x18;
        if (D_8004A407 & D_80295720) {
            D_80295708 = 3;
        } else {
            D_80295708 = 8;
        }
        D_8029570C = 3;
    } else if (D_8004A407 != 0 && D_8004A407 != 3 && D_8004A404 == 1) {
        D_80295708 = 5;
        func_801B3DB0(D_80295720 - 1, 3);
    } else if (D_8004A407 != 3) {
        D_80295719 = func_801C1990(arg0, D_8004A407);
        func_801C4040(D_80295720);
        D_80295708 = 3;
        mode = D_80127D50;
        if (mode == 3) {
            func_801CB998(D_80295719);
            if (D_80295720 == 0) {
                D_80295720 = guRandom() % 2 + 1;
            } else {
                func_801CA91C(D_80295720 - 1);
            }
            if (D_8004A404 != 2) {
                D_80295708 = 5;
                func_801B3DB0(D_80295720 - 1, 5);
            } else {
                D_80295708 = 0;
            }
            D_80295719 = 0;
        }
        if ((D_80295720 & (D_8004A407 ^ 3)) || mode == 3) {
            if (mode != 3) {
                D_80295719 |= 0x20 << (D_80295720 - 1);
                D_80295708 = 3;
                if (D_8004A407 != 0) {
                    D_80295719 &= 0x60;
                    if (D_8012834B >= 10 - (D_80127CC1 == 0) || D_80127D39 != 0) {
                        D_80295710 = 0;
                        D_8029570C = 4;
                        D_80295708 = 8;
                        if (D_80127D39 == 0) {
                            if (D_8012834C < D_80127CC1 + 1) {
                                D_8012834C = D_80127CC1 + 1;
                            }
                            arg0->unk0 = 0;
                            D_80295719 = func_801C1990(arg0, D_8004A407);
                        } else {
                            arg0->unk0 = 0;
                            D_80295719 = 0;
                        }
                        D_8004A404 = 3;
                        osSendMesg(D_802D3FC8, 9, 1);
                    }
                } else {
                    D_80295719 |= 8 << (2 - D_80295720);
                }
                D_80295710 = 5;
            }
            if (arg0->unk1C) {
                D_80295714 = D_80295708;
                D_80295708 = 6;
            }
        } else if (D_80295720 == 0) {
            D_80295719 |= 0x18 - D_8004A407 * 8;
            D_80295708 = 3;
            D_80295710 = 5;
        } else {
            D_80295719 |= 8 << (2 - D_80295720);
            D_80295710 = 0;
        }
    } else {
        D_8029571A = 5;
        func_8002F9FC();
    }
    if (D_8004A404 == 2 || D_8004A404 == 3) {
        D_80295710 = 0;
        D_80295719 &= 0x87;
        func_801C1704(0);
        func_801C1704(1);
        D_8004A404 = 2;
        func_801B4300();
    }
    if (D_80295719 == 0) {
        if (D_80295708 == 3) {
            D_80295708 = D_80295710;
        }
        if (D_80295708 == 6 && D_80295714 == 3) {
            D_80295714 = D_80295710;
        }
    }
    D_8004A414 = 0;
    D_8004A2D8[0] = 2;
    D_8004A2D8[8] = 2;
    D_8004A401 = 1;
    while (osRecvMesg(D_8004A298, &D_801CD458, 0) == 0) {
    }
    while ((state = D_80295708) != 10) {
        D_8029571C = 1;
        D_802D36A0 = D_802C9F74;
        if (state == 0) {
            D_8004A4B0 = 0;
            switch (D_8029571A) {
                case 0:
                    func_801ADAD4(0x11);
                    func_801C3990(D_800F4070);
                    func_801AF5EC(0xFFFF);
                    func_801AF5D4(1);
                    break;
                case 1:
                case 5:
                    size = D_A77960 - D_A73980;
                    func_801ADB20();
                    func_801ADC64(0);
                    func_801AF5EC(0x10);
                    func_801AF5D4(0x10);
                    boot_dma(D_A73980, D_8007F900, size);
                    boot_inflate(D_8007F900, D_8008EA20, D_8007D900);
                    break;
                case 3:
                    func_801B17BC(D_80127D40[(D_80127D4C + 8) % 10], D_80127D40[D_80127D4C % 10], D_80127D40[(D_80127D4C + 9) % 10]);
                    func_801AF5EC(0x10);
                    func_801AF5D4(0x100);
                    break;
                case 4:
                    r = guRandom();
                    func_801ADE48(D_80127D40[(D_80127D4C + 8) % 10], D_80127D40[(D_80127D4C + 9) % 10], r % 7, guRandom() % 7);
                    D_8004AC8B = 0;
                    D_8004AC88 = D_80127D40[D_80127D4C % 10];
                    D_80127D4C++;
                    D_8004A407 = 3;
                    D_80295708 = 10;
                    break;
                case 2:
                default:
                    D_80295708 = 1;
                    fighter = D_80127D40[D_80127D4C % 10];
                    D_80127D4C++;
                    break;
            }
            mode = D_8029571A;
        }
        if (state == 5) {
            D_8029571A = 1;
            mode = 1;
        }
        if (state == 0) {
            while (mode == D_8029571A) {
                if (D_80282A60 == 0) {
                    D_802D36A0 = D_802C9F74;
                }
                func_801ACE5C();
                if (D_80295708 != 0) {
                    break;
                }
            }
        }
        if (state == 5) {
            do {
                func_801ACE5C();
            } while (D_80295708 == 5);
        }
        if (state == 3) {
            func_801BFB40(D_80295719);
            while (D_80295708 == 3) {
                func_801AD388();
            }
            D_80295719 = 0;
        }
        if (state == 1) {
            func_801ADBB0();
            func_801C224C(fighter, D_802C9F74);
            D_8029571C = 1;
            while (D_80295708 == 1) {
                func_801ACF50();
            }
            func_8002F9FC();
            if (++D_8029571A >= 7) {
                D_8029571A = 1;
            }
        }
        state = D_80295708;
        if (state == 6) {
            func_801ADBB0();
            func_801C407C(arg0->unk1C, arg0->unk1D);
        }
        if (state == 6) {
            do {
                func_801AD098();
            } while (D_80295708 == 6);
        }
        if (state == 8) {
            func_801ADBB0();
            if (D_80127D50 == 1 || D_80127D50 == 2) {
                func_801C4E38(11, D_8004EA9D[D_80295720]);
            } else {
                func_801C4E38(D_8004EA9B[D_80295720], D_8004EA9D[D_80295720]);
            }
        }
        if (state == 8) {
            do {
                func_801ACFC8();
            } while (D_80295708 == 8);
        }
        if (state == 4) {
            D_8029571C = 4;
            func_801C72B0();
        }
        if (state == 4) {
            do {
                func_801AD030();
            } while (D_80295708 == 4);
        }
        if (state == 2) {
            func_801C7CD0(0);
        }
        if (state == 9) {
            func_801C7CD0(4);
        }
        if (state == 2 || state == 9) {
            do {
                func_801AD064();
            } while (D_80295708 == 2 || D_80295708 == 9);
        }
    }
    func_801CBA2C();
    if (D_80127D50 == 3) {
        func_801C7F40();
    } else {
        func_801C7F10();
    }
    if (D_80127D50 >= 2) {
        if (D_80127D50 == 2) {
            D_80127C40 = 0x11;
        } else {
            D_80127C40 = D_80127D50 - 1;
        }
    } else {
        D_80127C40 = D_80127D50;
    }
    func_801ADBB0();
    func_8002FA3C();
    func_801CBF50();
}
